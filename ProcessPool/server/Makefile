SRCS:=main.c worker.c tcpInit.c sendfd.c epoll.c
OBJS:=$(SRCS:%.c=%.o)
server:$(OBJS)
	gcc $^ -o $@ -lpthread
%.o:%.c
	gcc -c $^ -o $@ -g
clean:
	$(RM) $(OBJS) server
