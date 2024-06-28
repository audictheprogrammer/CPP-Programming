#include <iostream>
#include <cmath>

// Forward declarations
template<typename T>
class Monomial;

template <typename T>
bool operator < (const Monomial<T>& u, const Monomial<T>& v);

template <typename T>
class Monomial {
private:
    int n;
    T coeff;

public:
    Monomial():n(-1) {};
    Monomial(const T& a, int m = 0): n(m), coeff(a) {}; // Monomial: a x^m.

    friend bool operator < <>(const Monomial<T>& u, const Monomial<T>& v);

    T operator () (const T x) const {
        if (n == 0) {
            return coeff;
        }
        return coeff * std::pow(x, n);
    }
    int degree() const {
        return n;
    }
    T coefficient() const {
        return coeff;
    }

};

template <typename T>
bool operator <(const Monomial<T>& u, const Monomial<T>& v) {
    /* Comparison operator. */
    if (u.n < v.n || u.n == v.n && u.coeff < v.coeff) {
        return true;
    }
    return false;
}


