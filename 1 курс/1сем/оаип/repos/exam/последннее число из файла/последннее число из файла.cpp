#include <iostream>
#include <fstream>
#include <string>

//для вещественных чисел
void PrintReal(int pos)
{
	double x;

	std::ifstream file;
	file.open("inp.txt");

	//вывод на печать k-ый элемента файла
	if (!file.is_open())
	{
		std::cout << "ERROR" << "\n";
	}
	else
	{
		std::cout << "OPEN" << "\n";
		//file.seekg(pos);
		for (int i = 0; i <= pos; i++)
			file >> x;
		std::cout << x << "\n";
	}
	file.clear();
	file.close();

	//вывод на печать последний элемент файла
	file.open("inp.txt");
	if (!file.is_open())
	{
		std::cout << "ERROR" << "\n";
	}
	else
	{
		std::cout << "OPEN" << "\n";
		while (!file.eof())
			file >> x;
		std::cout << x;
	}
	file.clear();
	file.close();
}

//для строк	
void PrintString(int pos)
{
	std::string str;

	std::ifstream file;
	file.open("inp_string.txt");

	//вывод на печать k-ый элемента файла
	if (!file.is_open())
	{
		std::cout << "ERROR" << "\n";
	}
	else
	{
		std::cout << "OPEN" << "\n";
		//file.seekg(pos);
		for (int i = 0; i <= pos; i++)
			file >> str;
		std::cout << str << "\n";
	}
	file.clear();
	file.close();

	//вывод на печать последний элемент файла
	file.open("inp_string.txt");
	if (!file.is_open())
	{
		std::cout << "ERROR" << "\n";
	}
	else
	{
		std::cout << "OPEN" << "\n";
		while (!file.eof())
			file >> str;
		std::cout << str;
	}
	file.clear();
	file.close();
}

int main()
{
	int pos;

	std::cin >> pos;
	
	PrintReal(pos);
	PrintString(pos);

}