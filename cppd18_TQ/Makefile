SRCS := Query.cc
OBJS := $(SRCS:.cc=.o)
TARGET := Query

CXX := g++
CXXFLAGS := -Wall -g -std=c++11 
.PHONY: out clean rebulid

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(EXES)

rebulid: clean out
