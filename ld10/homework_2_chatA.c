#include <func.h>

int main(int argc, char* argv[])
{
    // ./homework_2_chatA 1.pipe 2.pipe
    ARGS_CHECK(argc, 3);
    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open fdw");
    int fdr = open(argv[2], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open fdr");
    
    char buf[2048];
    fd_set rdset;
    time_t time_la = time(NULL);
    struct timeval timeout;
    ssize_t rret;
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fdr, &rdset);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        select(fdr+1, &rdset, NULL, NULL, &timeout);
        time_t time_cur = time(NULL);
        if(FD_ISSET(STDIN_FILENO, &rdset)) {
            memset(buf, 0, sizeof(buf));
            rret = read(STDIN_FILENO, buf, sizeof(buf)-1); // 留一个给空字符
            if(rret == 0) {
                printf("--------Detect [off signal] from STDIN. Chat is closing!\n");
                write(fdw, "Bye!\n", 16);
                break;
            }
            write(fdw, buf, strlen(buf));
        }
        if(FD_ISSET(fdr, &rdset)){
            time_la = time_cur;
            memset(buf, 0, sizeof(buf));
            rret = read(fdr, buf, sizeof(buf));
            if(rret == 0) {
                printf("--------Detect [off signal] from ChatB. Chat is closing!\n");
                break;
            }
            printf("====From ChatB: %s", buf);
        }
        if(time_cur - time_la > 10) {
            printf("--------No message received from ChatB for 10s. Chat is closing!\n");
            write(fdw, "You didn't talk for 10s. Bye!\n", 32);
            break;
        }
    }
    close(fdr);
    close(fdw);
    printf("--------Chat is closed!\n");
    return 0;
}

