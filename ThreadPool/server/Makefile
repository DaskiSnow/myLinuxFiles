SRCS:=main.c worker.c tcpInit.c epoll.c transfile.c taskQueue.c threadPool.c
OBJS:=$(SRCS:%.c=%.o)
server:$(OBJS)
	gcc $^ -o $@ -lpthread
%.o:%.c
	gcc -c $^ -o $@ -g
clean:
	$(RM) $(OBJS) server
