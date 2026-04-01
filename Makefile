cc := gcc
LIBS := -L/usr/local/lib -lwiringPi
INCLUDES := -I inc
SRCS := src/*.c

all:
	$(cc) -o agribot $(SRCS) $(INCLUDES) $(LIBS)

install:
	sudo apt-get install libc6-dev valgrind
# 	git clone git://git.drogon.net/wiringPi
	cd WiringPi
	git pull origin
	./build

run: all
	./agribot

clean:
	rm -f agribot

