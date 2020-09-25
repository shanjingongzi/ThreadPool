INCDIR:=-I ./include
SRCS:=$(wildcard ./src/*.cpp)
OBJS:=$(patsubst ./src/%.cpp,%.o,$(SRCS))
CC:=g++
main : main.o
	$(CC) $(OBJS) -fPIC -shared -o main.so
%.o : ./src/%.cpp
	$(CC) $(SRCS) -c 