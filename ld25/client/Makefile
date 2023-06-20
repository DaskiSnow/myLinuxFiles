SRCS := main.c
OBJS := $(SRCS:%.c=%.o)

client: $(OBJS)
	gcc $^ -o $@ -Wall -lpthread
%.o: %.c
	gcc -c $< -o $@ -g

.PHONY: clean rebulid

clean:
	$(RM) $(OBJS) client
rebulid: clean client
