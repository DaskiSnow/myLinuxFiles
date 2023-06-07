#include <func.h>

void handler(int signum) {
    printf("\nBefore signum = %d\n", signum);
    sleep(5);
    printf("\nAfter signum = %d\n", signum);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, handler);
    while(1){
        sleep(1);
    }
    return 0;
}

