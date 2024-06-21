#include "polynomial.hpp"
#include <iostream>
#include <vector>
#include <complex>

int main() {
    // Part 1.
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
    // Polynomial<int> sum = p1 + p2;
    // Polynomial<int> diff = p1 - p2;
    // Polynomial<int> prod = p1 * p2;
    // std::cout << "Sum: " << sum << std::endl;
    // std::cout << "Difference: " << diff << std::endl;
    // std::cout << "Product: " << prod << std::endl;

    // // Division and remainder
    // Polynomial<int> div = p1 / p2;
    // Polynomial<int> remainder = p1 % p2;
    // std::cout << "Quotient: " << div << std::endl;
    // std::cout << "Remainder: " << remainder << std::endl;

    // // Evaluation at a point
    // std::cout << "p1(2): " << p1(2) << std::endl;

    return 0;
}
