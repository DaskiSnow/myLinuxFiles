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
    sigset_t pend;
    sigemptyset(&pend);
    sigpending(&pend);
    if(sigismember(&pend,SIGINT)){
        printf("SIGINT is pending!\n");
    } 
    else {
        printf("SIGINT is not pending!\n");
    } 
    ret = sigprocmask(SIG_UNBLOCK,&mask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    while(1);
    return 0;
}
