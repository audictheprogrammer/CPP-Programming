all: main

permutation.o: permutation.cpp permutation.hpp
	g++ -c permutation.cpp
main: main.cpp permutation.o
	g++ -o main main.cpp permutation.o

clean:
	rm -rf *.o main