#include <func.h>

int main(int argc, char* argv[])
{
    while(1){
        pid_t pid = getpid();
        sleep(2);
        printf("pid = %d\n",pid);
    }
    return 0;
}

