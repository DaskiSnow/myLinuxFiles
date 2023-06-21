#include "head.h"

int epollAdd(int epfd, int fd) {
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);

    return 0;
}

int epollDel(int epfd, int fd) {
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);

    return 0;
}
