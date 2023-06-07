#include <func.h>

void handler(int signum) {
    sleep(5);
    printf("signal %d has been handled.\n", signum);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, handler);
    while(1){
        sleep(1);
    }
    return 0;
}

