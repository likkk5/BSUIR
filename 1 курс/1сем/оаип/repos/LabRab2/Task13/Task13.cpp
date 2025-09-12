#include <iostream>

int main()
{
    long long k;
    std::cin >> k;
    setlocale(LC_ALL, "russian");
    if ((k % 100 == 11) || (k % 100 == 12) || (k % 100 == 13) || (k % 100 == 14))
    {
        std::cout << "Мы нашли " << k << " грибов в лесу" << "\n";
    }
    else
    {
        if (k % 10 == 1)
        {
            std::cout << "Мы нашли " << k << " гриб в лесу" << "\n";
        }
        if ((k % 10 == 2) || (k % 10 == 3) || (k % 10 == 4))
        {
            std::cout << "Мы нашли " << k << " гриба в лесу" << "\n";
        }
        if ((k % 10 > 4) || (k % 10 == 0))
        {
            std::cout << "Мы нашли " << k << " грибов в лесу" << "\n";
        }
    }
    if (k < 0)
    {
        std::cout << "ERROR" << "\n";
    }
    return 0;
}

   
