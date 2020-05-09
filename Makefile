SRCS = $(wildcard *.c ./src/*.c ./src/utils/*.c)    #wildcard把 指定目录 ./ 和 ../lib 下的所有后缀是c的文件全部展开。
#SRCS := $(shell find . -name "*.c")
OBJS = $(SRCS:.c = .o)    #OBJS将$(SRCS)下的.c文件转化为.o文件

CC = gcc   #代表所使用的编译器

INCLUDES = -I./include  #头文件查找路径

CCFLAGS = -g -Wall -O0   #附加参数

OUTPUT = fixElf   #输出程序名称

all:$(OUTPUT)

$(OUTPUT) : $(OBJS)
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS)

%.o : %.c
	$(CC) -c $< $(CCFLAGS)

clean:
	rm -rf $(OUTPUT) *.o    #清除中间文件及生成文件

.PHONY:clean