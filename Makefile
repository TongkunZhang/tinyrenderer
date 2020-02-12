FLAGS = -Wall -std=c++98 -ggdb -g -pg -O0
LIBS = -lm

all: tinyrenderer

tinyrenderer: tinyrenderer.o tgaimage.o
	g++ ${FLAGS} -o $@ $^

%.o : %.c
	g++ ${FLAGS} -c $<

.PHONY : clean
clean :
	-rm *.o tinyrenderer