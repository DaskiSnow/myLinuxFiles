#include <func.h>

void handler(int signum, siginfo_t *p, void* p1) {
    printf("signum = %d\n", signum);
    
}

int main(int argc, char* argv[])
{
    int fds[2];
    pipe(fds);
    if(fork()) { // 父; 父读子写
        close(fds[1]);

        // 注册信号，并设置能重启系统调用
        struct sigaction act;
        memset(&act, 0, sizeof(act));
        act.sa_sigaction = handler;
        act.sa_flags = SA_SIGINFO | SA_RESTART;
        sigaction(SIGINT, &act, NULL);

        char buf[2048] = {0};
        ssize_t rret;
        rret = read(STDIN_FILENO, buf, sizeof(buf)); // 为什么当换成fds[0]就不重启阻塞了？
        ERROR_CHECK(rret, -1, "read");
        printf("rret = %ld\n", rret);

        return 0;

    }
    else{ // 子
        close(fds[0]);
        while(1);

        return 0;
    }
}

