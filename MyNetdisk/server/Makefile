SRCS := main.c worker.c epoll.c taskQueue.c signup_login_tkcheck.c
OBJS := $(SRCS:%.c=%.o)
server:$(OBJS)
	gcc $^ -o $@ -lpthread -lcrypt -lmysqlclient
%.o:%.c
	gcc -c $^ -o $@ -g
clean:
	$(RM) $(OBJS) server
