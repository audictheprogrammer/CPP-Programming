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


GaussianScatter::GaussianScatter(int n, const std::vector<double>& param, std::mt19937& gen) {
    /* Constructs a Gaussian scatter in 2D.
    Generates two independant Gaussian random variables.
    param: mu1, mu2, sig1, sig2, rho, theta.
    N_i ~N(mu_i, sig_i).
    rho: coorrelation coefficiant between -1 and 1.
    theta: rotation angle.
    */
    // std::mt19937 gen(time(nullptr));

    double mu1 = param[0];
    double mu2 = param[1];
    double sig1 = param[2];
    double sig2 = param[3];
    double rho = param[4];
    double theta = param[5];

    std::normal_distribution<double> N1(0., 1.);
    std::normal_distribution<double> N2(0., 1.);

    this->data.resize(2, n);
    for (size_t i = 0; i < n; i++) {
        double n1 = mu1 + sig1 * N1(gen);
        double n2 = mu2 + sig2 * N2(gen);
        this->data(0, i) = cos(theta) * n1 - sin(theta) * n2;
        this->data(1, i) = sin(theta) * n1 + cos(theta) * (rho*n1 + (1-rho)*n2);
    }

    // std::cout << this->data << std::endl;

}
