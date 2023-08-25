#include <func.hh>
#include <signal.h>
#include "workflow/WFFacilities.h"
#include "workflow/RedisMessage.h"
#include "workflow/WFTaskFactory.h"
#include "workflow/Workflow.h"

using namespace std;

void redisCallback(WFRedisTask * redisTask)
{
    fprintf(stdout, "\033[36m--Task Running--\033[0m\n");
    // 1. 检查任务状态和错误情况
    using namespace protocol;

    int state = redisTask->get_state();
    int error = redisTask->get_error();
    switch(state)
    {
    case WFT_STATE_SYS_ERROR:
        fprintf(stderr, "system error: %s\n", strerror(error));
        break;
    case WFT_STATE_DNS_ERROR:
        fprintf(stderr, "DNS error: %s\n", gai_strerror(error));
        break;
    case WFT_STATE_SUCCESS:
        break;
    }
    if(state != WFT_STATE_SUCCESS)
    {
        fprintf(stderr, "Failed. Press Ctrl-C to exit.\n");
        return;
    }
    RedisResponse * resp = redisTask->get_resp();
    RedisValue value;
    resp->get_result(value);    // redis的结果保存在val对象中
    if(value.is_error())        // redis任务执行成功, 但并不意味redis服务器会正确返回, 可能会返回错误
    {
        fprintf(stderr, "Error reply.");
        state = WFT_STATE_TASK_ERROR;
    }

    // 2. 获取Redis请求信息
    RedisRequest * req = redisTask->get_req();
    string cmd;
    vector<string> params;
    req->get_command(cmd);
    req->get_params(params);
    cout << "command: " << cmd << endl;
    cout << "params: ";
    for(auto & param : params)
    {
        cout << param << " ";
    }
    cout << endl;

    // 3. 获取Redis响应信息
    if(value.is_int())
    {
        cout << "response(int): "<< value.int_value() << endl;
    }
    else if(value.is_array())
    {
        cout << "response(array): "<< endl;
        for(size_t i = 0; i < value.arr_size(); ++i)
        {
            cout << "[" << i << "] ";
            cout << value[i].string_value() << endl;
        }
    }
    else if(value.is_string())
    {
        cout << "response(string): "<< value.string_value() << endl;

    }
    /* cout << "debug_string: " << value.debug_string() << endl; */
    fprintf(stdout, "\033[36m--Task Finished--\033[0m\n\n");
}

static WFFacilities::WaitGroup waitGroup(1); 

void handler(int signum)
{
    waitGroup.done();
}

void test()
{
    signal(SIGINT, handler);

    // 1. 创建两个redis任务, 一个写, 一个读, 并将读任务放在写任务的序列容器中
    string url = "redis://127.0.0.1:6379"; 
    /* WFRedisTask * redisWriteTask = WFTaskFactory::create_redis_task(url, 1, redisCallback); */    
    WFRedisTask * redisReadTask = WFTaskFactory::create_redis_task(url, 1, redisCallback);    
    WFRedisTask * redisWriteTask = WFTaskFactory::create_redis_task(url, 1, [redisReadTask](WFRedisTask * redisWriteTask){redisCallback(redisWriteTask); series_of(redisWriteTask)->push_back(redisReadTask);});    
    protocol::RedisRequest * writeReq = redisWriteTask->get_req();
    protocol::RedisRequest * readReq = redisReadTask->get_req();
    writeReq->set_request("HSET", {"student", "1", "Snow", "2", "Hazuyuki", "3", "Daski"});
    readReq->set_request("HGETALL", {"student"});

    redisWriteTask->start();

    waitGroup.wait();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

