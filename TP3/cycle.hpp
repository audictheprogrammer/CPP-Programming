#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>

#ifndef CYCLE_HPP
#define CYCLE_HPP



class Cycle {
private:
    std::list<int> elem;

public:
    Cycle(const std::list<int>& L);
    int order() const;
    friend bool operator <(const Cycle& a, const Cycle& b);
    friend std::ostream& operator <<(std::ostream& o, const Cycle& c);
};

#endif