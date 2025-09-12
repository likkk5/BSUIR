#include <iostream>

int** Input(int** a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n;j++)
		{
			std::cin >> a[i][j];
		}
	}
	return a;
}
void Print(int** ar, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n;j++)
		{
			std::cout << ar[i][j];
		}
	}
}

int main()
{
	int m1, m2;
	std::cin >> m1 >> m2;
	int** array1;
	array1 = new int* [m1];
	for (int i = 0; i < m1; i++)
		array1[i] = new int[m1];

	array1 = Input(array1, m1);

	int** array2;
	array2 = new int* [m2];
	for (int i = 0; i < m2; i++)
		array2[i] = new int[m2];

	array2 = Input(array2, m2);


}

