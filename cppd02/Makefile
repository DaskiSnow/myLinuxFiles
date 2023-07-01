SRCS := $(wildcard *.cc)
#EXES := $(SRCS: %.cc=%)
EXES := $(patsubst %.cc, %, $(SRCS))

CC := g++
CFALGS := -Wall -g -std=c++11

.PHONY: out clean rebulid

out: $(EXES)

%:%.cc
	$(CC) $< -o $@ $(CFALGS)

clean:
	$(RM) $(EXES)

rebulid: clean out
