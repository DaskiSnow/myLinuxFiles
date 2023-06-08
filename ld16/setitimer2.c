#include <func.h>

void handler(int signum) {
    time_t now = time(NULL);
    printf("%s\n", ctime(&now));
}

// 使用真实计时器，统计while(1)程序执行时间
int main(int argc, char* argv[])
{
    signal(SIGPROF, handler);

    // 设置实时计时器：每1s发送一次信号
    struct itimerval timer;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;
    timer.it_value.tv_sec = 1;
    timer.it_value.tv_usec = 0;
    setitimer(ITIMER_PROF, &timer, NULL);

    while(1);

    return 0;
}

