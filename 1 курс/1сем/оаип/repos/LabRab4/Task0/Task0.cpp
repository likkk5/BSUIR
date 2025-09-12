#include <iostream>
int main()
{
	long long a;
	/*for (a = 3037000000; a <= 3037000502; a++)
	{
		std::cout << a << "   a*a = "<< a * a << "\n";
    }*/
	
	//2097151   Magic const = 4611679421361815551
	a = 2095000;
	while ((a * (a * a + 1) / 2 - 9223372036854775807) < 10000)
	{
		std::cout << a << "   Magic const = " << (a * (a*a+1)/2) << "   " << (a * (a * a + 1) / 2 - 9223372036854775807) << "\n";
		
	    a = a + 1;
	}
	return 0;

}