// прописную после точки заменить на заглавную букву

#include<fstream>
#include <iostream>

int main()
{
	std::fstream file;
	file.open("file.txt");
	
	char prev=' ', cur;
	int pos;

	if (!file.is_open())
	{
		std::cout << "ERROR";
		exit(1);
	}
	while (!file.eof())
	{
		file >> cur;
		
		if (prev == '.')
		{
			cur = cur - 32;
			pos = file.tellg();
			pos--;
			file.seekg(pos);
			file << cur;
			pos ++ ;
			file.seekg(pos);
		}
		prev = cur;
	}
	file.close();
	return 0;
}