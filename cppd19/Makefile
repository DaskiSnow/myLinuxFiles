SRCS := $(wildcard *.cc)
#EXES := $(SRCS: %.cc=%)
EXES := $(patsubst %.cc, %, $(SRCS))

CC := g++
CFALGS := -Wall -g -std=c++11 -llog4cpp -lpthread 
# 取消编译器优化 -fno-elide-constructors

.PHONY: out clean rebulid

out: $(EXES)

%:%.cc
	$(CC) $< -o $@ $(CFALGS)

clean:
	$(RM) $(EXES)

rebulid: clean out
