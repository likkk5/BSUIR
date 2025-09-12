#include <iostream>
#include <string>

unsigned long long x(unsigned long long kk, unsigned long long nn, unsigned long long mm)
{
    if (nn == 0)
    {
        return 1;
    }
    if (nn % 2 != 0)
    {
        return (kk * x((kk * kk) % mm, nn / 2, mm)) % mm;
    }
    return x((kk * kk) % mm, nn / 2, mm);
}


int main()
{
    long long k=1, n=1, t=1, i = 1, j, m = 1;

    while ((k > 0) && (k < 1e+19) && (n > 0) && (n < 1e+19) && (t > 0) && (t < 10))
    {
        std::cin >> k >> n >> t;
        if ((k != 0) && (n != 0) && (t != 0))
        {
            m = 1;
            for (j = 1; j <= t; j++)
            {
                m = m * 10;
            }

            
            std::cout << "Case #" << i << ": " << x(k % m, n, m) << "\n";
            i = i + 1;
        }
    }
    return 0;
}