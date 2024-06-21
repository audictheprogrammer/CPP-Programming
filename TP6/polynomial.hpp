#include <iostream>
#include <complex>
#include <cassert>
#include <algorithm>
#include <vector>
#include <type_traits>


template <typename T>
bool is_zero(const T a) {
    double eps = 1e-6;
    return std::abs(a) < eps;
}

template <typename T>
bool is_one(const T a) {
    double eps = 1e-6;
    return std::abs(a - 1) < eps;
}

template <typename T>
bool is_zero(const std::complex<T> a) {
    double eps = 1e-6;
    return std::abs(a.real()) < eps && std::abs(a.imag()) < eps;
}

template <typename T>
bool is_one(const std::complex<T> a) {
    double eps = 1e-6;
    return std::abs(a.real() - 1) < eps && std::abs(a.imag()) < eps;
}


template <typename T>
std::ostream& printMonomial(std::ostream& o, T coeff, int n) {
    /* Print a monomial.
    Examples: 7*x^2, -5*x.
    */
    if (n == -1 || is_zero(coeff)) {
        return o;
    }
    if (n == 0) {
        o << coeff;
        return o;
    }
    if (n == 1) {
        (std::is_same<T, std::complex<double>>::value) ? o << coeff << "*z": o << coeff << "*x";
        return o;
    }
    // o << coeff << "*x^" << n;
    (std::is_same<T, std::complex<double>>::value) ? o << coeff << "*z^" << n: o << coeff << "*x^" << n;

    return o;
}


template <typename T>
class Polynomial {
private:
    std::vector<T> values;
    int n;

public:
    /* Constructors. */
    Polynomial(): values(), n(-1) {};
    Polynomial(T a, int m): values(m+1, 0), n(m) {
        /* Monomial: a x^m. */
        assert(!is_zero(a));
        values[m] = a;
    }
    Polynomial(const std::vector<T>& values): values(values), n(values.size()-1) {}

    /* Methods. */
    int degree() const {return n;};

    T operator [](int i) const {
        assert(0 <= i && i <= degree());
        return values[i];
    }


    friend std::ostream& operator<<(std::ostream& o, const Polynomial<T>& P) {
        for (int i = 0; i < P.n; i++) {
            if (!is_zero(P[i])) {
                printMonomial(o, P[i], i);
                o << " + ";
            }
        }
        printMonomial(o, P[P.n], P.n+1);
        return o;
    }


};

