SRCS := main.c worker.c tcpInit.c epoll.c transfile.c taskQueue.c threadPool.c authenticate.c
OBJS := $(SRCS:%.c=%.o)
server:$(OBJS)
	gcc $^ -o $@ -lpthread -lcrypt
%.o:%.c
	gcc -c $^ -o $@ -g
clean:
	$(RM) $(OBJS) server
