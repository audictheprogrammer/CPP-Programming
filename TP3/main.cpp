#include "permutation.hpp"
#include "cycle.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>

int main() {
    // Part 1.
    std::vector<int> v = {2, 4, 5, 3, 1, 0};
    Permutation a(v); 
    Permutation b(6); // identity
    for (int i = 0; i <= 6; i++) {
        std::cout << "a^" << i << std::endl << b << std::endl;
        b = b * a;
    }
    std::list<int> fp = a.fixedPoints();
    std::cout << "Fixed points:" << std::endl;
    auto affiche = [](int x) {std::cout << x << " ";};
    std::for_each(fp.begin(), fp.end(), affiche);
    std::cout << std::endl << std::endl;

    // Part 2.
    // std::ifstream fichier_s("./file_s.dat");
    // std::ifstream fichier_t("./file_t.dat");
    // Permutation s(fichier_s);
    // Permutation t(fichier_t);
    // fichier_s.close();
    // fichier_t.close();

    Permutation u = a.inverse();
    std::cout << "a^{-1}:" << std::endl;
    std::cout << u << std::endl;
    std::list<Cycle> L = u.cycles();
    std::cout << "Permutation order of (s*t)^-1 is: " << u.order(L) << std::endl;
    u.printCycles(L);
    std::cout << "This permutation has " << L.size() <<
    " cycles, where the longest is of size: " <<
    (*std::max_element(L.begin(), L.end())).order() << std::endl;
    // Here it's using the '<' operator.


    // Part 3.
    
    return 0;
}