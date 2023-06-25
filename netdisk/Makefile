SRCS := main.c
OBJS := $(SRCS:%.c=%.o)
demo:$(OBJS)
	gcc $^ -o $@ -lpthread -lcrypt -lmysqlclient -ll8w8jwt
%.o:%.c
	gcc -c $^ -o $@ -g
clean:
	$(RM) $(OBJS) demo
