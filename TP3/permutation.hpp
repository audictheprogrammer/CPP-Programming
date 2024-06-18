#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <numeric>
#include "cycle.hpp"

#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

class Permutation {
private:
    std::vector<int> val;
    size_t n;
    Permutation extend (int m) const;
    static int gcd(int a, int b);
    static int lcm(int a, int b);
    static int lcm_list(const std::list<int>& L);

public:
    /* Constructors. */
    Permutation(const std::vector<int>& u);
    Permutation(const size_t n);
    Permutation(std::istream& input);

    /* Methods. */
    Permutation operator *(const Permutation& s);
    std::list<int> fixedPoints();
    Permutation inverse() const;
    std::list<Cycle> cycles() const;
    int order(const std::list<Cycle>& L) const;
    void printCycles(const std::list<Cycle>& L) const;

    /* Accessors and Mutators. */
    std::vector<int> getVal() const {return val;};
    int operator()(const int& i) const {return val[i];};
    int& operator()(const int& i) {return val[i];};
    size_t size() const {return n;};
    friend std::ostream& operator <<(std::ostream& o, const Permutation& s);
};

#endif