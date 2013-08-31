all : exception lib
.PHONY : all
exception : test.o lib
	g++ -I ./include -o exception test.o libexception.a

test.o : test/test.cpp include/*
	g++ -c -I ./include test/test.cpp

exception.o : include/* src/*
	g++ -c -I ./include src/exception.cpp

lib : exception.o
	ar cqs libexception.a exception.o

clean:
	rm *.o exception libexception.a
