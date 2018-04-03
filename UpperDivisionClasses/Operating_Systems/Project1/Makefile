all: thv1
all: thv2
all: thv3
all: thv4
clean:
	rm thv1
	rm thv2
	rm thv3
	rm thv4
	rm -f *.o
thv4: thv4.o p1fxns.o
	cc -g -o thv4 thv4.o p1fxns.o
thv3: thv3.o p1fxns.o
	cc -g -o thv3 thv3.o p1fxns.o
thv2: thv2.o p1fxns.o
	cc -g -o thv2 thv2.o p1fxns.o
thv1: thv1.o p1fxns.o
	cc -g -o thv1 thv1.o p1fxns.o
thv4.o: thv4.c
	gcc -g -W -Wall -c thv4.c
thv3.o: thv3.c
	gcc -g -W -Wall -c thv3.c
thv2.o: thv2.c
	gcc -g -W -Wall -c thv2.c
thv1.o: thv1.c
	gcc -g -W -Wall -c thv1.c
p1fxns.o:
	gcc -g -c p1fxns.c
copy:
	cp Makefile *.c *.h ../uoregon-cis415/Project1
