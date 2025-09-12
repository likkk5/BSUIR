#include <iostream>

int main()
{
	long long i, j, k, g, n, m, max;
	long long a[100][100];
	long long b[100][100];

	std::cin >> n >> m;

	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
		{
			std::cin >> a[i][j];
		}

	for (k = 1; k <= n; k++)
	{
		for (g = 1; g <= m; g++)
		{
			max = 0;
			for (i = 1; i <= k; i++)
				for (j = 1; j <= g; j++)
					if (max < a[i][j])
					{
						max = a[i][j];
					}
			b[k][g] = max;
		}
	}

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			std::cout << b[i][j] << " ";
		}
		std::cout << "\n";
	}

	return 0;
}
