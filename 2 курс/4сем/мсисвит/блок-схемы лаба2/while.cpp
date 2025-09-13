#include <iostream>

int main() {
    int outerCount = 0;
    while (outerCount < 3) {
        std::cout << "Outer iteration " << outerCount << std::endl;
        int innerCount = 0;
        while (innerCount < 2) {
            std::cout << "  Inner iteration " << innerCount << std::endl;
            innerCount++;
        }
        outerCount++;
    }
    return 0;
}
