// В текстовом файле найти сумму наименьшего и наибольшего числа (числа действительные)

#include<fstream>
#include <iostream>

int main()
{
	std::ifstream file;
	file.open("f.txt");

	double min=0, max=0, n;

	if (!file.is_open())
	{
		std::cout << "ERROR";
		exit(1);
	}
	while (!file.eof())
	{
		file >> n;
		
		if (min > n)
			min = n;
		if (max < n)
			max = n;
	}
	file.close();
	std::cout << min + max << "\n";
	return 0;
}