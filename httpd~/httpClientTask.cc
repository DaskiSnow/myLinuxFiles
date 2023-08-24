#include <signal.h>
#include <iostream>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/HttpUtil.h>

using namespace std;

// 初始化时, 计数器的值为1
static WFFacilities::WaitGroup waitGroup(1);

void handler(int signum)
{
    printf("signum = %d\n", signum);
    waitGroup.done(); 
    printf("waitGroup done!\n");
}

// 接收到响应报文后执行
void httpCallback(WFHttpTask * httpTask)
{
    printf("httptask is running\n"); 
    // 1. 检查错误状态
    int state = httpTask->get_state();
    int error = httpTask->get_error();
    switch(state)
    {
        case WFT_STATE_SYS_ERROR:
            printf("system error: %s\n", strerror(error));
            break;
        case WFT_STATE_DNS_ERROR:
            printf("dns error: %s\n", strerror(error));
            break;
        case WFT_STATE_SUCCESS:
            break;
    }
    if(state != WFT_STATE_SUCCESS)
    {
        printf("error occurs!\n");
        return;
    }

    // 2. 获取HTTP请求信息
    protocol::HttpRequest * req = httpTask->get_req();
    // 2.1 读取起始行
    string method = req->get_method();
    string uri = req->get_request_uri();
    string version = req->get_http_version();
    cout << method << " " << uri << " " << version << endl;
    // 2.2 读取首部字段
    protocol::HttpHeaderCursor cursorReq(req);
    string name, value;
    while(cursorReq.next(name, value))
    {
        cout << name << ": " << value << endl;
    }
    // 2.3 读取消息体
    const void * bodyReq = nullptr;
    size_t sizeReq = 0;
    req->get_parsed_body(&bodyReq, &sizeReq);
    string strbodyReq((char *)bodyReq, sizeReq);
    cout << "bodyReqSize: " << sizeReq << endl;
    cout << "bodyReq: " << strbodyReq << endl;
    cout << "----------------" << endl;

    // 3. 获取HTTP响应信息
    // 3.1 起始行
    protocol::HttpResponse * resp = httpTask->get_resp();
    string httpVersion = resp->get_http_version();
    string statusCode = resp->get_status_code();
    string reasonPhrase = resp->get_reason_phrase();
    cout << httpVersion << " " << statusCode << " " << reasonPhrase << endl;
    // 3.2 首部字段
    protocol::HttpHeaderCursor cursorResp(resp);   
    while(cursorResp.next(name, value))
    {
        cout << name << ": " << value << endl;
    }
    // 3.3 读取消息体
    const void * bodyResp = nullptr;
    size_t sizeResp = 0;
    resp->get_parsed_body(&bodyResp, &sizeResp);
    string strbodyResp((char *)bodyResp, sizeResp);
    cout << "bodyRespSize:" << sizeResp << endl;
    cout << "bodyResp: " << strbodyResp << endl;
    cout << "----------------" << endl;
    cout << "exit httpCallback" << endl;
}

// 需要开启nginx服务端, 使用配置文件1_live.conf
void test()
{
    signal(SIGINT, handler);
    string url = "http://192.168.182.131:80/cppreference-en";
    
    // 1. 创建http任务
    WFHttpTask * httpTask = WFTaskFactory::create_http_task(url, 1, 1, httpCallback);

    // 2. 设置任务属性
    httpTask->get_req()->set_method("GET");
    httpTask->get_req()->add_header_pair("Accept", "/");
    httpTask->get_req()->add_header_pair("User-Agent", "Snow's Workflow");

    // 3. 递交给框架运行
    httpTask->start();

    waitGroup.wait();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
