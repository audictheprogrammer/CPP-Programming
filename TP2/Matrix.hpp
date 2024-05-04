#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <fstream>
#include <chrono>

#ifndef MATRIX_HPP
#define MATRIX_HPP

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
        MatrixDouble;

typedef Eigen::Matrix<double, Eigen::Dynamic, 1>
        VectorDouble;

typedef Eigen::SparseMatrix<double>
        SparseMatrixDouble;

MatrixDouble power(const MatrixDouble &M, int n);
MatrixDouble powerV2(const MatrixDouble &M, int n);
SparseMatrixDouble power(const SparseMatrixDouble &M, int n);
SparseMatrixDouble powerV2(const SparseMatrixDouble &M, int n);
MatrixDouble readDenseMatrix(const std::string filename);
SparseMatrixDouble readSparseMatrix(const std::string filename);

#endif
