#include <iostream>
#include <iomanip>

int MinSubArray(int* a, int low, int high)
{
	int min;
	min = *(a + low);
	for (int i = low; i < high; i++)
	{
		if (min > *(a + i))
		{
			min = *(a + i);
		}
	}
	return min;
}

/*int* QuickSortArray(int* a, int low, int high)
{
	int i = low;
	int j = high;
	int mid = a[(low + high) / 2];
	int temp;
	do
	{
		while (a[i] < mid)
		{
			i++;
		}
		while (a[j] > mid)
		{
			j--;
		}
		if (i <= j)
		{
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;
		}
	} while (i < j);

	if (low < j)
	{
		a = QuickSortArray(a, low, j);
	}
	if (low < j)
	{
		a = QuickSortArray(a, i, high);
	}

	return a;
}
*/

int main()
{
	setlocale(LC_ALL, "rus");
	int i, j, n, k, minimum;
	
	std::cin >> n;
	
	int* array = nullptr;
	array = new int[n];

	for (i = 0; i < n; i++)
	{
		std::cin >> *(array + i);
	}
	
	std::cin >>  k;
	if ((k >= 1) && (k <= n))
	{
		for (j = 0; j < n - k + 1; j++)
		{
			minimum = MinSubArray(array, j, j + k - 1);
			std::cout << "В подмассиве [" << j + 1 << "; " << k + j << "]  min = " << minimum << "\n";
		}
	}
	
	delete[] array;
	array = nullptr;

	return 0;
}