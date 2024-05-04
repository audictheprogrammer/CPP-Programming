#include <iostream>
#include "Matrix.hpp"
#include <cassert>
#include <string>


bool isEqual(const MatrixDouble& A, const MatrixDouble& B) {
    double eps = 1e-6;
    size_t N = A.rows();
    size_t M = A.cols();
    assert(N == B.rows());
    assert(M == B.cols());

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            if (std::abs(A(i, j) - B(i, j)) > eps) {
                return false;
            }
        }
    }
    return true;
}

bool isEqual(const SparseMatrixDouble& A, const SparseMatrixDouble& B) {
    SparseMatrixDouble copyB = B;
    double eps = 1e-6;
    size_t N = A.rows();
    size_t M = A.cols();
    assert(N == B.rows());
    assert(M == B.cols());

    for (int k = 0; k < A.outerSize(); ++k) {
        for (Eigen::SparseMatrix<double>::InnerIterator it(A, k); it; ++it) {
            size_t row = it.row();
            size_t col = it.col();
            double val = it.value();
            if (std::abs(copyB.coeffRef(row, col) - val) > eps) {
                return false;
            }
        }
    }
    return true;
}

bool checkPowerOnDenseMatrices() {
    /* Checking if both power operators are valid.
    Using only on dense matrices. */
    MatrixDouble A(3, 3);
    A(0, 0) = 0.4;
    A(0, 1) = 0.6;
    A(1, 0) = 0.75;
    A(1, 1) = 0.25;
    A(2, 2) = 1;
    MatrixDouble B(3, 3);
    MatrixDouble C(3, 3);

    // TEST 1: To the power of 0.
    B = power(A, 0);
    C = powerV2(A, 0);
    MatrixDouble Id = MatrixDouble::Identity(A.rows(), A.cols());
    assert(isEqual(B, Id));
    assert(isEqual(C, Id));

    // TEST 2: To the power of 1.
    B = power(A, 1);
    C = powerV2(A, 1);
    assert(isEqual(B, A));
    assert(isEqual(C, A));

    // TEST 3: To the power of 100.
    B = power(A, 100);
    C = powerV2(A, 100);
    MatrixDouble R(3, 3);
    R(0, 0) = 0.555556;
    R(0, 1) = 0.444444;
    R(1, 0) = 0.555556;
    R(1, 1) = 0.444444;
    R(2, 2) = 1;

    assert(isEqual(B, R));
    assert(isEqual(C, R));

    std::cout << "All tests on sparse matrices succesfully passed." << std::endl;
    return true;
}

bool checkPowerOnSparseMatrices() {
    /* Checking if both power operators are valid.
    Using only on sparse matrices. */
    SparseMatrixDouble A(3, 3);
    A.coeffRef(0, 0) = 0.4;
    A.coeffRef(0, 1) = 0.6;
    A.coeffRef(1, 0) = 0.75;
    A.coeffRef(1, 1) = 0.25;
    A.coeffRef(2, 2) = 1;
    SparseMatrixDouble B(3, 3);
    SparseMatrixDouble C(3, 3);

    // TEST 1: To the power of 0.
    B = power(A, 0);
    C = powerV2(A, 0);
    SparseMatrixDouble Id(3, 3);
    Id.setIdentity();
    assert(isEqual(B, Id));
    assert(isEqual(C, Id));

    // TEST 2: To the power of 1.
    B = power(A, 1);
    C = powerV2(A, 1);
    assert(isEqual(B, A));
    assert(isEqual(C, A));

    // TEST 3: To the power of 100.
    B = power(A, 100);
    C = powerV2(A, 100);
    SparseMatrixDouble R(3, 3);
    R.coeffRef(0, 0) = 0.555556;
    R.coeffRef(0, 1) = 0.444444;
    R.coeffRef(1, 0) = 0.555556;
    R.coeffRef(1, 1) = 0.444444;
    R.coeffRef(2, 2) = 1;

    assert(isEqual(B, R));
    assert(isEqual(C, R));

    std::cout << "All tests on dense matrices succesfully passed." << std::endl;
    return true;
}


void benchmark(const std::string& filename) {
    MatrixDouble largeMatrix = readDenseMatrix("matrix.dat");
    SparseMatrixDouble sparseLargeMatrix = readSparseMatrix("matrix.dat");

    /* Benchmarking the performance of the naive power operator. */
    auto t1 = std::chrono::system_clock::now();
    MatrixDouble B = power(largeMatrix, 10000);
    auto t2 = std::chrono::system_clock::now();
    std::chrono::duration<double> denseNaiveTime = t2-t1;
    std::cout << "DenseMatrix Naive Power: " << denseNaiveTime.count() << " (s)." << std::endl;

    /* Benchmarking the performance of the optimized power operator. */
    auto t3 = std::chrono::system_clock::now();
    MatrixDouble C = powerV2(largeMatrix, 10000);
    auto t4 = std::chrono::system_clock::now();
    std::chrono::duration<double> denseOptimizedTime = t4-t3;
    std::cout << "DenseMatrix Opt Power: " << denseOptimizedTime.count() << " (s)." << std::endl;

    /* Benchmarking the performance of the naive power operator
    on sparse matrices. */
    auto t5 = std::chrono::system_clock::now();
    SparseMatrixDouble D = power(sparseLargeMatrix, 10000);
    auto t6 = std::chrono::system_clock::now();
    std::chrono::duration<double> sparseNaiveTime = t6-t5;
    std::cout << "SparseMatrix Naive Power: " << sparseNaiveTime.count() << " (s)." << std::endl;

    /* Benchmarking the performance of the optimized power
    operator on sparse matrices. */
    auto t7 = std::chrono::system_clock::now();
    SparseMatrixDouble E = power(sparseLargeMatrix, 10000);
    auto t8 = std::chrono::system_clock::now();
    std::chrono::duration<double> sparseOptimizedTime = t8-t7;
    std::cout << "SparseMatrix Opt Power: " << sparseOptimizedTime.count() << " (s)." << std::endl;

    return ;
}


int main() {

    checkPowerOnDenseMatrices();
    checkPowerOnSparseMatrices();

    benchmark("matrix.dat");

}
