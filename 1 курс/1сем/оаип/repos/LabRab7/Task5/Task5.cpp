#include <iostream>
#include <string>


int Interesting(int nn)
{
    return (nn + 1) / 10;
}

int main()
{
    setlocale(LC_ALL, "rus");
    int t, i, n;

    std::cin >> t;
    if ((t >= 1) && (t <= 1000))
    {
        for (i = 0; i < t; i++)
        {
            std::cin >> n;
            if ((n >= 1) && (n <= 1000000000))
            {
                std::cout << Interesting(n) << "\n" << "\n";
            }
        }
    }
    return 0;
}
