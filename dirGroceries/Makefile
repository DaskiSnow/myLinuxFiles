# 将所有.c文件编译链接成可执行程序
SRCS := $(wildcard *.c)
EXES := $(patsubst %.c, %, $(SRCS))

CC := gcc
CFLAGS := Wall -g
.PHONY: out

out: $(EXES)

%: %.c
	$(CC) $< -o $@ $(CFALGS)

clean:
	$(RM) $(EXES)

rebuild: clean out
