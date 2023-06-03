#ifndef __WD_FUNC_H
#define __WD_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define SIZE(a) (sizeof(a)/sizeof(a[0]))

#define ARGS_CHECK(argc, n) {               \
    if (argc != n) {                        \
        fprintf(stderr, "Error: expected %d arguments\n", n);   \
        exit(1);                            \
    }                                       \
}

#define ERROR_CHECK(retval, val, msg) {    \    
    if (retval == val) {                   \
        perror(msg);                       \
        exit(1);                           \
    }                                      \
}

#endif

