#include "Matrix.hpp"
#include <Eigen/Eigenvalues>

#ifndef PCA_HPP
#define PCA_HPP

class PCA {
private:
    MatrixDouble data;
    VectorDouble eigenvalues;
    MatrixDouble eigenvectors;

public:
    /* Constructors. */
    PCA(const MatrixDouble& M);
    PCA(const std::string& F);

    // /* Accessors. */
    // MatrixDouble getData() const {return this->data;};
    // VectorDouble getValues() const {return this->eigenvalues;};
    // MatrixDouble getVectors() const {return this->eigenvectors;};
    // double getValue(int j) const {return this->eigenvalues(j);};

    /* Mutators. */
    MatrixDouble& getData() {return this->data;};
    VectorDouble& getValues() {return this->eigenvalues;};
    MatrixDouble& getVectors() {return this->eigenvectors;};
    double& getValue(int j) {return this->eigenvalues(j);};


    /* Methods. */
    MatrixDouble centerData();
    void compute(const MatrixDouble& M);
    int dimension(double alpha);

};
#endif
