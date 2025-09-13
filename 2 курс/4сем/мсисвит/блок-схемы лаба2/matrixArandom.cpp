#include <iostream>
#include <vector>
#include <random>

int main() {
    // Creating a two-dimensional matrix
    std::vector<std::vector<int>> matrixA = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    // Generating random numbers and filling the matrix with them
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9); // Generating a random number from 0 to 9

    for (int rowIndex = 0; rowIndex < matrixA.size(); ++rowIndex) {
        for (int colIndex = 0; colIndex < matrixA[rowIndex].size(); ++colIndex) {
            matrixA[rowIndex][colIndex] = dis(gen);
        }
    }

    // Displaying the matrix
    std::cout << "Generated matrix:" << std::endl;
    for (const auto& row : matrixA) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
