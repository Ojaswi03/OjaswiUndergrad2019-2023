CC = gcc


Initiator: Initiator.o Prime.o Reader.o Square.o Padovan.o Perrin.o
		
Initiator.o: Initiator.c
		gcc Initiator.c -o Initiator -lrt

Prime.o: Prime.c
		gcc Prime.c -o Prime -lrt

Reader.o: Reader.c
		gcc Reader.c -o Reader -lrt

Square.o: Square.c
		gcc Square.c -o Square -lrt

Padovan.o: Padovan.c
		gcc Padovan.c -o Padovan -lrt

Perrin.o: Perrin.c
		gcc Perrin.c -o Perrin -lrt

tar:
		tar -cvzf Ojaswi-Sinha-HW3.tar *.c *.txt *.in Makefile

clean:
		rm -f $(out.exe) *.o *.tar 
