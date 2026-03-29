cc := gcc
LIBS := 
INCLUDES := -I inc
SRCS := src/*.c

all:
	$(cc) $(SRCS) $(INCLUDES)  -o agribot $(LIBS)

install:
	sudo apt-get install libc6-dev valgrind


run: all
	./agribot

clean:
	rm -f agribot

