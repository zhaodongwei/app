all : wordseg lib
.PHONY: all
lib_config = ../exception/libexception.a ../zdict/libzdict.a ../zlib/libzlib.a
headers = -I ./include -I ../exception/include -I ../zdict/include -I ../zlib/include

wordseg: test.o lib
	g++ -o wordseg test.o libwordseg.a $(lib_config)

wordseg.o : src/wordseg.cpp include/*
	g++ -c $(headers) src/wordseg.cpp

test.o : test/test.cpp
	g++ -c $(headers) test/test.cpp

lib: wordseg.o
	ar cqs libwordseg.a wordseg.o

clean:
	rm wordseg.o test.o wordseg libwordseg.a
