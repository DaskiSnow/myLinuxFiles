#include <iostream>
#include <string>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using namespace log4cpp;

#define __LogInfo(msg) {      \
    char output_msg[1024] = {0};                                        \
    sprintf(output_msg, " %s:%s:%d  %s", __FILE__, __func__, __LINE__, msg);     \
    Mylogger::getInstance()->info(output_msg); \
} 

#define __LogError(msg) {      \
    char output_msg[1024] = {0};                                        \
    sprintf(output_msg, " %s:%s:%d  %s", __FILE__, __func__, __LINE__, msg);     \
    Mylogger::getInstance()->error(output_msg); \
} 

#define __LogWarn(msg) {      \
    char output_msg[1024] = {0};                                        \
    sprintf(output_msg, " %s:%s:%d  %s", __FILE__, __func__, __LINE__, msg);     \
    Mylogger::getInstance()->warn(output_msg); \
} 

#define __LogDebug(msg) {      \
    char output_msg[1024] = {0};                                        \
    sprintf(output_msg, " %s:%s:%d  %s", __FILE__, __func__, __LINE__, msg);     \
    Mylogger::getInstance()->debug(output_msg); \
} 

// 单例模式实现Mylogger.cc
class Mylogger
{
public:
    static Mylogger * getInstance();
    static void destroy();
	void warn(const char *msg);
	void error(const char *msg);
	void debug(const char *msg);
	void info(const char *msg);
	void crit(const char *msg);
	void fatal(const char *msg);
	
private:
	Mylogger();
	~Mylogger();
    
private:
    static Mylogger * _pInstance;
    Category & _root;
};

Mylogger* Mylogger::_pInstance = nullptr;

Mylogger::Mylogger() 
: _root(Category::getRoot().getInstance("SnowCategory"))
{
    // 1. 日志布局
    PatternLayout *ppl1 = new PatternLayout();
    ppl1->setConversionPattern("%d{%H:%M:%S,%I} %c [%p] %m%n");
    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d{%H:%M:%S,%I} %c [%p] %m%n");

    // 2. 日志目的地Appender
    // 终端
    OstreamAppender *pos = new OstreamAppender("OstreamAppender", &cout);
    pos->setLayout(ppl1);
    // 卷积文件
    RollingFileAppender *prfa = new RollingFileAppender("RollingFileAppender", "rfa.log", 2*1024, 5);
    prfa->setLayout(ppl2);
    
    // 3. 日志记录器Category、绑定目的地、设置优先级
    _root.addAppender(pos);
    _root.addAppender(prfa);
    _root.setPriority(Priority::DEBUG);
}

Mylogger::~Mylogger() {
    _root.shutdown();
}

Mylogger * Mylogger::getInstance() {
    if(_pInstance != nullptr) return _pInstance;
    _pInstance = new Mylogger; // 无参构造
    return _pInstance;
}

void Mylogger::destroy() {
    if(!_pInstance) return ;
    delete _pInstance;
}

void Mylogger::warn(const char * msg) {
    
    _root.warn(msg);
}

void Mylogger::error(const char * msg) {
    _root.error(msg);
}

void Mylogger::debug(const char * msg) {
    _root.debug(msg);
}

void Mylogger::info(const char * msg) {
    _root.info(msg);
}

void Mylogger::fatal(const char * msg) {
    _root.fatal(msg);
}

void Mylogger::crit(const char * msg) {
    _root.crit(msg);
}

// 模板函数
template<typename... Args>
void LogInfo(Args... args)
{
    char msg[1024] = {0};
    sprintf(msg, args...);
    __LogInfo(msg);
}

template<typename... Args>
void LogError(Args... args)
{
    char msg[1024] = {0};
    sprintf(msg, args...);
    __LogError(msg);
}
template<typename... Args>
void LogWarn(Args... args)
{
    char msg[1024] = {0};
    sprintf(msg, args...);
    __LogWarn(msg);
}

template<typename... Args>
void LogDebug(Args... args)
{
    char msg[1024] = {0};
    sprintf(msg, args...);
    __LogDebug(msg);
}

void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
    Mylogger::destroy();
}

void test1() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    __LogInfo("The log is info message");
    __LogError("The log is error message");
    __LogWarn("The log is warn message");
    __LogDebug("The log is debug message");
    Mylogger::destroy();
}

void test2()
{
	int number = 100;
	const char *pstr = "hello, log4cpp";
    LogInfo("This is an info message. number = %d, str = %s\n", number, pstr); 
    LogError("This is an error message. number = %d, str = %s\n", number, pstr);
	LogWarn("This is a warn message. number = %d, str = %s\n", number, pstr);
	LogDebug("This is a debug message. number = %d, str = %s\n", number, pstr);
}

int main() {
    test2();
}
