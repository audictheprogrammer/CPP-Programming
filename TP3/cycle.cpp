#include "cycle.hpp"

Cycle::Cycle(const std::list<int>& L): elem(L) {};

int Cycle::order() const {
    /* Computes the order of the cycle. */
    return elem.size();
}

bool operator < (const Cycle& a, const Cycle& b) {
    /* Cycle-comparing operator.
    True: a has a smaller order than b. */
    if (a.order() < b.order()) return true;
    if (a.order() > b.order()) return false;

    return std::lexicographical_compare(a.elem.begin(), a.elem.end(),
                                        b.elem.begin(), b.elem.end());
    
}

std::ostream& operator <<(std::ostream& o, const Cycle& c) {
    /* Output stream operator. */
    for (int i: c.elem) {
        o << i << "\t";
    }
    o << std::endl;
    return o;
}



