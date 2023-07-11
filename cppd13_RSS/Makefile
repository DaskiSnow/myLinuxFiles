SRCS := test.cpp tinyxml2.cpp
#EXES := $(SRCS: %.cc=%)
EXES := test

CC := g++
CFALGS := -Wall -g -std=c++11 -llog4cpp -lpthread # -fno-elide-constructors
# 取消编译器优化 -fno-elide-constructors

.PHONY: out clean rebulid

out: $(EXES)

$(EXES): $(SRCS)
	$(CC) $< -o $@ $(CFALGS)

clean:
	$(RM) $(EXES)

rebulid: clean out
