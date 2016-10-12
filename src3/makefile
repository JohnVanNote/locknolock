.SILENT :

# program with no lock 
noLock : build
	./a.out 1

# program with lock in for-loop
lockIn : build
	./a.out 2

# program with lock out of for-loop
lockOut : build
	./a.out 3

# compiles
build : csapp.c stadium.c
	gcc -g -lpthread ./stadium.c ./csapp.c

clean :
	\rm *.out
