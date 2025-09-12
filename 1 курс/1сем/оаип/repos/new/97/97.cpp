#include<fstream>
#include <iostream>

int main()
{
	std::ifstream Input;
	Input.open("f.txt");
	std::ofstream Output;
	Output.open("g.txt");
	int s1, s2;
	if (!Input.is_open())
	{
		std::cout << "ERROR";
	}
	while (!Input.eof())
	{
		Input >> s1;
		if((s1%3==0) && (s1%7!=0)) //делятся на три но не делятся на 7
		Output << s1<< " ";
	}
	Input.close();
	Output.close();
}