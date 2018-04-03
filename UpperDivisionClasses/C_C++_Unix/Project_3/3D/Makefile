SRC=main3D.C image.C sink.C source.C PNMreaderCPP.C PNMwriterCPP.C filters.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3D

.C.o: $<
	g++ -I. -c $<

clean:
	rm *.o proj3D
