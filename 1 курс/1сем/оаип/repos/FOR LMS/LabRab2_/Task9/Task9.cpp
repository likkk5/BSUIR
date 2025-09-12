#include <iostream>
#include <cmath>

int main() //13
{
	long double y, n, x, k, m, z, f;
	int i;
	setlocale(LC_ALL, "russian");
	std::cout << "1: f(x) = 2*x" << "\n";
	std::cout << "2: f(x) = x^3" << "\n";
	std::cout << "3: f(x) = x/3" << "\n";
	std::cout << "Выберите функцию:";
	std::cin >> i;
	if ((i == 1) || (i == 2) || (i == 3))
	{
		std::cout << "Введите n=";
		std::cin >> n;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}
		
		std::cout << "Введите k=";
		std::cin >> k;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}

		std::cout << "Введите m=";
		std::cin >> m;
		if (std::cin.fail() || std::cin.peek() != '\n' )
		{
			std::cout << "некорректный ввод";
			return 0;
		}
		if (m<=0)
		{
			std::cout << "недопустимое значение m";
			return 0;
		}


		std::cout << "Введите z=";
		std::cin >> z;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}

		if (z > 1)
		{
			x = z;
		}
		else
		{
			x = z * z + 1;
		}
		std::cout << "x = " << x << "\n";

		switch (i)
		{
			case 1:
				f = 2 * x;
				std::cout << "f(x) = 2*x" << "\n";
				break;
			case 2:
				f = x * x * x;
				std::cout << "f(x) = x^3" << "\n";
				break;
			case 3:
				f = x / 3;
				std::cout << "f(x) = x/3" << "\n";
				break;
		}
			
		y = sin(int(n * f)) + cos(k * x) + log(m * x);
		std::cout << "y = " << y;
	}
	else
	{
		std::cout << "f(x) не выбрана" << "\n";
	}
	return 0;
}