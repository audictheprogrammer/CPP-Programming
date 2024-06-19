#include "perm_matrix.hpp"


PermutationMatrix::PermutationMatrix(const Permutation& p):
    A(p.size(), p.size()), n(p.size()) {
    /* Construct a permutation in sparse Matrix format. */
    for (size_t i = 0; i < p.size(); i++) {
        A.coeffRef(i, p(i)) = 1;
    }
}

PermutationMatrix::PermutationMatrix(const Eigen::SparseMatrix<double>& A):
    A(A), n(A.rows()) {}

PermutationMatrix PermutationMatrix::operator *(const PermutationMatrix& p) {
    /* The product of two PermutationMatrix.
    We have equivalence between these two products:
        (1) sigma1 * sigma2 ie sigma1(sigma2(i))
        (2) mat2 * mat1
    */
    return PermutationMatrix(p.getA() * this->A);
}

PermutationMatrix PermutationMatrix::inverse() const {
    /* Computes the inverse of a permutation. */
    Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
    solver.compute(A);
    Eigen::SparseMatrix<double> I(n, n);
    I.setIdentity();
    auto A_inv = solver.solve(I);
    // std::cout << "Inverse: " << A_inv << std::endl;

    return PermutationMatrix(A_inv);
}


std::ostream& operator <<(std::ostream& o, const PermutationMatrix& p) {
    /* Output stream operator. */
    o << p.getA() << std::endl;
    return o;
}


