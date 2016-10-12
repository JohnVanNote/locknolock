.SILENT:

# makes the stadium simulation without a lock
noLock: noLockBuild
	./a.out

# makes the stadium simulation with lock inside for-loop
inLoop : inLoopLockBuild
	./a.out

# makes the stadium simulation with lock outside for-loop
outLoop : outLoopLockBuild
	./a.out

noLockBuild: noLock.c csapp.c
	gcc -g -lpthread noLock.c csapp.c

inLoopLockBuild : inLoopLock.c csapp.c
	gcc -g -lpthread inLoopLock.c csapp.c

outLoopLockBuild : outLoopLock.c csapp.c
	gcc -g -lpthread outLoopLock.c csapp.c

clean:
	\rm *.out
