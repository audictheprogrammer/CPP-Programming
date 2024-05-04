CXX = g++
CXXFLAGS = -O2
LIB = -I /usr/include/eigen3

all: main test_pca

main: Matrix.o
	$(CXX) $(CXXFLAGS) $(LIB) main.cpp Matrix.o -o main
test_pca: test_pca.cpp Matrix.o PCA.o
	$(CXX) $(CXXFLAGS) $(LIB) test_pca.cpp Matrix.o PCA.o -o test_pca


Matrix.o: Matrix.cpp Matrix.hpp
	$(CXX) $(LIB) -c Matrix.cpp
PCA.o: PCA.cpp PCA.hpp Matrix.hpp
	$(CXX) $(LIB) -c PCA.cpp

clean:
	rm -rf main test_pca *.o
