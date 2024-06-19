#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <numeric>
#include <random>
#include <cassert>
#include "cycle.hpp"

#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

class Permutation {
private:
    std::vector<int> val;
    size_t n;
    Permutation extend (size_t m) const;
    static int gcd(int a, int b);
    static int lcm(int a, int b);
    static int lcm_list(const std::list<int>& L);

public:
    /* Constructors. */
    Permutation(const std::vector<int>& u);
    Permutation(const size_t n);
    Permutation(std::istream& input);
    Permutation(size_t n, std::mt19937& g);

    /* Methods. */
    Permutation operator *(const Permutation& s);
    std::list<int> fixedPoints();
    Permutation inverse() const;
    std::list<Cycle> cycles() const;
    int order(const std::list<Cycle>& L) const;
    void printCycles(const std::list<Cycle>& L) const;
    // Permutation without fixed points is a derangement.
    bool is_derangement() {return fixedPoints().empty();};
    template <typename T>
    void permute(std::vector<T>& V) const;

    /* Accessors and Mutators. */
    std::vector<int> getVal() const {return val;};
    int operator()(const int& i) const {return val[i];};
    int& operator()(const int& i) {return val[i];};
    size_t size() const {return n;};
    friend std::ostream& operator <<(std::ostream& o, const Permutation& s);
};

template <typename T>
void Permutation::permute(std::vector<T>& V) const {
    /* Permutes the elements of the vector V. */
    assert(V.size() >= this->n);
    std::vector<T> V_copy(V);
    std::list<Cycle> L = cycles();

    for (const Cycle& c: L) {
        std::list<int> elem = c.getElem();
        int i = elem.front();
        int j = i;
        auto it = elem.begin();
        do {
            V[val[j]] = V_copy[j];
            it++;
            j = *it;
        } while (j != i);
    }

}


#endif