objs = zlib.o main.o sign.o
all: zlib
.PHONY: all

zlib: $(objs)
	g++ -o zlib $(objs)

main.o: test/main.cpp include/* 
	g++ -I ./include -c test/main.cpp
zlib.o: src/zlib.cpp include/*
	g++ -I ./include -c src/zlib.cpp
sign.o: src/sign.cpp include/*
	g++ -I ./include -c src/sign.cpp

clean:
	rm -rf zlib $(objs)
