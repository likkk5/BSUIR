#include <iostream>

int main()
{
	int  n, m, j, i, k;
	long double a[100][100], b[100][100], c[100][100];

	std::cin >> n;
	for (i = 0; i <= n - 1; i++)
		for (j = 0;j <= n - 1; j++)
			std::cin >> a[i][j];

	std::cin >> m;
	for (i = 0; i <= m - 1; i++)
		for (j = 0;j <= m - 1; j++)
			std::cin >> b[i][j];
	
	if (n == m)
	{
		for (i = 0; i <= n - 1; i++)
			for (j = 0;j <= n - 1; j++)
			{
				c[i][j] = 0;
				for (k = 0; k <= n - 1; k++)
				{
					c[i][j] = c[i][j] + a[i][k] * b[k][j];
				}
				if (j != n - 1)
				{
					std::cout << c[i][j] << " ";
				}
				else
				{
					std::cout << c[i][j] << "\n";
				}
			}
		
	}
	return 0;
}