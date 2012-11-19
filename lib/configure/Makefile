all : configure
.PHONY: all

configure : test.o configure.o
	g++ -o configure test.o configure.o

test.o : test/test.cpp src/configure.cpp include/*
	g++ -I ./include -c test/test.cpp

configure.o : src/configure.cpp include/*
	g++ -I ./include -c src/configure.cpp

clean:
	rm test.o configure.o configure




