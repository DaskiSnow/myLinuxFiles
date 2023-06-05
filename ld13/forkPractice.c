#include <func.h>

int main(int argc, char* argv[])
{
    pid_t pid = fork();

    if(pid == 0) {
        char* arr_input[] = {"ls", "-a", "--color=auto",NULL};
        int ret_execv = execvp("ls",arr_input);
        ERROR_CHECK(ret_execv, -1, "execv");
    }
    else{
        wait(NULL);
    }
    return 0;
}

