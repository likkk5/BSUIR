#include<fstream>
#include <iostream>

int main()
{
	std::ifstream file;
	file.open("f.txt");
	double n, l, sum=0;
	if (!file.is_open())
	{
		std::cout << "ERROR";
	}
	while (!file.eof())
	{
		file >> n;
		//l = n * n;
		sum += n*n;
	}
	std::cout << sum;

	file.close();
}