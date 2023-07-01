SRCS := $(wildcard *.cc)
#EXES := $(SRCS: %.cc=%)
EXES := $(patsubst %.cc, %, $(SRCS))

CC := g++
CFALGS := -Wall -g

.PHONY: out clean rebulid

out: $(EXES)

%:%.cc
	$(CC) $< -o $@ $(CFLAGS)

clean:
	$(RM) $(EXES)

rebulid: clean out
