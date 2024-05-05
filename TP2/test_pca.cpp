#include <string>
#include <ctime>
#include "Matrix.hpp"
#include "PCA.hpp"


bool isEqual(MatrixDouble& A, MatrixDouble& B) {
    // Checks if two matrices A and B are approximately equal.
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
    /* Checks if constructors of PCA are valid:
    - Constructor via a MatrixDouble.
    - Constructor via a filename.
    */

    // Simple example to check the first constructor.
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


void checkMethods() {
    /* Check if the following methods are valid:
    - centerData()
    - compute()
    - dimension()
    */
    PCA pca("iris.dat");
    MatrixDouble centeredMatrix = pca.centerData();
    pca.compute(centeredMatrix);

    VectorDouble IrisEigenvalues = pca.getValues();
    MatrixDouble IrisEigenvectors = pca.getVectors();

    std::cout << "Largest Eigenvalue: " << std::endl;
    // std::cout << IrisEigenvalues[4] << std::endl << std::endl;
    assert(std::abs(IrisEigenvalues[4] - 720.42) <= 0.1);

    int d = pca.dimension(0.98);
    // std::cout << "Alpha = 0.98 => Dimension = " << d << std::endl;
    assert(d == 3);

    std::cout << "All tests on methods succesfully passed." << std::endl;
}


int main() {
    checkConstructors();

    checkMethods();

    // Generating gaussian distribution cloud points.
    int n = 10000;
    std::vector<double> param = {1, 3, 2, 10, 0, M_PI/6};
    std::mt19937 gen(time(nullptr));
    GaussianScatter gaussian(n, param, gen);
    MatrixDouble data = gaussian.getData();

    // Applying Principal Component Analysis.
    PCA pca(data);
    MatrixDouble centeredMatrix = pca.centerData();
    pca.compute(centeredMatrix);

    // The first eigenvector should be orthogonal to [sin(theta), -cos(theta)].
    VectorDouble v1 = pca.getVectors().col(0);
    VectorDouble ans(2);
    ans(0) = sin(param[5]);
    ans(1) = -cos(param[5]);

    double dotResult = v1.dot(ans);
    std::cout << "<v1, ans> = " << dotResult << std::endl;
    assert(std::abs(dotResult) <= 0.1);

    int d = pca.dimension(0.98);
    std::cout << "Alpha = 0.98 => Dimension = " << d << std::endl;


    return 0;
}
