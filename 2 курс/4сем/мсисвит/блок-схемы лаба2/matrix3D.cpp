#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<std::vector<int>>> matrix3D = {
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        },
        {
            {10, 11, 12},
            {13, 14, 15},
            {16, 17, 18}
        },
        {
            {19, 20, 21},
            {22, 23, 24},
            {25, 26, 27}
        }
    };

    for (int layerIndex = 0; layerIndex < matrix3D.size(); ++layerIndex) {
        std::cout << "Layer " << layerIndex << ":" << std::endl;
        for (int rowIndex = 0; rowIndex < matrix3D[layerIndex].size(); ++rowIndex) {
            std::cout << "  Row " << rowIndex << ":" << std::endl;
            for (int colIndex = 0; colIndex < matrix3D[layerIndex][rowIndex].size(); ++colIndex) {
                std::cout << "    Element [" << layerIndex << "][" << rowIndex << "][" << colIndex << "]: " << matrix3D[layerIndex][rowIndex][colIndex] << std::endl;
            }
        }
    }

    return 0;
}
