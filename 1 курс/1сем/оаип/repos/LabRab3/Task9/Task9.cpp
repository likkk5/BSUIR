#include <iostream>

int main()
{
    long long a, d, n, b = 1, sum=0;
	setlocale(LC_ALL, "rus");
	
	std::cout << "Введите a0 = ";
	std::cin >> a;
	std::cout << "Введите d = ";
	std::cin >> d;
	std::cout << "Введите n = ";
	std::cin >> n;

	for (int i = 0;i <= n-1;i++)
	{
		sum = sum + a * b;
		a = a + d;
		b = -2 * b;
	}
	std::cout << "sum = " << sum;
  
}
