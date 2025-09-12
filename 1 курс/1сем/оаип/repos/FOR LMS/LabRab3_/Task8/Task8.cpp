#include <iostream>
#include <cmath>

int main()
{
	setlocale(LC_ALL, "rus");
	unsigned long a, i, n, b, sum;
	int k, j;
	std::cin >> a;

	if ((a > 0) && (a <= pow(10, 8)))
	{
		for (i = 1; i < a; i++)
		{
			sum = 0;
			n = i;
			k = 0;
			while (n != 0)
			{
				n = n / 10;
				k = k + 1;
			}
			n = i;
			while (n != 0)
			{
				b = n % 10;
				n = n / 10;
				sum = sum + pow(b, k);
			}
			if (sum == i)
			{
				std::cout << i << "\n";
			}
		}

	}
	else
	{
		std::cout << "Некорректный ввод";
	}
	return 0;
}
