#include "Matrix.hpp"


MatrixDouble power(const MatrixDouble &M, int n) {
    /* Compute M to the power of n.
    Time complexity: O(n).
     */
    if (n == 0) {
        return MatrixDouble::Identity(M.rows(), M.cols());
    }
    if (n == 1) {
        return M;
    }
    
    MatrixDouble N(M.rows(), M.cols());
    N = power(M, n-1);
    return M*N;
}

MatrixDouble powerV2(const MatrixDouble &M, int n) {
    /* Compute M to the power of n.
    Time complexity: O(logn).
     */
    if (n == 0) {
        return MatrixDouble::Identity(M.rows(), M.cols());
    }
    if (n %2 == 0) {
        MatrixDouble N(M.rows(), M.cols());
        N = power(M, n/2);
        return N * N;
    }
    MatrixDouble N(M.rows(), M.cols());
    N = power(M, (n-1)/2);
    return M * N * N;
}

SparseMatrixDouble power(const SparseMatrixDouble &M, int n) {
    /* Compute a sparse matrix M to the power of n.
    Time complexity: O(n).
     */
     if (n == 0) {
         SparseMatrixDouble N(M.rows(), M.cols());
         N.setIdentity();
         return N;
     }
     if (n == 1) {
         return M;
     }
     SparseMatrixDouble N(M.rows(), M.cols());
     N = power(M, n-1);
     return M*N;
}

SparseMatrixDouble powerV2(const SparseMatrixDouble &M, int n) {
    /* Compute M to the power of n.
    Time complexity: O(logn).
     */
    if (n == 0) {
        SparseMatrixDouble N (M.rows(), M.cols());
        N.setIdentity();
        return N;
    }
    if (n %2 == 0) {
        SparseMatrixDouble
        N = power(M, n/2);
        return N * N;
    }
    SparseMatrixDouble N(M.rows(), M.cols());
    N = power(M, (n-1)/2);
    return M * N * N;
}

MatrixDouble readDenseMatrix(const std::string filename) {
    std::ifstream file(filename);

    std::vector<std::vector<double>> values;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<double> row;
        double val;
        while (iss >> val) {
            row.push_back(val);
        }
        values.push_back(row);
    }

    file.close();

    MatrixDouble A(values.size(), values[0].size());
    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = 0; j < values[0].size(); j++) {
                A(i, j) = values[i][j];
        }
    }

    return A;
}

SparseMatrixDouble readSparseMatrix(const std::string filename) {
    std::ifstream file(filename);

    std::vector<std::vector<double>> values;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<double> row;
        double val;
        while (iss >> val) {
            row.push_back(val);
        }
        values.push_back(row);
    }

    file.close();

    SparseMatrixDouble A(values.size(), values[0].size());
    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = 0; j < values[0].size(); j++) {
            if (values[i][j] != 0) {
                A.coeffRef(i, j) = values[i][j];
            }
        }
    }

    return A;
}
