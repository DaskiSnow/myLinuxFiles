// func.h,将func.h移动到/usr/include目录下
// 包含了所需的头文件，和一些常用的宏函数，方便使用。
#ifndef __YUKI_FUNC_H__
#define __YUKI_FUNC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARGS_CHECK(agrc, n) {                                   \
    if (argc != n) {                                            \
        fprintf(stderr,"Error: expected %d arguments.\n",n);    \
        exit(1);                                                \
    }                                                           \
}

#define ERROR_CHECK(retval, val, msg) {                         \
    if(retval == val){                                          \
        perror(msg);                                            \
        exit(1);                                                \
    }                                                           \
}

#define SIZE(a) (sizeof(a) / sizeof(a[0]))

#endif

