#include "PCA.hpp"
#include <numeric>
#include <algorithm>


PCA::PCA(const MatrixDouble& M): data(M), eigenvalues(M.rows()), eigenvectors(M.rows(), M.cols()) {

}


PCA::PCA(const std::string& filename) {
    std::ifstream F(filename);
    size_t p, n;
    F >> p;
    F >> n;
    data.resize(p, n);
    for (size_t i = 0; i < p; i++) {
        for (size_t j = 0; j < n; j++) {
            F >> (this->data)(i, j);
        }
    }
    eigenvalues.resize(p);
    eigenvectors.resize(p, p);
    F.close();
}

MatrixDouble PCA::centerData() {
    MatrixDouble M = this->data;
    MatrixDouble res(M.rows(), M.cols());
    for (size_t i = 0; i < M.rows(); i++) {
        for (size_t j = 0; j < M.cols(); j++) {
            double sumOfMi = std::accumulate(M.row(i).begin(), M.row(i).end(), 0., [](double acc, double val) {
                return acc + val;
            });
            res(i, j) = M(i, j) - sumOfMi / M.row(i).size();
        }
    }

    return res;
}


void PCA::compute(const MatrixDouble& M) {
    /* Computes the eigenvalues and eigenvectors of the covariance matrix M * M^T./ */
    MatrixDouble Sigma = M * M.transpose();
    Eigen::SelfAdjointEigenSolver<MatrixDouble> S(Sigma);
    this->eigenvalues = S.eigenvalues();
    this->eigenvectors = S.eigenvectors();

    return ;
}


int PCA::dimension(double alpha) {
    /* Returns the smallest d such that:
        alpha * sum_{i=1}^{p} eig_val <= sum_{i=1}^{d} eig_val.
    In other words, we're  trying to keep as much as possible information while reducing the dimension.
    */
    int p = this->eigenvalues.size();
    VectorDouble reversedEigenvalues(p);
    for (int i = 0; i < p; i++) {
        reversedEigenvalues[p-i-1] = this->eigenvalues(i);
    }
    double lhs = alpha * std::accumulate(reversedEigenvalues.begin(), reversedEigenvalues.end(), 0.);

    double partialSum[p];
    std::partial_sum(reversedEigenvalues.begin(), reversedEigenvalues.end(), partialSum);

    for (int d = 0; d < p; d++) {
        if (lhs <= partialSum[d]) {
            return d+1;
        }
    }


    return -1;
}
