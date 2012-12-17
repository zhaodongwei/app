objs = zlib.o main.o sign.o md5.o
all: zlib md5app lib
.PHONY: all

zlib: $(objs)
	g++ -o zlib $(objs)

main.o: test/main.cpp include/* 
	g++ -I ./include -c test/main.cpp
zlib.o: src/zlib.cpp include/*
	g++ -I ./include -c src/zlib.cpp
sign.o: src/sign.cpp include/*
	g++ -I ./include -c src/sign.cpp
md5.o : src/md5.cpp include/*
	g++ -I ./include -c src/md5.cpp

md5app : md5app.o $(objs)
	g++ -o md5 md5app.o zlib.o sign.o md5.o
md5app.o : src/md5app.cpp include/*
	g++ -I ./include -c src/md5app.cpp

lib : zlib.o sign.o md5.o
	ar cqs libzlib.a zlib.o sign.o md5.o

install:
	sudo cp md5 /usr/bin/

clean:
	rm -rf zlib $(objs) md5app.o md5 libzlib.a
