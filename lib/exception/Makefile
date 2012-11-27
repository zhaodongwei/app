all : exception
.PHONY : all
exception : test.o exception.o
	g++ -I ./include -o exception test.o exception.o

test.o : test/test.cpp
	g++ -c -I ./include test/test.cpp

exception.o : include/* src/*
	g++ -c -I ./include src/exception.cpp

clean:
	rm *.o exception
