//Написать программу, содержащую функцию, которая проверяет, упорядочены ли элементы списка (массива) по алфавиту.
#include <iostream>
#include <fstream>

// проверка отсортирован ли файл по алфавиту
bool CheckSort()
{
	std::ifstream fileIn ("input.txt");

	std::string str1, str2;
	bool check = true;

	if (!fileIn.is_open())
	{
		std::cout << "File error" << "\n";
		exit(1);
	}
	while (!fileIn.eof())
	{
		fileIn >> str1;
		fileIn >> str2;
		if (str1 > str2)
		{
			check = false;
			break;
		}
	}
	return check;
}

// сортировка слов в файле по алфавиту
void Sort()
{
	std::ifstream fileIn;
	std::fstream fileOut;
	unsigned int size = 0, pos1 = 0, pos2 = 0;
	std::string str1, str2;
	fileIn.open("input.txt");
	fileOut.open("output.txt");
	if (!fileIn.is_open() || !fileOut.is_open())
	{
		std::cout << "File error" << "\n";
		exit(1);
	}
	while (!fileIn.eof())
	{
		fileIn >> str1;
		fileOut << str1 << " ";
		size++;
	}
	fileIn.close();
	fileOut.clear();
	fileOut.seekg(0);
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			fileOut >> str1;
			pos1 = fileOut.tellg();
			pos1++;
			fileOut >> str2;
			if (str1 > str2)
			{
				fileOut.seekg(pos2);
				fileOut << str2 << " ";
				pos1 = fileOut.tellg();
				fileOut << str1 << " ";
				fileOut.seekg(pos1);
				pos2 = pos1;
				continue;
			}
			else
			{
				fileOut.seekg(pos1);
				pos2 = pos1;
				continue;
			}
		}
		fileOut.clear();
		pos1 = pos2 = 0;
		fileOut.seekg(pos1);
	}
	fileOut.close();
}

int main()
{
	
	// проверка отсортирован ли файл по алфавиту
	if (CheckSort())
	{
		std::cout << "File is  sorted";
	}
	else 
	{
		std::cout << "File isn't sorted";

		// сортировка слов по алфавиту
		Sort();
	}
	
	return 0;

}