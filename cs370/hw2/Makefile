CC = gcc


Initiator: Initiator.o SpecialNumbers.o SequenceNumbers.o Prime.o Square.o Padovan.o Perrin.o
		
Initiator.o: Initiator.c
		gcc -o Initiator Initiator.c

SpecialNumbers.o: SpecialNumbers.c
		gcc -o SpecialNumbers SpecialNumbers.c

SequenceNumbers.o: SequenceNumbers.c
		gcc -o SequenceNumbers SequenceNumbers.c

Prime.o: Prime.c
		gcc -o Prime Prime.c

Square.o: Square.c
		gcc -o Square Square.c

Padovan.o: Padovan.c
		gcc -o Padovan Padovan.c

Perrin.o: Perrin.c
		gcc -o Perrin Perrin.c

tar:
		tar -cvzf Ojaswi-Sinha-HW2.tar *.c *.txt Makefile

clean:
		rm -f $(out.exe) *.o *.tar
