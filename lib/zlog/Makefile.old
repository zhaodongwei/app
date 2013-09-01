all : zlog libzlog.a
.PHONY: all

zlog : zlog.o test.o
	g++ -o zlog zlog.o test.o ../exception/libexception.a ../configure/libconfigure.a -lpthread

zlog.o : src/zlog.cpp include/*
	g++ -c -I ./include -I ../exception/include -I ../configure/include src/zlog.cpp

test.o : test/test.cpp include/*
	g++ -c -I ./include -I ../exception/include -I ../configure/include test/test.cpp

libzlog.a : zlog.o
	ar cqs libzlog.a zlog.o

clean :
	rm test.o zlog.o libzlog.a zlog	
