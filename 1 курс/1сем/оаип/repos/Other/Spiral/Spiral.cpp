#include <iostream>
#include <iomanip>


int main()
{
	int i, j, k, l, n, m;
	int i_centr, j_centr;
	int vert = 1, horiz = 1;
	int min;
	std::cin >> n >> m;

	int* array = nullptr;
	array = new int [n*m];
	
	k = 1;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			*(array +i*m + j) = k;
			std::cout << *(array + i * m + j) << " " << "\n";
			k = k + 1;
		}
	}

	i_centr = n / 2;
	j_centr = m / 2;

	if (n < m)
	{
		min = n;
	}
	else
	{
		min = m;
	}

	i = i_centr = n / 2;
	j = j_centr = m / 2;

	for (k = 0; k < min; k++)
	{
		for (l = 0; l <= k; l++)
		{
			std::cout << *(array + i * m + j) << " ";
			i = i - vert;
		}
		vert = vert * (-1);
		if ((i < 0) || (i >= n))
		{
			break;
		}

		for (l = 0; l <= k; l++)
		{
			std::cout << *(array + i * m + j) << " ";
			j = j + horiz;
		}
		horiz = horiz * (-1);
		if ((j < 0) || (j >= m))
		{
			break;
		}
	}

	// если строк больше, чем столбцов
	l = 1;
	if (n > m)
	{
		while ((i >= 0) && (i < n))
		{
			i = i + min + l;
			if (i < n)
			{
				for (j = m - 1;j >= 0;j--)
				{
					std::cout << *(array + i * m + j) << " ";
				}
				l = l + 1;
			}

			i = i - min - l;
			if (i >= 0)
			{
				for (j = 0;j < m; j++)
				{
					std::cout << *(array + i * m + j) << " ";
				}
				l = l + 1;
			}
		}
	}
	
	// если столбцов больше, чем строк
	l = 0;
	if (n < m)
	{
		while ((j >= 0) && (j < m))
		{
			j = j - min - l;
			if (j >= 0)
			{
				for (i = n - 1;i >= 0; i--)
				{
					std::cout << *(array + i * m + j) << " ";
				}
				l = l + 1;
			}

			j = j + min + l;
			if (j < m)
			{
				for (i = 0; i < n; i++)
				{
					std::cout << *(array + i * m + j) << " ";
				}
				l = l + 1;
			}
		}
	}
	
	delete[] array;
	array = nullptr;

	return 0;
}