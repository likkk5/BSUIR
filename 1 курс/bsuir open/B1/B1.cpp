#include <iostream>
#include <iomanip>

int main()
{
    long m, n, k;
    double l, a, b, a1, b1, step;

    std::cin >> n >> m >> k;

    l = sqrt(double(n * m) / double(k));
    a = m / l;
    a1 = 1 + int(a);
    b = n / l;
    b1 = 1 + int(b);

    step = l / 1000000;
    while (((a1 - a) > 0.000001) && ((b1 - b) > 0.000001))
    {
        l = l - step;
        a = m / l;
        b = n / l;
    }

    std::cout << std::fixed << std::setprecision(1) << l << std::endl;
    //std::cout << l << std::endl;
    return 0;
}