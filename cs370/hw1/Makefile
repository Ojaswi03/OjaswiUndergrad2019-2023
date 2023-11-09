Initiator: Initiator.o Worker.o
	g++ Initiator.o Worker.o -o Initiator

Initiator.o: Initiator.c
	g++ -c Initiator.c

Worker.o: Worker.c
	g++ -c Worker.c

tar:
	tar -cvzf Ojaswi-Sinha-HW1.tar *.c *.h *.txt Makefile
clean:
	rm -f $(out.exe) *.o *.tar

