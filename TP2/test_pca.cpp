#include <string>
#include "Matrix.hpp"
#include "PCA.hpp"


bool isEqual(MatrixDouble& A, MatrixDouble& B) {
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


void checkConstructors() {
    /* Check if constructors of PCA are valid. */

    // Simple example to check the first construtor.
    MatrixDouble A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;

    PCA PCA_A(A);
    MatrixDouble PCA_A_Data = PCA_A.getData();
    assert(isEqual(PCA_A_Data, A));

    // Loading the Iris dataset using the second constructor.
    MatrixDouble Iris = readDenseMatrix("iris_formatted.dat");

    PCA PCA_Iris("iris.dat");
    MatrixDouble PCA_Iris_Data = PCA_Iris.getData();
    assert(isEqual(PCA_Iris_Data, Iris));

    std::cout << "All tests on constructors succesfully passed." << std::endl;
}

int main() {
    checkConstructors();

    PCA pca("iris.dat");
    MatrixDouble centeredMatrix = pca.centerData();
    pca.compute(centeredMatrix);

    VectorDouble IrisEigenvalues = pca.getValues();
    MatrixDouble IrisEigenvectors = pca.getVectors();

    std::cout << "Eigenvalues: " << std::endl;
    std::cout << IrisEigenvalues << std::endl;

    return 0;
}
