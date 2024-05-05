#include "Histogram.hpp"


Histogram::Histogram(const double a, const double b,
     const int M, const int n, const int N, const std::mt19937_64& gen)
     :a(a), b(b), M(M), n(n), N(N), gen(gen), hist(M, 0.) {
    /* Constructs a histogram.
    a, b: We consider the interval [a, b].
    M: The number of sub-intervals.
    n: The number of matrix to generate.
    N: Size of each matrix.
    gen: The random number generator.
    */
 }

void Histogram::generateRandomGOEAndIncrementHistogram() {
    /* Generates a GOE matrix, computes its eigenvalues, and updates the Histogram. */

    std::uniform_real_distribution<double> uniform_distribution(-3, 3);
    std::normal_distribution<double> normal_distribution(0., 1.);

    // Generating the GOE matrix: Gaussian Orthogonal Ensemble.
    MatrixDouble A(N, N);
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            if (i == j) {
                A(i, j) = normal_distribution(gen);
            } else if (i < j) {
                A(i, j) = 2 * normal_distribution(gen);
            } else {
                A(i, j) = A(j, i);
            }
        }
    }

    // Computing its eigenvalues.
    Eigen::EigenSolver<MatrixDouble> Solver(A);
    auto spectrum = Solver.eigenvalues();

    for (auto eigval: spectrum.real()) {
        double normalized_eigval = eigval / (2.0 * std::sqrt(N));

        // Finding the index of corresponding sub-interval.
        int index = -1;
        for (size_t k = 0; k < M; k++) {
            double left = a + k*(b-a)/M;
            double right = a + (k+1)*(b-a)/M;
            if ((left <= normalized_eigval) && (normalized_eigval < right)) {
                index = k;
                break;
            }
        }

        // If we found an index, fill the histogram.
        if (index != -1) {
            hist[index] += 1. / (N * M);
        }

    }

}


void Histogram::compute() {
    /* Repeat N times the experiment. */
    for (size_t i = 0; i < n; i++) {
        generateRandomGOEAndIncrementHistogram();
    }
}


void Histogram::write(const std::string& filename) {
    /* Writes histogram data to a file. */
    std::ofstream F(filename);
    for (size_t i = 0; i < hist.size(); i++) {
        double left = a + i*(b-a)/M;
        double right = a + (i+1)*(b-a)/M;
        F << (left+right)/2 << "\t" << hist[i] << std::endl;
    }
    F.close();
}
