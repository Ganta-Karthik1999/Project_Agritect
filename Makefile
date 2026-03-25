cc := gcc
LIBS := -lwiringPi
INCLUDES := -I inc
SRCS := src/*.c

all:
	$(cc) $(SRCS) $(INCLUDES)  -o agribot

run: all
	./agribot

clean:
	rm -f agribot

