// матрица-удалить-добавить.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include "stdio.h"
#include "stdlib.h"

int** Input(int** a, int nn, int mm)
{
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < mm;j++)
		{
			scanf_s("%d", &a[i][j]);
		}
	}
	return a;
}

void Print(int** a, int nn, int mm)
{
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < mm;j++)
		{
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
}

int main() {

	int i, j;
	
	int n, m;
	scanf_s("%d", &n);
	scanf_s("%d", &m);
	
	//выделяем память на массив массивов
	int** array = (int**)malloc(sizeof(int*) * n);
	// выделяем память на массив значений
	for (i = 0; i < m; i++) {
		array[i] = (int*)malloc(sizeof(int) * m);
	}
	
	array = Input(array, n, m);
	Print(array, n, m);
	printf("\n");

	int countMod2 = m / 2;
	m -= countMod2; // новое количество столбцов в матрице после удаления четных столбцов

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < countMod2; j++)
		{
			array[i][j + 1] = array[i][j * 2 + 2];
		}
		array[i] = (int*)realloc(array[i], sizeof(int) * m);
	}
	Print(array,n, m);
	printf("\n");

	m++;
	for (i = 0; i < n; i++)
	{
		array[i] = (int*)realloc(array[i], sizeof(int) * (m));

		if (!array[i]) {
			printf("Invalid reallocate");
			exit(1);
		}
		array[i][m - 1] = 0;
	}
	Print(array, n, m);

	printf("\n");

	//free(array);

	return 0;
}