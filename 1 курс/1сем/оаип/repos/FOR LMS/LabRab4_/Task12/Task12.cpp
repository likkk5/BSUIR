#include <iostream>
#include <string>

int main()
{
	unsigned long long n, i, j, k, d;
	unsigned long long a[10 ^ 18];

	std::cin >> n;
	if (n > 0)
	{
		i = 0;

		while (n >= i * i)
		{
			i++;
		}

		if (n == (i - 1) * (i - 1))
		{
			std::cout << i - 2 << " 0";
		}
		else
		{
			j = 1;
			k = 0;
			while (n >= j)
			{
				j = j + 2 * k + 1;
				k = k + 1;
			}

			j = j - (2 * k - 1);

			if (n == j)
			{
				std::cout << "0 " << k - 1;
			}
			else
			{
				d = (i * i + j) / 2;
				if (n == d)
				{
					std::cout << i - 1 << " " << k - 1;
				}
				else
				{
					if (n > d)
					{
						k = i * i - n;
						std::cout << i - 1 << " " << k;
					}
					else
					{
						i = n - j;
						std::cout << i << " " << k - 1;
					}
				}
			}

		}
	}

	return 0;
}