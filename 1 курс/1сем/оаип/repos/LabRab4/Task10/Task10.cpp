#include <iostream>

int main()
{
	long long int n, i, j, k, l, size_n;
	const int size_max = 40;
	int a[size_max]{ 0 }, b[size_max]{ 0 }, c[size_max]{ 0 }, mult[size_max]{0}, sum[size_max]{ 0 }, p;
	const long long int max_n = 9223372036854775807; //2^64-1
	// sum = 42535295865117307919086767873688862722
	 
	std::cin >> n;
	if ((n > 1) && (n <= max_n))
	{
		i = 0;
		k = n;

		// в массиве a[] лежит число n
		while (k > 0)
		{
			a[i] = k % 10;
			i = i + 1;
			k = k / 10;
		}
		size_n = i;

		// в массиве b[] лежит число n - 1
		p = 1;
		if (a[0] >= 1)
		{
			b[0] = a[0] - 1;
			for (i = 1; i < size_n;i++)
			{
				b[i] = a[i];
			}
		}
		else
		{
			i = 0;
			while (a[i] < 1)
			{
				b[i] = 10 * p + a[i] - p;
				i = i + 1;
			}
			b[i] = a[i] - 1;
			i = i + 1;
			for (int j = i; i < size_n;i++)
			{
				b[i] = a[i];
			}
		}

		// n делим на 2, если n - четное
		if (a[0] % 2 == 0)
		{
			i = size_n - 1;
			p = 0;
			while (i >= 0)
			{
				p = p * 10 + a[i];
				if (p == 1)
				{
					p = p * 10 + a[i - 1];
					i = i - 1;
				}

				c[i] = p / 2;
				p = p % 2;
				i = i - 1;
			}
			for (i = size_max - 1; i >= 0; i--)
			{
				a[i] = c[i];
			}
		}

		// (n - 1) делим на 2, если (n - 1) - четное
		if (b[0] % 2 == 0)
		{
			i = size_n - 1;
			p = 0;
			while (i >= 0)
			{
				p = p * 10 + b[i];
				if (p == 1)
				{
					p = p * 10 + b[i - 1];
					i = i - 1;
				}

				c[i] = p / 2;
				p = p % 2;
				i = i - 1;
			}
			for (i = size_max - 1; i >= 0; i--)
			{
				b[i] = c[i];
			}
		}
		
		// умножение
		for (i = 0; i < size_n; i++)
		{
			p = 0;
			for (j = 0; j < size_n; j++)
			{
				mult[j + i] = (a[j] * b[i] + p) % 10;
				p = (a[j] * b[i] + p) / 10;
			}
			if (p > 0)
			{
				mult[j + i ] = p % 10;
				mult[j + i + 1] = p / 10;
			}
						 
			p = 0; l = 0;
			for (j = 0; j < size_max; j++)
			{
				k = sum[j] + mult[j] + p;
				sum[j] = k % 10;
				p = k / 10;
			}
			
			for (j = 0; j < size_max; j++)
			{
			    mult[j] =0;
			}
		}

		// +1
		p = 1;
		for (j = 0; j < size_max; j++)
		{
			k = sum[j] + p;
			sum[j] = k % 10;
			p = k / 10;
		}

		// вывод на печать числа без первых нулей
		i = size_max - 1;
		while (sum[i] == 0)
		{
			i = i - 1;
		}
    	for (j = i; j>=0; j--)
		{
			std::cout << sum[j];
		}
		// std::cout << "\n";

	}
	else
	{
		if ((n == 0) || (n == 1))
		{
			std::cout << 1;
		}
	}

	return 0;
}
