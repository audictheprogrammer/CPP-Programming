#include "Histogram.hpp"

int main() {
    std::mt19937_64 gen(time(NULL));

    // Initialize the histogram.
    std::cout << "Step 1." << std::endl;
    int M = 20; // Number of sub-intervals.
    int n = 20; // Number of matrices.
    int N = 150; // Size of each matrix.
    Histogram hist(-3, 3, M, n, N, gen);

    // Simulating the experiments.
    std::cout << "Step 2." << std::endl;
    hist.compute();

    std::cout << "Step 3." << std::endl;
    // Showing the results.
    hist.write("eigenvalues2.dat");
    // We can compare eigenvalues2.dat and eigenvalue.dat which is an correct example.

    return 0;
}
