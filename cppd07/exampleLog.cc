#include <iostream>
#include <log4cpp/SimpleLayout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>

using std::cout;
using std::endl;
using namespace log4cpp;

void test()
{
    //1、日志的布局
    /* SimpleLayout *psl = new SimpleLayout(); */
    BasicLayout *pbl =  new BasicLayout();

    //2、日志的目的地
    OstreamAppender *pos = new OstreamAppender("ostream",&cout);
    /* pos->setLayout(psl); */
    pos->setLayout(pbl);

    //3、Catagory的种类,日志记录器
    Category &root = Category::getRoot();
    root.addAppender(pos);
    
    //当Category设置的优先级大于等于root调用的时候，书写的优先级
    //的时候，才能将这些日志记录下来
    //4、过滤器
    root.setPriority(Priority::ERROR);

    //记录日志
    root.fatal("this is an fatal message");
    root.alert("this is an alert message");
    root.crit("this is an crit message");
    root.error("this is an error message");
    root.warn("this is an warn message");
    root.info("this is an info message");
    root.debug("this is an debug message");

    //回收内存
    Category::shutdown();
}

void test2()
{
    //1、日志的布局
    PatternLayout *ppl1 = new PatternLayout();
    ppl1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m%n");

    //2、日志的目的地
    //注意：一个日志的目的地要对应一种日志的布局，不能共用
    //一旦共用就会发生错误
    //终端
    OstreamAppender *pos = new OstreamAppender("ostream", &cout);
    pos->setLayout(ppl1);

    //文件
    FileAppender *pfa = new FileAppender("FileAppender", "wd.txt");
    pfa->setLayout(ppl2);

    //3、Catagory的种类,日志记录器
    Category &root = Category::getRoot().getInstance("mycat");
    root.addAppender(pos);
    root.addAppender(pfa);
    
    //当Category设置的优先级大于等于root调用的时候，书写的优先级
    //的时候，才能将这些日志记录下来
    //4、过滤器
    root.setPriority(Priority::ERROR);

    //记录日志
    root.fatal("this is an fatal message");
    root.alert("this is an alert message");
    root.crit("this is an crit message");
    root.error("this is an error message");
    root.warn("this is an warn message");
    root.info("this is an info message");
    root.debug("this is an debug message");

    //回收内存
    Category::shutdown();
}

void test3()
{
    //1、日志的布局
    PatternLayout *ppl1 = new PatternLayout();
    ppl1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ppl2 = new PatternLayout();
    ppl2->setConversionPattern("%d %c [%p] %m%n");

    //2、日志的目的地
    //注意：一个日志的目的地要对应一种日志的布局，不能共用
    //一旦共用就会发生错误
    //终端
    OstreamAppender *pos = new OstreamAppender("ostream", &cout);
    pos->setLayout(ppl1);

    //回滚文件(卷积文件)
    RollingFileAppender *prfa = 
        new RollingFileAppender("RollingFileAppender"
                                , "wd.txt"
                                , 5*1024
                                , 3);
    prfa->setLayout(ppl2);

    //3、Catagory的种类,日志记录器
    Category &root = Category::getRoot().getInstance("mycat");
    root.addAppender(pos);
    root.addAppender(prfa);
    
    //当Category设置的优先级大于等于root调用的时候，书写的优先级
    //的时候，才能将这些日志记录下来
    //4、过滤器
    root.setPriority(Priority::ERROR);

    //记录日志
    size_t idx = 300;
    while(idx > 0)
    {
        root.fatal("this is an fatal message");
        root.alert("this is an alert message");
        root.crit("this is an crit message");
        root.error("this is an error message");
        root.warn("this is an warn message");
        root.info("this is an info message");
        root.debug("this is an debug message");
        --idx;
    }

    //回收内存
    Category::shutdown();
}
int main(int argc, char **argv)
{
    test3();
    return 0;
}
