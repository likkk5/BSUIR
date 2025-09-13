#include <iostream>

int main() {
    for (int i = 1; i <= 3; ++i) {
        std::cout << "Outer loop, iteration " << i << std::endl;
        for (int j = 1; j <= 2; ++j) {
            std::cout << "Inner loop, iteration " << j << std::endl;
            if (j == 2) {
                std::cout << "Condition inside inner loop" << std::endl;
            }
        }
    }
    return 0;
}
