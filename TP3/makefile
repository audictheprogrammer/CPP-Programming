all: main

permutation.o: permutation.cpp permutation.hpp
	g++ -c permutation.cpp
cycle.o: cycle.cpp cycle.hpp
	g++ -c cycle.cpp

main: main.cpp permutation.o cycle.o
	g++ -o main main.cpp permutation.o cycle.o

clean:
	rm -rf *.o main