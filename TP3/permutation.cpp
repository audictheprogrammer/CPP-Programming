#include "permutation.hpp"
#include <assert.h>

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

    int v;
    for (size_t i = 0; i < n; i++) {
        input >> v;
        assert(v >= 0 && v < n);
    }
    std::cout << "Permutation of size " << n << " loaded." << std::endl;
}

Permutation Permutation::operator*(const Permutation& s) {
    /* Composition of permutation. */
    assert(this->n == s.n);
    std::vector<int> res(n);
    for (size_t i = 0; i < n; i++) {
        res[i] = this->val[s.val[i]];
    }
    return Permutation(res);
}

std::list<int> Permutation::fixedPoints() {
    /* Returns the fixed points of a permutation. */
    std::list<int> res;
    for (size_t i = 0; i < n; i++){
        if (val[i] == i) res.push_back(i);
    }

    return res;
}

Permutation Permutation::inverse() const {
    /* Computes the inverse of the current permutation.
    Uses the following property: Any permutation in Sn can be
    written as a product of disjoint cycles.
    Time Complexity: O(n).
    */

    // Part 1: Use the property.
    std::vector<int> visited(n);
    std::list<std::list<int>> cycles;

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        std::list<int> current_cycle;
        int current_elem = i;

        do {
            visited[current_elem] = 1;
            current_cycle.push_back(current_elem);
            current_elem = val[current_elem];
        } while (current_elem != i);

        cycles.push_back(current_cycle);
    }

    // Part 2: Inverse the cycles.
    std::vector<int> res(n);
    for (const auto& cycle: cycles) {
        for (auto it = cycle.rbegin(); it != cycle.rend(); it++) {
            int i = *it;
            int j = (it == std::prev(cycle.rend())) ? *cycle.rbegin() : *std::next(it);
            res[i] = j;
            std::cout << "i, j = (" << i << ", " << j << ")\n";
        }
    }    

    return Permutation(res);
}



std::ostream& operator <<(std::ostream& o, const Permutation& s) {
    /* Output stream operator. */
    const std::vector<int> val = s.getVal();
    for (auto it = val.begin(); it != val.end(); it++) {
        o << *it << "\t";
    }
    o << "\n";
    return o;
}