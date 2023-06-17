#include <50func.h>
int main(){
    int fds[2];
    //pipe(fds);
    socketpair(AF_UNIX,SOCK_STREAM,0,fds);
    printf("sv[0] = %d, sv[1] = %d\n", fds[0], fds[1]);
    if(fork() == 0){
        //  子进程
        close(fds[1]);
        int fd1;
        read(fds[0],&fd1,sizeof(fd1));
        printf("child, fd1 = %d\n", fd1);
        sleep(5);
        printf("sleep over\n");
        ssize_t sret = write(fd1,"world",5);
        printf("sret = %ld\n", sret);
    }
    else {
        // 父进程
        // 父 --> 子
        close(fds[0]);//父进程关闭管道的读端
        int fd1 = open("file1",O_RDWR);
        write(fds[1],&fd1,sizeof(fd1));
        printf("parent, fd1 = %d\n", fd1);
        write(fd1,"hello",5);
        wait(NULL);
        exit(0);
    }
}
