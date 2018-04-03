CLI = cli/cli.c
LIB = ./lib
INC = ./include
DEPS = ./lib/cos330.o ./lib/sin330.o ./lib/tan330.o ./lib/exp330.o ./lib/log330.o ./lib/arccos330.o ./lib/arctan330.o ./lib/arcsin330.o

Main:
	mkdir include
	cp math330.h include
	mkdir lib
	gcc -c ./trig/*.c -I $(INC)
	gcc -c ./exp/*.c -I $(INC)
	mv *.o $(LIB)
	ar r libmath.a $(DEPS)
	mv libmath.a $(LIB)
	gcc -I $(INC) -L$(LIB) -lmath $(CLI)
clean:
	rm -rf lib
	rm -rf include
	rm a.out
