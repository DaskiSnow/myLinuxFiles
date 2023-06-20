#include "threadPool.h"
// 版本1 发生一个小文件
//int transfile(int netfd){
//    send(netfd,"file1",5,0);//文件名
//    int fd = open("file1",O_RDWR);
//    char buf[1024] = {0};
//    ssize_t ret = read(fd,buf,sizeof(buf));
//    send(netfd,buf,ret,0);//文件的内容
//    return 0;
//}

// 版本2 小火车发生一个小文件
//int transfile(int netfd){
//    train_t train = {5,"file1"};
//    send(netfd,&train,sizeof(int)+train.length,0);//文件名
//    int fd = open("file1",O_RDWR);
//    bzero(&train,sizeof(train));
//    ssize_t ret = read(fd,train.data,sizeof(train.data));
//    train.length = ret;
//    send(netfd,&train,sizeof(int)+train.length,0);//文件内容
//    return 0;
//}

//版本3 小火车发生一个大文件
//int transfile(int netfd){
//    train_t train = {5,"file1"};
//    send(netfd,&train,sizeof(int)+train.length,MSG_NOSIGNAL);//文件名
//    int fd = open("file1",O_RDWR);
//    while(1){
//        bzero(&train,sizeof(train));
//        ssize_t ret = read(fd,train.data,sizeof(train.data));
//        train.length = ret;
//        send(netfd,&train,sizeof(int)+train.length,MSG_NOSIGNAL);//文件内容
//        if(ret == 0){
//            break;
//        }
//    }
//    close(fd);
//    return 0;
//}
//
//版本4 小火车发生一个大文件 显示进度条
//int transfile(int netfd){
//    train_t train = {5,"file1"};
//    send(netfd,&train,sizeof(int)+train.length,MSG_NOSIGNAL);//文件名
//    int fd = open("file1",O_RDWR);
//    struct stat statbuf;
//    fstat(fd,&statbuf);
//    train.length = sizeof(statbuf.st_size);
//    memcpy(train.data,&statbuf.st_size,train.length);
//    send(netfd,&train,sizeof(int)+train.length,MSG_NOSIGNAL);//文件长度
//    /*
//    while(1){
//        bzero(&train,sizeof(train));
//        ssize_t ret = read(fd,train.data,sizeof(train.data));
//        train.length = ret;
//        send(netfd,&train,sizeof(int)+train.length,MSG_NOSIGNAL);//文件内容
//        if(ret == 0){
//            break;
//        }
//    }*/
//    // 先mmap
//    char *p = (char *)mmap(NULL,statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0); 
//    off_t cursize = 0;
//    while(cursize < statbuf.st_size){
//        if(statbuf.st_size - cursize > 1000){
//            train.length = 1000;
//        }
//        else{
//            train.length = statbuf.st_size - cursize;
//        }
//        send(netfd,&train.length,sizeof(int),MSG_NOSIGNAL);
//        send(netfd,p+cursize,train.length,MSG_NOSIGNAL);
//        cursize += train.length;
//    }
//    train.length = 0;
//    send(netfd,&train.length,sizeof(int),MSG_NOSIGNAL);
//    munmap(p,statbuf.st_size);
//    close(fd);
//    return 0;
//}
//版本5 大火车
int transfile(int netfd){
    sleep(10);
    printf("sleep over!\n");
    train_t train = {5,"file1"};
    send(netfd,&train,sizeof(int)+train.length,MSG_NOSIGNAL);//文件名
    int fd = open("file1",O_RDWR);
    struct stat statbuf;
    fstat(fd,&statbuf);
    train.length = sizeof(statbuf.st_size);
    memcpy(train.data,&statbuf.st_size,train.length);
    send(netfd,&train,sizeof(int)+train.length,MSG_NOSIGNAL);//文件长度
    // 先mmap
    //char *p = (char *)mmap(NULL,statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0); 
    //send(netfd,p,statbuf.st_size,MSG_NOSIGNAL);
    //munmap(p,statbuf.st_size);
    sendfile(netfd,fd,NULL,statbuf.st_size);
    close(fd);
    return 0;
}
