#include "head.h"
int sendfd(int sockfd, int fdtosend){
    // fdtosend 要发送的文件对象的文件描述符
    struct msghdr hdr;
    bzero(&hdr,sizeof(hdr));//不可省略 设置好msgname
    //消息的正文字段
    int data = 3;
    struct iovec iov[1];
    iov[0].iov_base = &data;
    iov[0].iov_len = sizeof(data);
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1;
    //消息的控制字段
    struct cmsghdr * pcmsg = (struct cmsghdr *)calloc(1,CMSG_LEN(sizeof(int)));
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    // 找到data的首地址，强转成int *， 再解引用赋值
    *(int *)CMSG_DATA(pcmsg) = fdtosend;
    hdr.msg_control = pcmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    int ret = sendmsg(sockfd,&hdr,0);
    ERROR_CHECK(ret,-1,"sendmsg");
    return 0;
}
int recvfd(int sockfd, int *pfdtorecv){
    struct msghdr hdr;
    bzero(&hdr,sizeof(hdr));//不可省略 设置好msgname
    int data;
    struct iovec iov[1];
    iov[0].iov_base = &data;
    iov[0].iov_len = sizeof(data);
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1;
    //消息的控制字段
    struct cmsghdr * pcmsg = (struct cmsghdr *)calloc(1,CMSG_LEN(sizeof(int)));
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    hdr.msg_control = pcmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    int ret = recvmsg(sockfd,&hdr,0);
    ERROR_CHECK(ret,-1,"recvmsg");
    printf("data = %d\n", data);
    *pfdtorecv = *(int *)CMSG_DATA(pcmsg);
    return 0;
}
