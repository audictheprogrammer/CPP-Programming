#include "polynomial.hpp"
#include <iostream>
#include <vector>
#include <complex>

int main() {
    // Part 1.
    std::cout << "\n";
    std::cout << "#############################################" << std::endl;
    std::cout << "########## Testing Basic features ###########" << std::endl;
    std::cout << "#############################################" << std::endl;
    std::cout << "\n";
    Polynomial<double> q;
    std::cout << "Degree of q: " << q.degree() << std::endl;

    std::vector<int> v1 = {6, 3, 0, 1, 5};
    Polynomial<int> p1(v1);

    std::vector<int> v2 = {1, 0, 1};
    Polynomial<int> p2(v2);

    std::complex<double> a(2.0, 1.0);
    std::complex<double> b(0.0, 1.0);
    std::vector<std::complex<double>> vc = {a, b};

    Polynomial<std::complex<double>> pc(vc);

    std::complex<int> one = 1;
    std::cout << "Is one one: " << is_one(one) << std::endl;
    std::cout << is_zero(a) << std::endl;
    printMonomial(std::cout, a, 3);
    std::cout << std::endl;

    std::cout << "p1: " << p1 << std::endl;

    // Part 2.
    // Sum, difference, product
    std::cout << "\n";
    std::cout << "#############################################" << std::endl;
    std::cout << "########### Testing Sum Diff Prod ###########" << std::endl;
    std::cout << "#############################################" << std::endl;
    std::cout << "\n";
    Polynomial<int> sum = p1 + p2;
    Polynomial<int> diff = p1 - p2;
    Polynomial<int> prod = p1 * p2;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << diff << std::endl;
    std::cout << "Product: " << prod << std::endl;

    // Division and remainder
    std::cout << "\n";
    std::cout << "#############################################" << std::endl;
    std::cout << "####### Testing Division and remainder ######" << std::endl;
    std::cout << "#############################################" << std::endl;
    std::cout << "\n";
    std::vector<int> V1 = {-4, 0, -2, 1};
    std::vector<int> V2 = {-3, 1};
    Polynomial<int> P1(V1);
    Polynomial<int> P2(V2);
    Polynomial<int> div = P1 / P2;
    Polynomial<int> remainder = P1 % P2;
    std::cout << "Quotient: " << div << std::endl;
    std::cout << "Remainder: " << remainder << std::endl;

    // Evaluation at a point
    std::cout << "\n";
    std::cout << "#############################################" << std::endl;
    std::cout << "####### Testing Evaluation at a point #######" << std::endl;
    std::cout << "#############################################" << std::endl;
    std::cout << "\n";
    std::cout << "P1(7.): " << P1(7.) << std::endl;
    std::cout << "P2(7.): " << P2(7.) << std::endl;
    std::cout << "p1(7.): " << p1(7.) << std::endl;
    std::cout << "p2(7.): " << p2(7.) << std::endl;

    // Evaluation using monomials
    std::cout << "\n";
    std::cout << "#############################################" << std::endl;
    std::cout << "##### Testing Evaluation using monomials ####" << std::endl;
    std::cout << "#############################################" << std::endl;
    std::cout << "\n";
    P1.computeMonomials();
    P2.computeMonomials();
    p1.computeMonomials();
    p2.computeMonomials();
    std::cout << "P1(7.): " << P1(7.) << std::endl;
    std::cout << "P2(7.): " << P2(7.) << std::endl;
    std::cout << "p1(7.): " << p1(7.) << std::endl;
    std::cout << "p2(7.): " << p2(7.) << std::endl;
    
    return 0;
}
