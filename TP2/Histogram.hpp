#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <vector>

#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
        MatrixDouble;


class Histogram {
private:
    double a, b; // We consider the interval: [a, b].
    int M; // Number of sub-intervals.
    int n; // Number of matrix to generate.
    int N; // Size of each matrix.
    std::mt19937_64 gen; // Random number generator.
    std::vector<double> hist;

public:
    Histogram(const double a, const double b,
         const int M, const int n, const int N, const std::mt19937_64& gen);
    void generateRandomGOEAndIncrementHistogram();
    void compute();
    void write(const std::string& filename);
};





#endif
