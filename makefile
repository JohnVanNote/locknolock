.SILENT :

noLock : build
	./a.out 1

lockIn : build
	./a.out 2

lockOut : build
	./a.out 3

build : csapp.c stadium.c
	gcc -g -lpthread ./stadium.c ./csapp.c
