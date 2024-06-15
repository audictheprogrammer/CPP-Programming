#include <iostream>
#include <vector>
#include <list>

#ifndef PERMUTATION_HPP
#define PERMUTATION_HPP

class Permutation {
private:
    std::vector<int> val;
    size_t n;

public:
    /* Constructors. */
    Permutation(const std::vector<int>& u);
    Permutation(const size_t n);
    Permutation(std::istream& input);

    /* Methods. */
    Permutation operator *(const Permutation& s);
    std::list<int> fixedPoints();
    Permutation inverse() const;

    /* Accessors. */
    std::vector<int> getVal() const {return val;};
    size_t size() const {return n;}; 

};

std::ostream& operator <<(std::ostream& o, const Permutation& s);

#endif