#include <iostream>
#include <string>
using namespace std;

int64_t merge(int n, int *A, int leftBorder, int rightBorder, int64_t result)
{
	int* temp = new int[n];
	int pos[] = { (leftBorder + rightBorder) / 2, leftBorder, (leftBorder + rightBorder) / 2 + 1 };

	int i = leftBorder;
	while (i < rightBorder + 1)
	{
		if (pos[1] <= pos[0])
		{
			if (pos[2] > rightBorder || A[pos[1]] < A[pos[2]]) {
				temp[i] = A[pos[1]];
				pos[1]++;
			}
			else {
				temp[i] = A[pos[2]];
				pos[2]++;
				result = result + pos[0] - pos[1] + 1;
			}
		}
		else
		{
			temp[i] = A[pos[2]];
			pos[2]++;
			result = result + pos[0] - pos[1] + 1;
		}
		i++;
	}
	i = leftBorder;
	while (i < rightBorder + 1)
	{
		A[i] = temp[i];
		i++;
	}
	delete[] temp;
	return result;
}

int64_t recursive(int n, int *A, int leftBorder, int rightBorder, int64_t result)
{
	if (leftBorder < rightBorder)
	{
		result = recursive(n, A, leftBorder, (leftBorder + rightBorder) / 2, result);
		result = recursive(n, A, (leftBorder + rightBorder) / 2 + 1, rightBorder, result);
		result = merge(n, A, leftBorder, rightBorder, result);
	}
	return result;
}

int main19()
{
	int n;
	int* A;
	cin >> n;
	A = new int[n];
	for (int i = 0; i < n; i++)
		cin >> A[i];
	cout << recursive(n, A, 0, n - 1, 0);
	return 0;
}