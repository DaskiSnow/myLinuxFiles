#include <func.h>
#include "head.h"

int sendfd(int sfd, int fdtosend, int indextosend) {
    // 初始化消息前两个字段
    struct msghdr msghdr;
    memset(&msghdr, 0, sizeof(msghdr));
    
    // 消息的正文字段
    struct iovec msg_iov[1];
    msg_iov[0].iov_base = &indextosend;
    msg_iov[0].iov_len = sizeof(indextosend);
    msghdr.msg_iov = msg_iov;
    msghdr.msg_iovlen = SIZE(msg_iov);

    // 消息的控制字段
    struct cmsghdr* pcmsghdr = (struct cmsghdr *)calloc(1, CMSG_LEN(sizeof(int)));
    pcmsghdr->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsghdr->cmsg_level = SOL_SOCKET;
    pcmsghdr->cmsg_type = SCM_RIGHTS;
    // 找到data的首地址，强转成int*，再解引用赋值
    *(int*)CMSG_DATA(pcmsghdr) = fdtosend;
    msghdr.msg_control = pcmsghdr;
    msghdr.msg_controllen = CMSG_LEN(sizeof(int));

    int ret = sendmsg(sfd, &msghdr, 0);
    ERROR_CHECK(ret, -1, "sendfd");

    return 0;
}

int recvfd(int sfd, int* pfdtorecv, int* pindextorecv) {
    struct msghdr msghdr;
    memset(&msghdr, 0, sizeof(msghdr));

    struct iovec msg_iov[1];
    msg_iov[0].iov_base = pindextorecv;
    msg_iov[0].iov_len = sizeof(int);
    msghdr.msg_iov = msg_iov;
    msghdr.msg_iovlen = SIZE(msg_iov);

    struct cmsghdr *pcmsghdr = (struct cmsghdr *)calloc(1, CMSG_LEN(sizeof(int)));
    pcmsghdr->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsghdr->cmsg_level = SOL_SOCKET;
    pcmsghdr->cmsg_type = SCM_RIGHTS;

    msghdr.msg_control = pcmsghdr;
    msghdr.msg_controllen = CMSG_LEN(sizeof(int));

    int ret = recvmsg(sfd, &msghdr, 0);
    ERROR_CHECK(ret, -1, "recvfd");

    *pfdtorecv = *(int *)CMSG_DATA(pcmsghdr);
    *pindextorecv = *(int *)msghdr.msg_iov[0].iov_base;

    return 0;
}

