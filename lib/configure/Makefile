all : configure lib
.PHONY: all

configure : test.o lib
	g++ -o configure test.o libconfigure.a

test.o : test/test.cpp src/configure.cpp include/*
	g++ -I ./include -c test/test.cpp

configure.o : src/configure.cpp include/*
	g++ -I ./include -c src/configure.cpp

conf_struct.o : src/conf_struct.cpp include/*
	g++ -I ./include -c src/conf_struct.cpp

lib : configure.o conf_struct.o
	ar cqs libconfigure.a configure.o conf_struct.o

clean:
	rm test.o configure.o conf_struct.o configure libconfigure.a




