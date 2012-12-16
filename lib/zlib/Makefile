objs = tools.o main.o
all: tools
.PHONY: all

tools: $(objs)
	g++ -o tools $(objs)

main.o: test/main.cpp include/* 
	g++ -I ./include -c test/main.cpp
tools.o: src/tools.cpp include/*
	g++ -I ./include -c src/tools.cpp

clean:
	rm -rf tools $(objs)
