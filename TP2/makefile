CXX = g++
CXXFLAGS = -O2
LIB = -I /usr/include/eigen3

all: main test_pca test_histogram

main: Matrix.o
	$(CXX) $(CXXFLAGS) $(LIB) main.cpp Matrix.o -o main
test_pca: test_pca.cpp Matrix.o PCA.o
	$(CXX) $(CXXFLAGS) $(LIB) test_pca.cpp Matrix.o PCA.o -o test_pca
test_histogram: test_histogram.cpp Histogram.o Matrix.o
	$(CXX) $(CXXFLAGS) $(LIB) test_histogram.cpp Histogram.o Matrix.o -o test_histogram


Matrix.o: Matrix.cpp Matrix.hpp
	$(CXX) $(LIB) -c Matrix.cpp
PCA.o: PCA.cpp PCA.hpp Matrix.hpp
	$(CXX) $(LIB) -c PCA.cpp
Histogram.o: Histogram.cpp Histogram.hpp
	$(CXX) $(LIB) -c Histogram.cpp

clean:
	rm -rf main test_pca test_histogram *.o
