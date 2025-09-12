#include<fstream>
#include <iostream>
//вывод в D A0,B0,C0,A1,B1,C1
int main()
{
	std::ifstream InputA;
	InputA.open("NameA.txt");
	std::ifstream InputB;
	InputB.open("NameB.txt");
	std::ifstream InputC;
	InputC.open("NameC.txt");

	std::ofstream OutputD;
	OutputD.open("NameD.txt");
	
	int s;
	
	if (!InputA.is_open() || !InputB.is_open() || !InputC.is_open())
	{
		std::cout << "ERROR";
		exit(1);
	}
	while (!InputA.eof())
	{
		InputA >> s;
		OutputD << s <<" ";
		InputB >> s;
		OutputD << s << " ";
		InputC >> s;
		OutputD << s << " ";
	}
	InputA.close();
	InputB.close();
	InputC.close();
	OutputD.close();
}