#include "permutation.hpp"
#include "cycle.hpp"
#include <Eigen/Sparse>
#include <Eigen/SparseLU>

class PermutationMatrix {
private:
    Eigen::SparseMatrix<double> A;
    size_t n;

public:
    PermutationMatrix(const Permutation& p);
    PermutationMatrix(const Eigen::SparseMatrix<double>& A);

    PermutationMatrix operator*(const PermutationMatrix& p);
    PermutationMatrix inverse() const;
    Eigen::SparseMatrix<double> getA() const {return A;};
    friend std::ostream& operator <<(std::ostream& o, const PermutationMatrix& p);
};