#include <iostream>
//13
int main()
{
	setlocale(LC_ALL, "rus");
	int n,m;
	double x, y, s, h,d;
	std::cout << "Введите количество членов ряда" << "\n";
	std::cin >> n;
	if (std::cin.fail() || std::cin.peek() != '\n')
	{
		std::cout << "Incorrect input";
		return 0;
	}
	std::cout << "Введите количество чисел, от которых надо посчитать функцию" << "\n";
	std::cin >> m;
	if (std::cin.fail() || std::cin.peek() != '\n')
	{
		std::cout << "Incorrect input";
		return 0;
	}
	if ((n > 0) && (m > 0))
	{
		h = (1 - 0.1) / (m - 1);
		for (x = 0.1; x <= 1; x = x + h)
		{
			std::cout << "x=" << x << "\n";
			s = 0;
			d = 1;
			for (int i = 1; i <= n; i++)
			{
				d = d * (1 + x) * (1 + x)*(-1);
				s = s + d / i;
			}
			std::cout << "s(x) = " << s << "\n";
			y = log(1/(2 + 2 * x + x * x));
			std::cout << "y(x) = " << y << "\n";
		}
	}
	else
	{
		std::cout << "Incorrect input";
	}

	return 0;
}