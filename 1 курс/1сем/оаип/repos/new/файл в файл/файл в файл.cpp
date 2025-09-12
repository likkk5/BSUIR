#include<fstream>
#include <iostream>

int main()
{
	std::ifstream Input;
	Input.open("f.txt");
	std::ofstream Output;
	Output.open("g.txt");
	std::string s1, s2;
	std::cin >> s1;
	if (!Input.is_open())
	{
		std::cout << "ERROR";
	}
	while (!Input.eof())
	{
		Input >> s1;
		Output << s1;
	}
	Input.close();
	Output.close();
}