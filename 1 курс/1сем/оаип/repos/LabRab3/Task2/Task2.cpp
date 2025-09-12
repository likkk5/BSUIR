#include <iostream>

int main()
{	
	long double d = 0, e = 0.001, sum = 0;
	int n = 0;
	
	do 
	{
		n++;
		sum = sum + d;
		d = 1/pow(2, n) + 1 / pow(3, n);
	}
	while (d >= e);
	std::cout << "sum = " << sum << "\n";
	return 0;

}
