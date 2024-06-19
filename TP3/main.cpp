#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include "permutation.hpp"
#include "cycle.hpp"
#include "../TP1/Ex3.cpp"
#include "perm_matrix.hpp"

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
    std::cout << "This permutation has: " << L.size() <<
    " cycles, with the longest being of size: " <<
    (*std::max_element(L.begin(), L.end())).order() << std::endl;
    // Here it's using the '<' operator.
    // Part 3.
    std::mt19937 g(time(nullptr));
    unsigned n = 100;
    unsigned nb_echant = 10000;
    unsigned nb_derang = 0;
    for (unsigned i = 0; i < nb_echant; i++) {
        nb_derang += Permutation(n, g).is_derangement();
    }
    std::cout << "The ratio of derangements is approximately: "
        << nb_derang/double(nb_echant) << std::endl;

    // Part 4: Custom.
    std::vector<double> V = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0};
    a.permute(V);
    std::cout << "The vector V permuted by a gives: \n";
    for (size_t i = 0; i < V.size(); i++) {
        std::cout << V[i] << "\t";
    }
    std::cout << std::endl;

    std::vector<PersonInfo> personsInfo;
    std::ifstream file("../TP1/smalldata.txt");

    std::string name;
    std::string city;
    int age;
    double time;
        while (file >> name >> city >> age >> time) {
        PersonInfo p = {name, city, age, time};
        personsInfo.push_back(p);
    }
    file.close();

    // Initial statistics.
    Answers A1 = analysis(personsInfo);
    writeAnswers(A1, "Analysis.txt");

    // for (const PersonInfo p: personsInfo) {
    //     if (p.name[0] == 'P' && p.name[1] == 'a')
    //         std::cout << "Name: " << p.name << std::endl;
    // }
    // std::cout << std::endl;
    
    // Permuted statistics, should not modify the analysis.
    Permutation random_permutation(personsInfo.size(), g);
    random_permutation.permute(personsInfo);

    Answers A2 = analysis(personsInfo);
    writeAnswers(A2, "Analysis2.txt");

    // for (const PersonInfo p: personsInfo) {
    //     if (p.name[0] == 'P' && p.name[1] == 'a')
    //         std::cout << "Name: " << p.name << std::endl;
    // }
    // std::cout << std::endl;

    // Part 5: Comparing permutation format:
    // Sparse Matrix format and vector format.
    // Permutation perm_vect1(4, g);
    // Permutation perm_vect2(4, g);
    Permutation perm_vect1(1000000, g);
    Permutation perm_vect2(1000000, g);
    auto t1 = std::chrono::system_clock::now();
    Permutation res_vect1 = perm_vect1 * perm_vect2;
    auto t2 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = t2-t1;

    PermutationMatrix res_mat1(res_vect1);

    // Create sparse permmutation.
    PermutationMatrix perm_mat1(perm_vect1);
    PermutationMatrix perm_mat2(perm_vect2);

    auto t3 = std::chrono::system_clock::now();
    PermutationMatrix res_mat2 = perm_mat1 * perm_mat2;
    auto t4 = std::chrono::system_clock::now();
    std::chrono::duration<double> diff2 = t4-t3;
    std::cout << "Benchmarking both permutation formats." << std::endl;
    std::cout << "Vector format: " << diff.count() << "s." << std::endl;
    std::cout << "Matrix format: " << diff2.count() << "s." << std::endl;
    // Vector format is so much faster.

    // std::cout << "P1: \n" << perm_vect1 << std::endl;
    // std::cout << "P2: \n" << perm_vect2 << std::endl;
    // std::cout << "Res 1: \n" << res_mat1 << std::endl;
    // std::cout << "Res 2: \n" << res_mat2 << std::endl;
    // std::cout << PermutationMatrix(res_vect1.inverse()) << std::endl;
    // std::cout << res_mat1.inverse() << std::endl;

    return 0;
}