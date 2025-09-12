// если число является квадратом, то записать в другой файл

#include<fstream>
#include <iostream>

int main()
{
	std::ifstream F; //вводим файл для чтения в  программу
	F.open("f.txt"); 
	std::ofstream G;
	G.open("g.txt"); //файл для записи

	int n;
	double sq;

	if (!F.is_open())
	{
		std::cout << "ERROR";
		exit(1);
	}
	//while (F >> n)
	while (!F.eof())
	{
		F >> n;
		sq = sqrt(n);
	
		if (sq - int(sq) == 0) //проверяем на целое число
			G << n << " ";
	}
	F.close();
	G.close();
	
	return 0;
}