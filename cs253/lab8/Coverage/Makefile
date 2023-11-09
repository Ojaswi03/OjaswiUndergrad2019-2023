CXXFLAGS=-Wall -Werror -Wfatal-errors -fprofile-arcs -ftest-coverage

prog: main.o Date.o
	g++ $(CXXFLAGS) -o $@ main.o Date.o

Date.o: Date.cc Date.h
	g++ $(CXXFLAGS) -c Date.cc
	
main.o: main.cc Date.h
	g++ $(CXXFLAGS) -c main.cc
	

clean:
	-rm -f prog *.o *.gcov *.gcda *.gcno
