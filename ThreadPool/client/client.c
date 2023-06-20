#include <func.h>
typedef struct train_s {
    int length;
    char data[1000];
} train_t;
// 版本1 
//int recvfile(int netfd){
//    char filename[1024] = {0};
//    recv(netfd,filename,sizeof(filename),0);
//    int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
//    char buf[1024] = {0}; 
//    ssize_t ret = recv(netfd,buf,sizeof(buf),0);
//    write(fd,buf,ret);
//    return 0;
//}
// 版本2 
//int recvfile(int netfd){
//    char filename[1024] = {0};
//    int length;
//    recv(netfd,&length,sizeof(int),0);
//    recv(netfd,filename,length,0);
//    int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
//    char buf[1024] = {0}; 
//    recv(netfd,&length,sizeof(int),0);
//    recv(netfd,buf,length,0);
//    write(fd,buf,length);
//    return 0;
//}
// 版本3 
//int recvfile(int netfd){
//    char filename[1024] = {0};
//    int length;
//    recv(netfd,&length,sizeof(int),MSG_WAITALL);
//    recv(netfd,filename,length,0);
//    int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
//    char buf[1024] = {0}; 
//    while(1){
//        recv(netfd,&length,sizeof(int),MSG_WAITALL);
//        if(length != 1000){
//            printf("length = %d\n", length);
//        }
//        if(length == 0){
//            break;
//        }
//        bzero(buf,sizeof(buf));
//        recv(netfd,buf,length,MSG_WAITALL);
//        write(fd,buf,length);
//    }
//    close(fd);
//    return 0;
//}
int recvn(int netfd, void *buf, int length){
    int total = 0;//已经recv的总字节数
    char *p = (char *)buf;//void * --> char *
    while(total < length){
        int ret = recv(netfd,p+total,length-total,0);
        if(ret == 0){
            return -1;
        }
        total += ret;
    }
    return 0;
}
//用了recvn的版本3
//int recvfile(int netfd){
//    char filename[1024] = {0};
//    int length;
//    recvn(netfd,&length,sizeof(int));
//    recvn(netfd,filename,length);
//    int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
//    char buf[1024] = {0}; 
//    while(1){
//        recvn(netfd,&length,sizeof(int));
//        if(length != 1000){
//            printf("length = %d\n", length);
//        }
//        if(length == 0){
//            break;
//        }
//        bzero(buf,sizeof(buf));
//        recvn(netfd,buf,length);
//        write(fd,buf,length);
//    }
//    close(fd);
//    return 0;
//}
//版本4 进度条
//int recvfile(int netfd){
//    char filename[1024] = {0};
//    int length;
//    recvn(netfd,&length,sizeof(int));
//    recvn(netfd,filename,length);
//    int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
//    off_t filesize;
//    recvn(netfd,&length,sizeof(int));
//    recvn(netfd,&filesize,length);
//    printf("filesize = %ld\n", filesize);
//    off_t cursize = 0;
//    off_t slice = filesize/10000;
//    off_t lastsize = 0; //上一次printf的时候，已经发送的长度
//    char buf[1024] = {0}; 
//    while(1){
//        recvn(netfd,&length,sizeof(int));
//        if(length != 1000){
//            printf("length = %d\n", length);
//        }
//        if(length == 0){
//            break;
//        }
//        bzero(buf,sizeof(buf));
//        recvn(netfd,buf,length);
//        cursize += length;
//        if(cursize - lastsize > slice){
//            printf("%5.2lf%%\r",100.0 * cursize / filesize);
//            fflush(stdout);
//            lastsize = cursize;
//        }
//        write(fd,buf,length);
//    }
//    printf("100.00%%\n");
//    close(fd);
//    return 0;
//}
//版本5 大火车
int recvfile(int netfd){
    char filename[1024] = {0};
    int length;
    recvn(netfd,&length,sizeof(int));
    recvn(netfd,filename,length);
    int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, 0666);
    off_t filesize;
    recvn(netfd,&length,sizeof(int));
    recvn(netfd,&filesize,length);
    printf("filesize = %ld\n", filesize);
    ftruncate(fd,filesize);
    char *p = (char *)mmap(NULL,filesize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    recvn(netfd,p,filesize);
    munmap(p,filesize);
    close(fd);
    return 0;
}
int main(int argc, char *argv[])
{
    // ./client 192.168.118.128 1234
    ARGS_CHECK(argc,3);
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(sockfd,(struct sockaddr *)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret,-1,"connect");
    recvfile(sockfd);
    close(sockfd);
    return 0;
}

