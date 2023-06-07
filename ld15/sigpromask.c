#include <func.h>

int main()
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    int ret = sigprocmask(SIG_BLOCK,&mask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    printf("block success!\n");
    sleep(3);
    ret = sigprocmask(SIG_UNBLOCK,&mask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    while(1);
    return 0;
}
