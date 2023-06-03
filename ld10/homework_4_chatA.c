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
            int rret = read(STDIN_FILENO, buf, sizeof(buf)-1); // 留一个给空字符
            if(rret == 0) {
                printf("--------Detect [off signal] from STDIN. Chat is closing!\n");
                write(fdw, "Bye!\n", 16);
                break;
            }

            // 获取日历时间
            time_t stime = time(NULL);
            struct tm* calendar_timep = localtime(&stime);

            // 发送消息内容前，先发送日历信息
            write(fdw, calendar_timep, sizeof(*calendar_timep));
            // free(calendar_timep);

            // 发送消息内容
            memset(buf, 0, sizeof(buf));
            write(fdw, buf, strlen(buf));
        }
        if(FD_ISSET(fdr, &rdset)){
            time_la = time_cur;
            
            // 先接收日历信息
            struct tm calendar_time;
            int rret = read(fdr, &calendar_time, sizeof(calendar_time));
            if(rret == 0) {
                printf("--------Detect [off signal] from ChatB. Chat is closing!\n");
                break;
            }

            // 再接收信息内容
            memset(buf, 0, sizeof(buf));
            read(fdr, buf, sizeof(buf));
            printf("====(%d/%d/%d weekday-%d %d:%d:%d)From ChatB: %s",
                   calendar_time.tm_year,
                   calendar_time.tm_mon, 
                   calendar_time.tm_mday,
                   calendar_time.tm_wday,
                   calendar_time.tm_hour,
                   calendar_time.tm_min,
                   calendar_time.tm_sec,
                   buf);
        }
        if(time_cur - time_la > 50) {
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

