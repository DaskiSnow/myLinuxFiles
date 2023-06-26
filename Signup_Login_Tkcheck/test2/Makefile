# 将所有.c文件编译链接成可执行程序
Srcs := $(wildcard *.c)
Exes := $(patsubst %.c, %, $(Srcs))

CC := gcc
CFLAGS := -Wall -g -lcrypt -lmysqlclient -lpthread -ll8w8jwt 

.PHONY: Out clean rebuild

Out: $(Exes)

%: %.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	$(RM) $(Exes)
rebuild: clean Out
