#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (int rowIndex = 0; rowIndex < matrix.size(); ++rowIndex) {
        std::cout << "Row " << rowIndex << ":" << std::endl;
        for (int colIndex = 0; colIndex < matrix[rowIndex].size(); ++colIndex) {
            int element = matrix[rowIndex][colIndex];
            std::cout << "Element [" << rowIndex << "][" << colIndex << "]: " << element << std::endl;

            switch (element) {
                case 1:
                    std::cout << "This is number one" << std::endl;
                    if (element % 2 == 0) {
                        std::cout << "This is an even number" << std::endl;
                    } else {
                        std::cout << "This is an odd number" << std::endl;
                    }
                    break;
                case 2:
                    std::cout << "This is number two" << std::endl;
                    if (element % 2 == 0) {
                        std::cout << "This is an even number" << std::endl;
                    } else {
                        std::cout << "This is an odd number" << std::endl;
                    }
                    break;
                case 3:
                    std::cout << "This is number three" << std::endl;
                    if (element % 2 == 0) {
                        std::cout << "This is an even number" << std::endl;
                    } else {
                        std::cout << "This is an odd number" << std::endl;
                        if (element % 3 == 0) {
                            std::cout << "This number is divisible by 3" << std::endl;
                            if (element % 5 == 0) {
                                std::cout << "This number is divisible by 5" << std::endl;
                            } else {
                                std::cout << "This number is not divisible by 5" << std::endl;
                            }
                        } else {
                            std::cout << "This number is not divisible by 3" << std::endl;
                        }
                    }
                    break;
                case 4:
                    std::cout << "This is number four" << std::endl;
                    if (element % 2 == 0) {
                        std::cout << "This is an even number" << std::endl;
                    } else {
                        std::cout << "This is an odd number" << std::endl;
                    }
                    break;
                case 5:
                    std::cout << "This is number five" << std::endl;
                    if (element % 2 == 0) {
                        std::cout << "This is an even number" << std::endl;
                    } else {
                        std::cout << "This is an odd number" << std::endl;
                        if (element % 3 == 0) {
                            std::cout << "This number is divisible by 3" << std::endl;
                            if (element % 5 == 0) {
                                std::cout << "This number is divisible by 5" << std::endl;
                            } else {
                                std::cout << "This number is not divisible by 5" << std::endl;
                            }
                        } else {
                            std::cout << "This number is not divisible by 3" << std::endl;
                        }
                    }
                    break;
                case 6:
                    std::cout << "This is number six" << std::endl;
                    if (element % 2 == 0) {
                        std::cout << "This is an even number" << std::endl;
                        if (element % 3 == 0) {
                            std::cout << "This number is divisible by 3" << std::endl;
                            if (element % 5 == 0) {
                                std::cout << "This number is divisible by 5" << std::endl;
                            } else {
                                std::cout << "This number is not divisible by 5" << std::endl;
                            }
                        } else {
                            std::cout << "This number is not divisible by 3" << std::endl;
                        }
                    } else {
                        std::cout << "This is an odd number" << std::endl;
                    }
                    break;
                case 7:
                    std::cout << "This is number seven" << std::endl;
                    if (element % 2 == 0) {
                        std::cout << "This is an even number" << std::endl;
                    } else {
                        std::cout << "This is an odd number" << std::endl;
                    }
                    break;
                case 8:
                    std::cout << "This is number eight" << std::endl;
                    if (element % 2 == 0) {
                        std::cout << "This is an even number" << std::endl;
                        if (element % 4 == 0) {
                            std::cout << "This number is divisible by 4" << std::endl;
                            if (element % 8 == 0) {
                                std::cout << "This number is divisible by 8" << std::endl;
                            } else {
                                std::cout << "This number is not divisible by 8" << std::endl;
                            }
                        } else {
                            std::cout << "This number is not divisible by 4" << std::endl;
                        }
                    } else {
                        std::cout << "This is an odd number" << std::endl;
                    }
                    break;
                case 9:
                    std::cout << "This is number nine" << std::endl;
                    if (element % 2 == 0) {
                        std::cout << "This is an even number" << std::endl;
                    } else {
                        std::cout << "This is an odd number" << std::endl;
                        if (element % 3 == 0) {
                            std::cout << "This number is divisible by 3" << std::endl;
                            if (element % 9 == 0) {
                                std::cout << "This number is divisible by 9" << std::endl;
                                if (element < 10) {
                                    std::cout << "This number less than 10" << std::endl;
                                    if (element > 5) {
                                        std::cout << "This number greater than 5" << std::endl;
                                    } else {
                                        std::cout << "This number less than 5" << std::endl;
                                    }
                                } else {
                                    std::cout << "This number greater than 10" << std::endl;
                                }
                            } else {
                                std::cout << "This number is not divisible by 9" << std::endl;
                            }
                        } else {
                            std::cout << "This number is not divisible by 3" << std::endl;
                        }
                    }
                    break;
            }
        }
    }

    return 0;
}
