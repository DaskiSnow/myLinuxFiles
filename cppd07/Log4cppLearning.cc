#include <iostream>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
using std::cout;
using std::cin;
using std::endl;
using namespace log4cpp;

void test() {
    // 1、日志布局
    PatternLayout *ppl1 = new PatternLayout();
    ppl1->setConversionPattern("%d{%H:%M:%S,%I} %c [%p] %m%n");
    
    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d{%H:%M:%S,%I} %c [%p] %m%n");

    PatternLayout *ppl3 = new PatternLayout();
    ppl3->setConversionPattern("%d{%H:%M:%S,%I} %c [%p] %m%n");
    
    // 2、日志目的地Appender
    // 终端
    OstreamAppender *pos = new OstreamAppender("O", &cout);
    pos->setLayout(ppl1);
    // 文件
    FileAppender *pfa = new FileAppender("F", "fileAppender.txt");
    pfa->setLayout(ppl2);
    // 卷积文件(卷积文件最大值2048，备份文件最大数5)
    RollingFileAppender *prfa = new RollingFileAppender("R", "rollingFileAppender.txt", 2048, 5);
    prfa->setLayout(ppl3);
    
    // 3、日志记录器Category
    Category & root = Category::getRoot().getInstance("SnowCategory");
    root.addAppender(pos);
    root.addAppender(pfa);
    root.addAppender(prfa);

    // 4、设置记录的优先级
    root.setPriority(Priority::DEBUG);
    
    // 5、模拟记录日志信息
    for(int i = 0; i < 400; i++) {
        root.fatal("write a fatel message in log");
        root.alert("write a alert message in log");
        root.crit("write a crit message in log");
        root.error("write a error message in log");
        root.warn("write a warn message in log");
        root.notice("write a notice message in log");
        root.info("write a info message in log");
        root.debug("write a debug message in log");
    }
    
    // 6、释放空间
    Category::shutdown();
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}

