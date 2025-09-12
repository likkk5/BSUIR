#include <iostream>
#include <string>

long long function (long long l)
{
    long long m = l %10;
    if (l == 0)
    {
        return 0;
    }
    return m * (1 + m) / 2 + l / 10 * 45 + function(l / 10);
}

long long s(long long pp, long long qq)
{
    return function(qq) - function(pp - 1);
}

int main()
{
    long long p=0, q=0;

    while ((p >= 0) && (q >= 0))
    {
        std::cin >> p >> q;
        if ((p >= 0) && (q >= 0))
        {
            if (p <= q)
            {
                std::cout << s(p, q) << "\n";
            }
        }
    }
    return 0;
}