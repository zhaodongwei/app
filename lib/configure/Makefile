all : configure
.PHONY: all

configure : test.o configure.o conf_struct.o
	g++ -o configure test.o configure.o conf_struct.o

test.o : test/test.cpp src/configure.cpp include/*
	g++ -I ./include -c test/test.cpp

configure.o : src/configure.cpp include/*
	g++ -I ./include -c src/configure.cpp

conf_struct.o : src/conf_struct.cpp include/*
	g++ -I ./include -c src/conf_struct.cpp

clean:
	rm test.o configure.o conf_struct.o configure




