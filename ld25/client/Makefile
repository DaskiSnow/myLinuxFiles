SRCS := main.c epoll.c transfile.c
OBJS := $(SRCS:%.c=%.o)

client: $(OBJS)
	gcc $^ -o $@ -Wall -lpthread -lcrypt
%.o: %.c
	gcc -c $< -o $@ -g

.PHONY: clean rebulid

clean:
	$(RM) $(OBJS) client
rebulid: clean client
