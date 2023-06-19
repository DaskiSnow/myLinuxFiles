SRCS := main.c worker.c tcp.c epoll.c fdIPC.c 
OBJS := $(SRCS: %.c = %.o)
CC   := gcc
FLAGS:= -g -Wall -lpthread

server: $(OBJS)
	$(CC) $^ -o $@ $(FLAGS)
%.o: %.c
	$(CC) -c $< -o $@ -g

.PTHONY: clean rebulid

clean:
	$(RM) $(OBJS)
rebulid: clean server
	
