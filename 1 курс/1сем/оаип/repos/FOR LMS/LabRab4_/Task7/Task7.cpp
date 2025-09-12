#include <iostream>
#include <string>
#include <cstring>
#include <fstream>


int main()
{
	std::string n = "";
	std::string n1 = "";
	long long i, j, m, n_len, max = 0, max_i = 0, min = 0, min_i = 0;
	long long a[1000];

	getline(std::cin, n);
	n_len = n.length();

	j = 0;
	for (i = 0;i <= n_len;i++)
	{
		if (n[i] != ' ')
		{
			n1 = n1 + n[i];
		}
		else
		{
			a[j] = std::stoi(n1);
			j = j + 1;
			n1 = "";
		}
	}

	a[j] = std::stoi(n1);
	m = j;

	for (i = 0; i <= m;i++)
		if (max < a[i])
		{
			max = a[i];
			max_i = i;
		}

	for (i = 0; i <= m;i++)
		if (min > a[i])
		{
			min = a[i];
			min_i = i;
		}

	if (min_i < max_i)
		for (i = min_i + 1; i < max_i; i++)
			a[i] = 0;

	if (min_i > max_i)
		for (i = max_i + 1; i < min_i; i++)
			a[i] = 0;


	j = 0;
	for (i = 0; i <= m;i++)
		if (a[i] == 0)
			j = j + 1;

	if (j > (m / 2))
	{
		for (i = 0; i <= m;i++)
			if (a[i] != 0)
			{
				std::cout << a[i] << " ";
			}
	}
	else
	{
		for (i = 0; i <= m;i++)
			std::cout << a[i] << " ";
	}

	return 0;
}
