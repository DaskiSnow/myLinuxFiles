SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .
SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS := $(patsubst %.cc, $(OBJ_DIR)/%.o, $(SRCS))
EXE := main
#EXES := $(SRCS: %.cc=%)  # 从.cc生成可执行文件

CC := g++
CFLAGS  := -Wall -g -std=c++11 #-fsanitize=leak
LDFALGS := -lpthread  
CPPFALGS:= -DEBUG
# 开启内存泄露检查功能：-fsanitize=leak
# 开启地址越界检查功能：-fsanitize=address
# 开启越界详细错误信息：-fno-omit-frame-pointer
# -llog4cpp  
# 取消编译器优化 -fno-elide-constructors

.PHONY: out clean rebulid
out:$(EXE)

$(EXE):$(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFALGS)
#	$(RM) $(OBJS)

%.o:%.cc
	$(CC) $< -c -o $@ $(CFLAGS)

clean:
	$(RM) $(EXE)
	$(RM) $(OBJS)

rebulid: clean out
