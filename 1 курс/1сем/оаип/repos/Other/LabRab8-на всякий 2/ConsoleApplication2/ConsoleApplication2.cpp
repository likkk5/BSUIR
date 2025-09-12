#include <iostream>                   
#include <windows.h>
#include <stdio.h>		// для ввода, вывода (scanf, printf)
#include <conio.h>		// для задержки программы (getch)
#include <string.h>		// для работы со строковыми функциями

// У администратора железнодорожных касс имеется информация о свободных местах в поездах на текущие сутки в следующем виде :
//пункт назначения, время отправления, число свободных мест.
//Вывести информацию о числе свободных мест в поездах, следующих до заданного пункта назначения(сортировка вставкой по убыванию).
const int arr_size = 256;


struct train  //объявляем шаблон структуры
{
	char amount[arr_size]; //номер поезда
	char destination[arr_size];  //пункт назначения 
	char departure_time[9]; //время отправления
	int	number_of_seats_available; //число свободных мест

};



int main()
{
	setlocale(LC_ALL, "Russian");
	train a[100]; // Объявление массива структур 
	char destination[arr_size];
	int amount; 

	std::cout << "Введите количество поездов: " ;
	std::cin >> amount;

	std::cout << "Введите пункт назначения: "  ;
	std::cin >> destination;

	for (int i = 0; i < amount; i++) // Ввод информации о поездах
	{
		std::cout << "Введите номер поезда: ";
		std::cin >> a[i].amount;

		std::cout << "Введите пункт назначения: ";
		std::cin >> a[i].destination;

		std::cout << "Введите время отправления: ";
		std::cin >> a[i].departure_time;

		std::cout << "Введите количество свободных мест на этом поезде: " << "\n";
		std::cin >> a[i].number_of_seats_available; 
		
	}

	
	for (int i = 0; i <amount; i++)
	{
		if ((a[i].number_of_seats_available != 0) && (strcmp(destination, a[i].destination) == 0))
		{
			std::cout << "Поезд №" << a[i].amount
				<< ", отправляющийся в " << a[i].departure_time
				<< ", имеет свободных мест: " << a[i].number_of_seats_available
				<< "\n";
		}
	}
	return 0;
}

