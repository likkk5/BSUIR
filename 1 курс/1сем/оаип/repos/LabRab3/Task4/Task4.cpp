#include <iostream>

int main()
{
    int sum = 0, n, i;
    setlocale(LC_ALL, "rus");
    std::cout << "Введите n = ";
    std::cin >> n;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Incorrect input";
        return 0;
    }
    std::cout << "Выберите способ вычисления: 1 - с использованием цикла; 2 - без использования цикла " << "\n";
    std::cin >> i;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Incorrect input";
        return 0;
    }
            if (n > 0)
            {
                switch (i)
                {
                case 1:
                    // с использованием цикла
                    for (int i = 1;i < n; i++)
                    {
                        if (i % 2 == 0)
                        {
                            sum = sum + i;
                        }
                    }
                    std::cout << sum;
                    break;

                case 2:
                    // без использования цикла
                    if ((n - 1) % 2 == 0)
                    {
                        sum = ((n - 1) / 2) * ((n - 1) / 2 + 1);
                    }
                    else 
                    {
                        sum = ((n - 2) / 2) * ((n - 2) / 2 + 1);
                    }
                    std::cout << sum;
                    break;
                default:
                    std::cout << "Incorrect input";
                    break;
                }
            }
            
            else
            {
                std::cout << "Incorrect input";
            }
    
    return 0;
}