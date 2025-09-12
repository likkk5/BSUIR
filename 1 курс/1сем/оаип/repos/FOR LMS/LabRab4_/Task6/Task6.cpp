#include <iostream>
#include <string>

int main()
{
	std::string n = "";
	long long l;
	unsigned short j, m, k = 0;
	unsigned int a[65535]{}, i, g;

	std::cin >> n;
	std::cin >> i;

	l = n.length();
	i = n[i - 1] - 48;


	if ((l > 0) && (l <= 65535))
	{
		for (j = 0; j <= l - 1; j++)
		{
			a[l - 1 - j] = n[j] - 48;
		}

		for (g = 0; g <= 9; g++)
		{
			m = 0;
			for (j = 0; j <= l - 1; j++)
				if (a[j] == g)
				{
					m = m + 1;
				}

			if (m > 0)
			{
				k = k + 1;
			}
		}
		std::cout << k << "\n";

		for (j = 0; j <= l - 1; j++)
			if (a[j] == i)
			{
				std::cout << j << " ";
			}

	}
	return 0;
}
