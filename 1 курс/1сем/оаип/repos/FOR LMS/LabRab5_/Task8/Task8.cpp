#include <iostream>
#include <string>

unsigned long long summa (long long l)
{
    long long m = (l + 1) / 2;
    if (l == 0)
    { 
        return 0;
    }
    return m * m + summa(l / 2);
}

int main()
{
    long long k, n, j;
    std::cin >> k;
 
    for (j = 0; j < k; j++)
    {
        std::cin >> n;
        std::cout << summa(n) << "\n";
    }
    return 0;
}
