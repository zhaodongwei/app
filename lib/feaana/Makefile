all : feaana lib
.PHONY : all

objects = feaana.o funclib.o spliter.o

feaana: test.o lib
	g++ -o feaana test.o $(objects) ../exception/libexception.a

feaana.o : src/feaana.cpp ./include/*
	g++ -c -I ./include -I ../exception/include src/feaana.cpp

funclib.o : src/funclib.cpp ./include/*
	g++ -c -I ./include src/funclib.cpp

spliter.o : src/spliter.cpp ./include/*
	g++ -c -I ./include -I ../exception/include src/spliter.cpp

test.o : test/test.cpp ./include/*
	g++ -c -I ./include test/test.cpp

lib: $(objects)
	ar cqs libfeaana.a $(objects)

clean:
	rm $(objects) test.o feaana *.a
