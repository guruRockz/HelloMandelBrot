OBJS=main.o MandelBrotGen.o MandelBrotThread.o

CCFLAGS=`sdl-config --cflags` -Wall -c -O3

MandelBrotGen.o: MandelBrotGen.h MandelBrotThread.cpp
	g++ $(CCFLAGS) MandelBrotGen.cpp

MandelBrotThread.o: MandelBrotThread.h
	g++ $(CCFLAGS) MandelBrotThread.cpp

main.o: MandelBrotGen.cpp
	g++ $(CCFLAGS) main.cpp

all:  $(OBJS) main.cpp
	g++ `sdl-config --libs` -O3 -o MandelBrotGen main.o MandelBrotGen.o MandelBrotThread.o 


