#include<fstream>
#include <iostream>

int main()
{
	std::ifstream file;
	file.open("f.txt");
	std::string s1, s2;
	std::cin >> s1;
	if (!file.is_open())
	{
		std::cout << "ERROR";
	}
	while (!file.eof())
	{
		file >> s2;
		if (s1 == s2)
		{
			std::cout << "DONE";
			break;
		}
	}
	file.close();
}