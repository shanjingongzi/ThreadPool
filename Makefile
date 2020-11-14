INCDIR:=-I ./include
SRCS:=$(wildcard ./src/*.cpp)
OBJS:=$(patsubst ./src/%.cpp,%.o,$(SRCS))
CC:=g++
FLAG:=-Wall -g -lpthread
main : main.o
	$(CC) $(FLAG) $(OBJS)  -o main
%.o : ./src/%.cpp
	$(CC) $(FLAG) $(SRCS) $(INCDIR) -c 
clean:
	del .\*.o 