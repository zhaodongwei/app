all : configure lib
.PHONY: all

objects = root.o trunk.o branch.o item.o array_root.o array_item.o configure.o conf_struct.o conf_node.o

configure : test.o lib
	g++ -o configure test.o libconfigure.a ../exception/libexception.a

test.o : test/test.cpp src/configure.cpp include/*
	g++ -I ../exception/include -I ./include -c test/test.cpp

configure.o : src/configure.cpp include/*
	g++ -I ../exception/include -I ./include -c src/configure.cpp 

conf_struct.o : src/conf_struct.cpp include/*
	g++ -I ../exception/include -I ./include -c src/conf_struct.cpp

conf_node.o : src/conf_node.cpp ./include/*
	g++ -I ../exception/include -I ./include -c src/conf_node.cpp

root.o : src/root.cpp ./include/*
	g++ -I ../exception/include -I ./include -c src/root.cpp

trunk.o : src/trunk.cpp ./include/*
	g++ -I ../exception/include -I ./include -c src/trunk.cpp

branch.o : src/branch.cpp ./include/*
	g++ -I ../exception/include -I ./include -c src/branch.cpp

item.o : src/item.cpp ./include/*
	g++ -I ../exception/include -I ./include -c src/item.cpp

array_root.o : src/array_root.cpp ./include/*
	g++ -I ../exception/include -I ./include -c src/array_root.cpp

array_item.o : src/array_item.cpp ./include/*
	g++ -I ../exception/include -I ./include -c src/array_item.cpp

lib : $(objects)
	ar cqs libconfigure.a $(objects)

clean:
	rm test.o $(objects) configure libconfigure.a




