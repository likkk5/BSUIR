// двумерный массив. Если хотя бы один столбец имеет все отрицательные числа, то все элементы матрицы домножить на -1
#include <iostream>

int** Input(int** a, int nn, int mm)
{
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < mm;j++)
		{
			std::cin >> a[i][j];
		}
	}
	return a;
}

bool CheckNegativeColumn(int** a, int nn, int mm)
{
	bool check = false;
	int count = 0;

	for (int j = 0; j < mm; j++)
	{
		for (int i = 0; i < nn; i++)
		{
			if(a[i][j] < 0)
				count++;
		}
		if (count == nn)
		{
			check = true;
			break;
		}
	}
	return check;
}

int** Mult(int** a, int nn, int mm)
{
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < mm;j++)
		{
			a[i][j] = -a[i][j];
		}
	}
	return a;
}


void Print(int** ar, int nn, int mm)
{
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < mm;j++)
		{
			std::cout << ar[i][j]<<" ";
		}
		std::cout << "\n";
	}
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	int** array;
	array = new int* [n];
	for (int i = 0; i < n; i++)
		array[i] = new int[m];

	array = Input(array, n, m);
	
	if (CheckNegativeColumn(array, n, m))
	{
		std::cout << "Array contains at least one negative column. All matrix elements multiplied by -1 " << "\n";
		array = Mult(array, n, m);
	}
	else
	{
		std::cout << "Array does not contain any negative columns" << "\n";
	}

	Print(array, n, m);

	delete[] array;
	return 0;
}


