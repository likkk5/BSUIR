#include <iostream>                   
#include <windows.h>
#include <stdio.h>		// для ввода, вывода (scanf, printf)
#include <conio.h>		// для задержки программы (getch)
#include <string>
#include "struct.h"
#include "foo.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("Задание 1. Лишик Ксения. Группа 253505 \n");
    printf("Вариант 13. У администратора железнодорожных касс имеется информация о свободных местах в поездах на текущие сутки в следующем виде: ");
    printf("пункт назначения, время отправления, число свободных мест. \n");
    printf("Вывести информацию о числе свободных мест в поездах, следующих до заданного пункта назначения (сортировка вставкой по убыванию). \n \n");
  
    Menu();
      
    return 0;
}
