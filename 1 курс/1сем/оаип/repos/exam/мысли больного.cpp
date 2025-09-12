//Создать текстовый файл F1 не менее, чем из 10 строк и записать в него информацию. Скопировать в файл F2 только те строки из F1, которые начинаются с буквы «А».

#include <iostream>
#include <string> 
#include <fstream> 

using namespace std;

int n;

void Сreate(void)
{
	std::ofstream G;          // поток для записи
	G.open("G.txt"); // открываем файл для записи
	if (!G.is_open())
	{
		cout << "Problems..." << std::endl;
	}
	else {

		printf("Введите количество строк ");
		std::cin >> n;
		std::string ch = "";
		for (int ii = 0; ii < n; ii++) {
			std::cin >> ch;
			G << ch;
			G << "\n";
		}
	}

}

void New() {
		std::ifstream G;       // поток для чтения
		G.open("G.txt"); // окрываем файл для чтения
		std::ofstream F;          // поток для записи
		F.open("F.txt"); // окрываем файл для записи
		if (!F.is_open())
		{
			cout << "Problems..." << std::endl;
		}
		std::string str, str1;
		while (!G.eof()) {
			str = "";
			getline(G, str);
			if (str[0] == 'A') {
				F << str;
				F << "\n";
			}
		}

}


int main() {
	setlocale(LC_ALL, "Russian");


	Сreate();

	New();

}






/*
//Создать текстовый файл F1 не менее, чем из 10 строк и записать в него информацию. Скопировать из файла F1 в файл F2 строки, начиная с К до К + 5.

#include <iostream>
#include <string> 
#include <fstream> 

using namespace std;

int n;

void Сreate( void )
{
	std::ofstream G;          // поток для записи
	G.open("G.txt"); // окрываем файл для записи
	if (!G.is_open())
	{
		cout << "Problems..." << std::endl;
	}
	else {
		
		printf("Введите количество строк ");
		std::cin >> n;
		int ch=0;
		for (int ii = 0; ii < n; ii++) {
			std::cin >> ch;
			G << ch;
			G << "\n";
		}
	}

}

void New() {
	std::cout << "Введите с какой строки начать копирование";
	int k = -1;
	int K;
	std::cin >> K;
	K = K - 1;
	if (K > n) {
		std::cout << "Вы ввели слишком большое число :(";
	}
	else {
		std::ifstream G;       // поток для чтения
		G.open("G.txt"); // окрываем файл для чтения
		std::ofstream F;          // поток для записи
		F.open("F.txt"); // окрываем файл для записи
		if (!F.is_open())
		{
			cout << "Problems..." << std::endl;
		}
		std::string str, str1;
		while (!G.eof()) {
			
			k++;
			std::cout << "k = " << k << " K = " << K << "\n";
			if (k >= K && k < K + 5) {
				str1 = "";
				getline(G, str1);
				F << str1;
				F << "\n";
			}
			else {
				str = "";
				getline(G, str);
			}
		}

	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	

	Сreate();

	New();

}






*/