#include <func.h>

int main(int argc, char* argv[])
{
    pid_t pid = fork();
    if(pid == 0) {
        exit(-1); 
    }
    else {
        int status;
        wait(&status);
        if(WIFEXITED(status)) {
            printf("child exit code is %d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}

