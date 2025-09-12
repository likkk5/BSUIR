#include <iostream>

// остаток от деления на m
int findRemainder(int n, int m)
{
    int x = n & (m-1);
    return x;
}

int main()
{
    int n;
    std::cin >> n;

    std::cout << "remainder of division by 2 is " << findRemainder(n, 2) << "\n";
    std::cout << "remainder of division by 4 is " << findRemainder(n, 4) << "\n";
    
    return 0;
}