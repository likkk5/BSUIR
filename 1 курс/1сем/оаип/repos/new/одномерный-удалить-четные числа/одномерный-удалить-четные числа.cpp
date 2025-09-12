// одномерный-удалить-четные числа.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include "stdio.h"
#include "stdlib.h"

int* Input(int* a, int nn)
{
	for (int i = 0; i < nn; i++)
	{
		scanf_s("%d", &a[i]);
	}
	return a;
}

void Print(int* a, int nn)
{
	for (int i = 0; i < nn; i++)
	{
		printf("%3d", a[i]);
	}
	printf("\n");
}

int main() {

	int i, j;

	int n, m;
	scanf_s("%d", &n);

	//выделяем память на массив значений
	int* array = (int*)malloc(sizeof(int) * n);
	
	array = Input(array, n);
	Print(array, n);
	printf("\n");

	for (i = 0; i < n; i++)
	{
		if (array[i] % 2 == 0)
		{
			n--;
			for (j = i; j < n; j++)
				array[j] = array[j + 1];
			array = (int*)realloc(array, sizeof(int) * n);
		}
	}
	Print(array, n);
	printf("\n");
	//free(array);

	return 0;
}