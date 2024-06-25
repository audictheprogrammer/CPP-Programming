#include <iostream>
#include <complex>
#include <cassert>
#include <algorithm>
#include <vector>
#include <type_traits>

template<typename T>
class Polynomial;

template <typename T>
Polynomial<T> operator +(const Polynomial<T>& P, const Polynomial<T>& Q);

template <typename T>
Polynomial<T> operator -(const Polynomial<T>& P, const Polynomial<T>& Q);

template <typename T>
Polynomial<T> operator *(const Polynomial<T>& P, const Polynomial<T>& Q);

template <typename T>
std::pair<Polynomial<T>, Polynomial<T>> euclid_div(const Polynomial<T>& P, const Polynomial<T>& Q);

template <typename T>
Polynomial<T> operator /(const Polynomial<T>& P, const Polynomial<T>& Q);

template <typename T>
Polynomial<T> operator %(const Polynomial<T>& P, const Polynomial<T>& Q);

template <typename T>
void adjust(Polynomial<T>& P); // Adjust Polynomial size.

// External functions.
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
bool is_invertible(const Polynomial<T>& P) {
    if (P.degree() == -1) {
        return false;
    }

    T x = P[P.degree()];
    if (std::is_integral<decltype(x)>::value) { // Is it integer type ?
        return x == 1 || x == -1;
    }
    return is_zero(x);
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
    (std::is_same<T, std::complex<double>>::value) ? o << coeff << "*z^" << n: o << coeff << "*x^" << n;

    return o;
}


/* ********************************************
************** CLASS: POLYNOMIAL **************
********************************************* */

template <typename T>
class Polynomial {
private:
    std::vector<T> values;
    int n;
    friend void adjust<>(Polynomial<T>& P); // Adjust Polynomial size.

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

    friend Polynomial<T> operator +<>(const Polynomial<T>& P, const Polynomial<T>& Q);
    friend Polynomial<T> operator -<>(const Polynomial<T>& P, const Polynomial<T>& Q);
    friend Polynomial<T> operator *<>(const Polynomial<T>& P, const Polynomial<T>& Q);

    friend std::ostream& operator<<(std::ostream& o, const Polynomial<T>& P) {
        if (P.n == -1) {
            return o;
        }
        for (int i = 0; i < P.n; i++) {
            if (!is_zero(P[i])) {
                printMonomial(o, P[i], i);
                o << " + ";
            }
        }
        printMonomial(o, P[P.n], P.n);
        return o;
    }


};

template <typename T>
void adjust(Polynomial<T>& P) {
    /* Adjust the size of the polynomial.
    Time Complexity: O(n).
    */
    int i = P.n;
    while (i >= 0) {
        if (!is_zero(P[i])) {
            P.values.resize(i+1);
            P.n = i;
            return ;
        }
        i--;
    }

    P.values.resize(0);
    P.n = -1;
    return ;
}


/* Arithmetics operators. */
template <typename T>
Polynomial<T> operator +(const Polynomial<T>& P, const Polynomial<T>& Q){
    /* Sum of two polynomials. */
    std::vector<T> r_values(std::max(P.n, Q.n) + 1, T(0));

    for (int i = 0; i <= P.n; i++) {
        r_values[i] += P[i];        
    }
    for (int i = 0; i <= Q.n; i++) {
        r_values[i] += Q[i];        
    }

    Polynomial<T> R(r_values);
    adjust(R);
    return R;
}

template <typename T>
Polynomial<T> operator -(const Polynomial<T>& P, const Polynomial<T>& Q){
    /* Difference of two polynomials. */
    std::vector<T> r_values(std::max(P.n, Q.n) + 1, T(0));
    for (int i = 0; i <= P.n; i++) {
        r_values[i] += P[i];        
    }
    for (int i = 0; i <= Q.n; i++) {
        r_values[i] -= Q[i];        
    }

    Polynomial<T> R(r_values);
    adjust(R);
    return R;
}

template <typename T>
Polynomial<T> operator *(const Polynomial<T>& P, const Polynomial<T>& Q){
    /* Product of two polynomials. */
    std::vector<T> r_values(P.n + Q.n + 1, T(0));

    for (int i = 0; i <= P.n; i++) {
        for (int j = 0; j <= Q.n; j++) {
            r_values[i+j] += P[i]*Q[j];
        }
    }

    Polynomial<T> R(r_values);
    return R;
}

template <typename T>
std::pair<Polynomial<T>, Polynomial<T>> euclid_div(const Polynomial<T>& A, const Polynomial<T>& B){
    /* Euclidean division of two polynomials. */
    if (!is_invertible(B)) {
        return std::make_pair(Polynomial<T>{}, A);
    }
    if (A.degree() < B.degree()) {
        return euclid_div(B, A);
    }

    Polynomial<T> R(A);
    Polynomial<T> Q {};
    while (R.degree() >= B.degree()) {
        // Get the degree.
        int deg = R.degree() - B.degree();
        // Get the coefficient.
        T coeff = R[R.degree()] / B[B.degree()];
        // Construct the Q monomial.
        Polynomial<T> monomialQ(coeff, deg);
        Q = Q + monomialQ;
        R = R - monomialQ*B;
    }

    return std::make_pair(R, Q);
}

template <typename T>
Polynomial<T> operator /(const Polynomial<T>& P, const Polynomial<T>& Q) {
    /* Division of polynomial P by polynomial Q and returns the quotient. */
    if (Q.degree() > P.degree()) {
        std::cout << "P / Q changed to Q / P." << std::endl;
    }
    auto pair = euclid_div(P, Q);
    return pair.second;
}


template <typename T>
Polynomial<T> operator %(const Polynomial<T>& P, const Polynomial<T>& Q) {
    /* Modulo of polynomial P by polynomial Q and returns the remainder. */
    if (Q.degree() > P.degree()) {
        std::cout << "P mod Q changed to Q mod P." << std::endl;
        return Q % P;
    }

    auto pair = euclid_div(P, Q);
    return pair.first;
}


