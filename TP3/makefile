all: main

permutation.o: permutation.cpp permutation.hpp
	g++ -c permutation.cpp -Wall
cycle.o: cycle.cpp cycle.hpp
	g++ -c cycle.cpp -Wall
perm_matrix.o: perm_matrix.cpp perm_matrix.hpp
	g++ -c perm_matrix.cpp -I /usr/include/eigen3 -Wall

main: main.cpp permutation.o cycle.o perm_matrix.o
	g++ -o main main.cpp permutation.o cycle.o perm_matrix.o -I /usr/include/eigen3 -O3 -Wall

clean:
	rm -rf *.o main