#include<fstream>
#include <iostream>

//найти модуль суммы и квадрат произведения
int main()
{
	std::ifstream file;
	file.open("f.txt");
	double n, l, sum = 0, mult=1;
	if (!file.is_open())
	{
		std::cout << "ERROR";
	}
	while (!file.eof())
	{
		file >> n;
		sum += n;
		mult = mult * n;
	}
	std::cout << fabs(sum);
	std::cout << mult*mult;

	file.close();
}
