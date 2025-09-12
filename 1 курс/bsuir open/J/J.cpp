#include <iostream>

long long f(long long a, long long b, long long x)
{
    if (x <= a)
    {
        x = a + 1;
    }
    return x - b + 1;
  
}

int main()
{
    int t;

    long long a, b, x;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cin >> a >> b >> x;
        std::cout << f(a, b, x) << std::endl;
    }
    return 0;
}