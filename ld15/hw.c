#include <func.h>

void handler(int signum, siginfo_t* p, void* p1) {
    printf("Before signum = %d\n", signum);
    sleep(5);  // 模拟处理时间
    sigset_t pendingSet;
    sigpending(&pendingSet);
    if(sigismember(&pendingSet, SIGQUIT)){
        printf("SIGQUIT is pending!\n");
    }
    else{
        printf("SIGQUIT is not pending!\n");
    }
    printf("pid = %d\n", p->si_pid);
    printf("After signum = %d\n", signum);

}

int main(int argc, char* argv[])
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));

    // 额外阻塞3号
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGQUIT); 

    act.sa_mask = mask;
    act.sa_flags = SA_SIGINFO | SA_RESTART;
    act.sa_sigaction = handler;
    sigaction(SIGINT, &act, NULL);

    char buf[2048] = {0};
    ssize_t rret;
    rret = read(STDIN_FILENO, buf, sizeof(buf));
    ERROR_CHECK(rret, -1, "read");

    return 0;
}

