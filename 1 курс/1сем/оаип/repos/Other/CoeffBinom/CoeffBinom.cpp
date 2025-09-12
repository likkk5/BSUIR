#include <iostream>

unsigned long long BinominalCoefficient(int n, int k)
{
	unsigned long long p = 0;

	if ((n == k) || (k == 0))
	{
		return 1;
	}
	else
	{
		p = p + 2;
		return BinominalCoefficient(n - 1, k - 1) + BinominalCoefficient(n - 1, k);
	}
	std::cout << p << "\n";
}

int main()
{
	int n, k;
	std::cin >> n >> k;
	if ((n >= 0) && (k >= 0) && (n >= k))
	{
		std::cout << BinominalCoefficient(n, k) << "\n";
	}
	else
	{
		std::cout << "Incorrect input";
	}
	return 0;
}

