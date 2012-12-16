all: zdict
.PHONY: all

zdict: zdict.o test.o
	g++ -o zdict test.o zdict.o

zdict.o : src/zdict.cpp include/*
	g++ -I ./include -c src/zdict.cpp

test.o : test/test.cpp include/*
	g++ -I ./include -c test/test.cpp

clean:
	rm test.o zdict.o zdict
