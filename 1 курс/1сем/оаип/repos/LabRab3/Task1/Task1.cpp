#include <iostream>

int main()
{
	int i=1, a, b, N=0;
		
	while (i <= 30)
	{
		if (i % 2 == 0)
		{
			a = i / 2;
			b = i * i * i;
		}
		else
		{
			a = i;
			b = i * i;
		}
	    N = N + (a - b) * (a - b);
	    i++;
	}
	std::cout << N;
	
	return 0;
}