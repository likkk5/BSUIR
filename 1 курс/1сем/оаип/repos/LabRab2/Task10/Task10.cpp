#include <iostream>

int main()
{
    long double x1, y1, r, x2, y2, R, d;
    setlocale(LC_ALL, "russian");
    std::cout << "x1=", x1;
    std::cin >> x1;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Некорректный ввод";
        return 0;
    }

    std::cout << "y1=", y1;
    std::cin >> y1;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Некорректный ввод";
        return 0;
    }

    std::cout << "r=", r;
    std::cin >> r;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Некорректный ввод";
        return 0;
    }

    std::cout << "x2=", x2;
    std::cin >> x2;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Некорректный ввод";
        return 0;
    }

    std::cout << "y2=", y2;
    std::cin >> y2;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Некорректный ввод";
        return 0;
    }

    std::cout << "R=", R;
    std::cin >> R;
    if (std::cin.fail() || std::cin.peek() != '\n')
    {
        std::cout << "Некорректный ввод";
        return 0;
    }
   

    d = sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
            
    if ((R > 0) && (r > 0))
    {
        if (d + r < R)
        {
            std::cout << "Да";
        }
        else
        {
            if (d + R < r)
            {
                std::cout << "Да, но справедливо обратное для двух фигур";
            }
            else
            {
                if ((r + R >= d) && ((x1 != x2) || (y1 != y2) || (r != R)) && (((d + r) != R) && ((d + R) != r)))
                {
                    std::cout << "Фигуры пересекаются";
                }
                else
                {
                    std::cout << "Ни одно условие не выполнено";
                }
            }
        }
    }
    else
    {
        std::cout << "ERROR";
    }
    return 0;
}