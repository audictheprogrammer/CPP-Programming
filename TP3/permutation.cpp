#include "permutation.hpp"

/* Constructors. */
Permutation::Permutation(const std::vector<int>& u): val(u), n(u.size()) {}

Permutation::Permutation(const size_t n) {
    /*  Identity permutation. */
    val.resize(n);
    this->n = n;
    for (size_t i = 0; i < this->n; i++) {
        val[i] = i;
    }
}

Permutation::Permutation(std::istream& input) {
    /* Loads a permutation from an input stream. */
    size_t n;
    input >> n;
    Permutation res(n);

    size_t v;
    for (size_t i = 0; i < n; i++) {
        input >> v;
        assert(v >= 0 && v < n);
    }
    std::cout << "Permutation of size " << n << " loaded." << std::endl;
}

Permutation::Permutation(size_t n, std::mt19937& g) {
    /* Construct a random permutation. 
    Time Complexity: O(n). 
    */
    this->n = n;
    this->val.resize(n);
    for (size_t i = 0; i < n; i++) {
        this->val[i] = i;
    }

    /* Version 1: Using std::swap. */
    // for (size_t i = 0; i < n-1; i++) {
    //     std::uniform_int_distribution<int> distribution(i, n-1);
    //     int j = distribution(g);
    //     std::swap(val[i], val[j]);
    // }

    /* Version 2: Using std::shuffle. */
    std::shuffle(val.begin(), val.end(), g);
}


/* Methods. */
Permutation Permutation::extend(size_t m) const{
    /* Extension of the current permutation by 
    adding new fixed points. */
    if (m <= n) return *this;

    std::vector<int> res = val;
    res.resize(m);
    for (size_t i = n; i < m; i++) {
        res[i] = i;
    }

    return Permutation(res);
}

Permutation Permutation::operator*(const Permutation& s) {
    /* Composition of permutation. 
    Performs extension of permutation if needed. 
    Time Complexity: O(N).
    */
    size_t N = std::max(this->n, s.n);
    Permutation A = this->extend(N);
    Permutation B = s.extend(N);
    std::vector<int> res(N);
    for (size_t i = 0; i < N; i++) {
        res[i] = A(B(i));
    }

    return Permutation(res);
}

std::list<int> Permutation::fixedPoints() {
    /* Returns the fixed points of a permutation. */
    std::list<int> res;
    for (size_t i = 0; i < n; i++){
        if (val[i] == (int) i) res.push_back(i);
    }

    return res;
}

Permutation Permutation::inverse() const {
    /* Computes the inverse of the current permutation. 
    Time Complexity: O(n).
    */
    Permutation res(n);
    for (size_t i = 0; i < n; i++) {
        res(val[i]) = i;
    }

    return res;
}

std::list<Cycle> Permutation::cycles() const{
    /* Uses the following property: Any permutation in Sn can be
    written as a product of disjoint cycles.
    Time Complexity: O(n).
    */
    std::list<Cycle> L; // Cycles.
    std::set<int> S;
    for (size_t i = 0 ; i < n; i++) {
        S.insert(i);
    }

    while (S.size() != 0) {        
        int i = *S.begin();
        std::list<int> elem; // Cycle.
        int j = i; 
        do {
            S.erase(j);
            elem.push_back(j);
            j = val[j];
        } while (j != i);
        L.push_back(elem);
    }

    return L;
}

int Permutation::order(const std::list<Cycle>& L) const {
    /* Computes the order of a permutation. 
    Converts the list of cycles to a list of order.
    */
    std::list<int> O;
    std::for_each(L.begin(), L.end(), [&O] (Cycle c) {O.push_back(c.order());});
    return lcm_list(O);
}

void Permutation::printCycles(const std::list<Cycle>& L) const {
    /* Prints the cycles. */
    std::cout << "Permutation in cycle format: " << std::endl;
    for (Cycle c: L) {
        std::cout << c;
    }
    std::cout << std::endl;
}


// Static methods.
int Permutation::gcd(int a, int b) {
    /* Computes the gcd of two numbers. */
    if (b == 0) return a;
    int r = a % b;
    return gcd(b, r);
}

int Permutation::lcm(int a, int b) {
    /* Computes the lcm of two numbers. */
    return a*b / gcd(a, b);
}

int Permutation::lcm_list(const std::list<int>& L) {
    /* Computes the lcm of a list of numbers. */
    return std::accumulate(L.begin(), L.end(), 1, lcm);
}

std::ostream& operator <<(std::ostream& o, const Permutation& s) {
    /* Output stream operator. */
    for (auto it = s.val.begin(); it != s.val.end(); it++) {
        o << *it << "\t";
    }
    o << "\n";
    return o;
}