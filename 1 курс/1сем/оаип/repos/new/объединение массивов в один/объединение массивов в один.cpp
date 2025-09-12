#include <iostream>

int main()
{   
	int n,m;
	std::cin >> n;
	int* a1;
	a1 = new int[n];
	for(int i=0; i<n;i++)
	std::cin >> a1[i];

	std::cin >> m;
	int* a2;
	a2 = new int[m];
	for (int j = 0; j < m;j++)
	std::cin >> a2[j];

	int* a3;
	a3 = new int[n+m];
	for (int i = 0; i < n;i++)
		 a3[i]=a1[i];
	for (int i = 0; i < m;i++)
		a3[n+i] = a2[i];

	for (int i = 0; i < n+m;i++)
		std::cout<< a3[i]<< " ";
	delete[] a1;
	delete[] a2;
	delete[] a3;
}