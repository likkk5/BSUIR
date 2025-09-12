#include <iostream>
#include <iomanip>
#include <cmath>

long double min(double a, double b)
{
    return a < b ? a : b;
}

int main() // k>0, k<0
{
    long double k, x, y, d;
    std::cin >> k;
    std::cin >> x;
    std::cin >> y;

    if (k > 0)
    {
        if ((x >= 0) && (x <= k))
        {
            if (y > k)
            {
                d = y - k;
                std::cout << std::setprecision(22) << d;
            }
            if ((y >= 0) && (y <= k))
            {
                d = min(min(x, y), min(k - x, k - y));
                std::cout << std::setprecision(22) << d;
            }
            if (y < 0)
            {
                d = fabsl(y);
                std::cout << std::setprecision(22) << d;
            }
        }

        if (x >= k)
        {
            if (y < 0)
            {
                d = sqrtl((x - k) * (x - k) + y * y);
                std::cout << std::setprecision(22) << d;
            }
            if ((y >= 0) && (y < k))
            {
                d = x - k;
                std::cout << std::setprecision(22) << d;
            }
            if (y >= k)
            {
                d = sqrtl((x - k) * (x - k) + (y - k) * (y - k));
                std::cout << std::setprecision(22) << d;
            }
        }

        if (x <= 0)
        {
            if (y <= 0)
            {
                d = sqrtl(x * x + y * y);
                std::cout << std::setprecision(22) << d;
            }
            if ((y > 0) && (y <= k))
            {
                d = fabsl(x);
                std::cout << std::setprecision(22) << d;
            }
            if (y > k)
            {
                d = sqrtl(x * x + (y - k) * (y - k));
                std::cout << std::setprecision(22) << d;
            }
        }
    }

    if (k < 0)
    {
        if ((x <= 0) && (x >= k))
        {
            if (y < k)
            {
                d = k - y;
                std::cout << std::setprecision(22) << d;
            }
            if ((y <= 0) && (y >= k))
            {
                d = min(min(fabsl(x), fabsl(y)), min(x - k, y - k));
                std::cout << std::setprecision(22) << d;
            }
            if (y > 0)
            {
                d = y;
                std::cout << std::setprecision(22) << d;
            }
        }

        if (x <= k)
        {
            if (y > 0)
            {
                d = sqrtl((k - x) * (k - x) + y * y);
                std::cout << std::setprecision(22) << d;
            }
            if ((y <= 0) && (y > k))
            {
                d = k - x;
                std::cout << std::setprecision(22) << d;
            }
            if (y <= k)
            {
                d = sqrtl((k - x) * (k - x) + (k - y) * (k - y));
                std::cout << std::setprecision(22) << d;
            }
        }

        if (x >= 0)
        {
            if (y >= 0)
            {
                d = sqrtl(x * x + y * y);
                std::cout << std::setprecision(22) << d;
            }
            if ((y < 0) && (y >= k))
            {
                d = x;
                std::cout << std::setprecision(22) << d;
            }
            if (y < k)
            {
                d = sqrtl(x * x + (k - y) * (k - y));
                std::cout << std::setprecision(22) << d;
            }
        }
    }
    return 0;
}