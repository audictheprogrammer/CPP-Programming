#include <iostream>
#include <vector>
#include <fstream>


int main() {
    size_t n;

    std::cout << "Please input a number smaller than 100:" << std::endl;
    std::cin >> n;
    std::vector<int> squaredValues(n);
    std::vector<int> cubedValues(n);
    for (size_t i = 0; i < n; i++) {
        squaredValues[i] = i*i;
        cubedValues[i] = i*i*i;
    }

    std::ofstream file("Squares_Cubes.txt");
    file << "Here are the first squares to " << n << std::endl;
    for (size_t i = 0; i < n; i++) {
        file << i << ": " << squaredValues[i] << ", " << cubedValues[i] << std::endl;
    }

    file.close();
    return 0;
}
