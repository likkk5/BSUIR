#include <iostream>                   
#include <windows.h>
#include <stdio.h>		// для ввода, вывода (scanf, printf)
#include <conio.h>		// для задержки программы (getch)
#include <string.h>		// для работы со строковыми функциями
#include <string>

#define MAX_LENGHT_STRING 30 // максимальная длина строки для пункт отправления/назначения
#define MAX_COUNT_TRAIN 100 // максимальное количество поездов в динамическом массиве структур
#define MAX_COUNT_TIME 5 // максимальная количество сиволов для времени отправления (XX::XX)

typedef struct depo //объявляем шаблон структуры
{
    int amount; //номер поезда
    char departure[MAX_LENGHT_STRING];  //пункт отправления
    char destination[MAX_LENGHT_STRING];  //пункт назначения 
    char departure_time[MAX_COUNT_TIME]; //время отправления
    int	number_of_seats_available; //число свободных мест

};

int NumberOfTrains(void)
{
    int amount;
    do
    {
        printf("Введите количество поездов из отрезка [1 .. %d]: ", MAX_COUNT_TRAIN);
        scanf_s("%d", &amount);
    } while ((amount < 1) || (amount > MAX_COUNT_TRAIN));
    return amount;
}

/*
void AddTrain(depo* ftrains, int* famountoftr)
{
    int tempNumberTrain; // номер поезда, перед которым планируется добавить новый поезд
    int add;
    int i;

    printf("\nВведите № поезда, перед которым планируется добавить новый: ");
    scanf_s("%d", &tempNumberTrain);

    // проверка, существует ли такой номер поезда в нашем списке. Если да, то новый поезд возможно добавить, иначе - нет
    for (add = 0; add < *famountoftr; add++)
        if ((ftrains + add)->amount == tempNumberTrain)
            break;

    if (add >= *famountoftr)
    {
        printf("Поезда с введенным номером не существует. Добавление нового поезда невозможно\n");
        return;
    }
    else
    {
        // происходит смещение всех поездов, чтобы освободить место для нового поезда
        for (i = (*famountoftr - 1); i >= add; i--)
        {
            ftrains[i + 1].amount = ftrains[i].amount;
            strcpy_s(ftrains[i + 1].depurture, ftrains[i].depurture);
            strcpy_s(ftrains[i + 1].destination, ftrains[i].destination);
            strcpy_s(ftrains[i + 1].departure_time, ftrains[i].departure_time);
            ftrains[i + 1].number_of_seats_available = ftrains[i].number_of_seats_available;
        }
        printf("\nВведите номер добавляемого поезда: ");
        scanf_s("%d", &ftrains[add].amount);
        printf("\nИнформация о новом поезде успешно добавлена!\n");
        (*famountoftr)++;
        // getch();
    }
}*/

void FillTrains1(depo* ftrains, const int famountoftr)
{
    int i;
    printf_s("\nВам предстоит ввести с клавиатуры информацию о %d поездах.\n", famountoftr);
    for (i = 1; i <= famountoftr; i++, ftrains++)
    {
        printf("\nВвод информации по %d-му поезду.\n", i);
        printf("Введите номер поезда: ");
        scanf_s("%d", &ftrains->amount);
        printf("Введите пункт отправления: ");
        scanf_s("%s", &ftrains->departure, MAX_LENGHT_STRING);
        printf("Введите пункт назначения: ");
        scanf_s("%s", &ftrains->destination, MAX_LENGHT_STRING);
        printf("Введите время отправки поезда: ");
        scanf_s("%s", &ftrains->departure_time, MAX_COUNT_TIME);
        printf("Введите количество свободных мест: ");
        scanf_s("%d", &ftrains->number_of_seats_available);
    }
}

void FillTrains2(depo* ftrains, int* famountoftr)
{
    int i = 0;
    int repeat3 = 0;
    std::string temp_str3;
    int lastTrain;

    printf("Введите номер поезда, после которого ввод информации завершится: ");
    scanf_s("%d", &lastTrain);

    printf_s("\nВам предстоит ввести с клавиатуры информацию о поездах пока не введете поезд номер %d", lastTrain);
    do
    {
        i++;
        *famountoftr = *famountoftr + 1;
        printf("\nВвод информации по %d-му поезду.\n", i);
        printf("Введите номер поезда: ");
        scanf_s("%d", &ftrains[i - 1].amount);
        printf("Введите пункт отправления: ");
        scanf_s("%s", &ftrains[i - 1].departure, MAX_LENGHT_STRING);
        printf("Введите пункт назначения: ");
        scanf_s("%s", &ftrains[i - 1].destination, MAX_LENGHT_STRING);
        printf("Введите время отправки поезда: ");
        scanf_s("%s", &ftrains[i - 1].departure_time, MAX_COUNT_TIME);
        printf("Введите количество свободных мест: ");
        scanf_s("%d", &ftrains[i - 1].number_of_seats_available);

        if (ftrains[i - 1].amount == lastTrain)
        {
            printf("Ввод динамического одномерного массива структур завершен\n");
            repeat3 = 0;
            break;
            repeat3 = 1;
        }
        else
        {
            repeat3 = 1;
        }
    } while (repeat3 == 1);

    *famountoftr = *famountoftr - 1;
}


void FillTrains3(depo* ftrains, int* famountoftr)
{
    int i = 0;
    int repeat3 = 0;
    std::string temp_str3;

    printf_s("\nВам предстоит ввести с клавиатуры информацию о поездах.\n");
    do
    {
        i++;
        *famountoftr = *famountoftr + 1;
        printf("\nВвод информации по %d-му поезду.\n", i);
        printf("Введите номер поезда: ");
        scanf_s("%d", &ftrains[i-1].amount);
        printf("Введите пункт отправления: ");
        scanf_s("%s", &ftrains[i - 1].departure, MAX_LENGHT_STRING);
        printf("Введите пункт назначения: ");
        scanf_s("%s", &ftrains[i - 1].destination, MAX_LENGHT_STRING);
        printf("Введите время отправки поезда: ");
        scanf_s("%s", &ftrains[i - 1].departure_time, MAX_COUNT_TIME);
        printf("Введите количество свободных мест: ");
        scanf_s("%d", &ftrains[i - 1].number_of_seats_available);

        while (std::cin.get() != '\n');
        printf("Для продолжения ввода информации о следующем поезде введите ДА, для завершения ввода информации - любой символ:  ");
        getline(std::cin, temp_str3);
        if (temp_str3 == "ДА")
        {
           repeat3 = 1;
        }
        else
        {
            printf("Ввод динамического одномерного массива структур завершен\n");
            repeat3 = 0;
            break;
        }
    } while (repeat3 == 1);
    
    *famountoftr = *famountoftr - 1;
}



void PrintTrains(depo* ftrains, const int famountoftr)
{
    int i;
    if (famountoftr == 0)
    {
        printf("\nНет ни одного поезда. Печать информации невозможна.\n");
        return;
    }
    printf_s("\nИнформация о %d поездах имеет вид:\n", famountoftr);
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| № Поезда |          Пункт отправления          |          Пункт назначения           | Время отправки | Количество свободных мест |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------- \n");
    for (i = 1; i <= famountoftr; i++, ftrains++)
    {
        printf("| %-8d | %35s | %35s | %14s | %-25d |\n",
            ftrains->amount, ftrains->departure, ftrains->destination, ftrains->departure_time, ftrains->number_of_seats_available);
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

void AddNewTrain(depo* ftrains, int* famountoftr)
{

    int add = (*famountoftr)++;

    printf("\nДобавьте новый поезд");
    printf("Введите номер поезда: ");
    scanf_s("%d", &ftrains[add].amount);
    printf("Введите пункт отправления: ");
    scanf_s("%s", &ftrains[add].departure, MAX_LENGHT_STRING);
    printf("Введите пункт назначения: ");
    scanf_s("%s", &ftrains[add].destination, MAX_LENGHT_STRING);
    printf("Введите время отправки поезда: ");
    scanf_s("%s", &ftrains[add].departure_time, MAX_COUNT_TIME);
    printf("Введите количество свободных мест: ");
    scanf_s("%d", &ftrains[add].number_of_seats_available);

    printf("\nИнформация о новом поезде успешно добавлена\n");
}

int SearchTrainByNumber(depo* ftrains, int* famountoftr, int searchNumber)
{
    int i, j;
    int countsearch = 0;
    int foundIndex = -1;
    for (i = (*famountoftr - 1); i >= 0; i--)
    {
        if (ftrains[i].amount == searchNumber)
        {
            foundIndex = i;
            countsearch++;
            break;
        }
    }
    return foundIndex;
}

void PrintSearchTrain(depo* ftrains, const int famountoftr, int foundIndex)
{

    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| № Поезда |          Пункт отправления          |          Пункт назначения           | Время отправки | Количество свободных мест |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------- \n");
    printf("| %-8d | %35s | %35s | %14s | %-25d |\n",
        ftrains[foundIndex].amount, ftrains[foundIndex].departure, ftrains[foundIndex].destination, ftrains[foundIndex].departure_time, ftrains[foundIndex].number_of_seats_available);
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

void DeleteTrainByNumber(depo* ftrains, int* famountoftr)
{
    int i, j;
    int countdel = 0;
    int deleteNumber;
    printf("\nВведите номер удаляемого поезда: ");
    scanf_s("%d", &deleteNumber);
    for (i = 0; i < *famountoftr; i++)
    {
        if (ftrains[i].amount == deleteNumber)
        {
            countdel++;
            if (*famountoftr != 1)
            {
                for (j = i + 1; j < *famountoftr; j++)
                {
                    ftrains[j - 1].amount = ftrains[j].amount;
                    strcpy_s(ftrains[j - 1].departure, ftrains[j].departure);
                    strcpy_s(ftrains[j - 1].destination, ftrains[j].destination);
                    strcpy_s(ftrains[j - 1].departure_time, ftrains[j].departure_time);
                    ftrains[j - 1].number_of_seats_available = ftrains[j].number_of_seats_available;
                }
            }
        }
    }
    if (countdel == 0)
    {
        printf("Поезд с заданным номером не найден.\n");
    }
    else
    {
        printf("Поезд с заданным номером успешно удален.\n");
    }
    *famountoftr = *famountoftr - countdel;
}

void EditTrain(depo* ftrains, const int famountoftr, int editIndex)
{
    printf("Измените данные для поезда номер %d : ", ftrains[editIndex].amount);
    printf("Введите пункт отправления: ");
    scanf_s("%s", &ftrains[editIndex].departure, MAX_LENGHT_STRING);
    printf("Введите пункт назначения: ");
    scanf_s("%s", &ftrains[editIndex].destination, MAX_LENGHT_STRING);
    printf("Введите время отправки поезда: ");
    scanf_s("%s", &ftrains[editIndex].departure_time, MAX_COUNT_TIME);
    printf("Введите количество свободных мест: ");
    scanf_s("%d", &ftrains[editIndex].number_of_seats_available);

    printf("\nИнформация о поезде успешно изменена\n");
}

// сортировка массива структур по числу свободных мест в поездах(сортировка вставкой по возрастанию)
void SortAscendingTrain(depo* ftrains, int* famountoftr)
{
    int j, k;
    depo tempTrain;

    for (j = 1; j < *famountoftr; j++)
    {
        tempTrain.amount = ftrains[j].amount;
        strcpy_s(tempTrain.departure, ftrains[j].departure);
        strcpy_s(tempTrain.destination, ftrains[j].destination);
        strcpy_s(tempTrain.departure_time, ftrains[j].departure_time);
        tempTrain.number_of_seats_available = ftrains[j].number_of_seats_available;
        
        k = j - 1;
        while (tempTrain.number_of_seats_available < ftrains[k].number_of_seats_available)
        {
            ftrains[k + 1].amount = ftrains[k].amount;
            strcpy_s(ftrains[k + 1].departure, ftrains[k].departure);
            strcpy_s(ftrains[k + 1].destination, ftrains[k].destination);
            strcpy_s(ftrains[k + 1].departure_time, ftrains[k].departure_time);
            ftrains[k + 1].number_of_seats_available = ftrains[k].number_of_seats_available;
            k--;
            if (k < 0)
            {
                break;
            }
        }

        ftrains[k + 1].amount = tempTrain.amount;
        strcpy_s(ftrains[k + 1].departure, tempTrain.departure);
        strcpy_s(ftrains[k + 1].destination, tempTrain.destination);
        strcpy_s(ftrains[k + 1].departure_time, tempTrain.departure_time);
        ftrains[k + 1].number_of_seats_available = tempTrain.number_of_seats_available;
   }
}

// сортировка массива структур по числу свободных мест в поездах(сортировка вставкой по убыванию)
void SortDescendingTrain(depo* ftrains, int* famountoftr)
{
    int j, k;
    depo tempTrain;

    for (j = (*famountoftr - 2); j >=0; j--)
    {
        tempTrain.amount = ftrains[j].amount;
        strcpy_s(tempTrain.departure, ftrains[j].departure);
        strcpy_s(tempTrain.destination, ftrains[j].destination);
        strcpy_s(tempTrain.departure_time, ftrains[j].departure_time);
        tempTrain.number_of_seats_available = ftrains[j].number_of_seats_available;

        k = j + 1;
        while (tempTrain.number_of_seats_available < ftrains[k].number_of_seats_available)
        {
            ftrains[k - 1].amount = ftrains[k].amount;
            strcpy_s(ftrains[k - 1].departure, ftrains[k].departure);
            strcpy_s(ftrains[k - 1].destination, ftrains[k].destination);
            strcpy_s(ftrains[k - 1].departure_time, ftrains[k].departure_time);
            ftrains[k - 1].number_of_seats_available = ftrains[k].number_of_seats_available;
            k++;
            if (k > *famountoftr -1)
            {
                break;
            }
        }

        ftrains[k - 1].amount = tempTrain.amount;
        strcpy_s(ftrains[k - 1].departure, tempTrain.departure);
        strcpy_s(ftrains[k - 1].destination, tempTrain.destination);
        strcpy_s(ftrains[k - 1].departure_time, tempTrain.departure_time);
        ftrains[k - 1].number_of_seats_available = tempTrain.number_of_seats_available;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("Задание 1. Лишик Ксения. Группа 253505 \n");
    printf("Вариант 13. У администратора железнодорожных касс имеется информация о свободных местах в поездах на текущие сутки в следующем виде: ");
    printf("пункт назначения, время отправления, число свободных мест. \n");
    printf("Вывести информацию о числе свободных мест в поездах, следующих до заданного пункта назначения (сортировка вставкой по убыванию). \n");
    printf("\n");


    std::string temp_str, temp_str1;
    //bool correctInput = true;
    depo* trains;// указатель на массив поездов
    int amountoftr; // активное количество аоездов

    // меню
    printf("Выберите способ формирования динамического одномерного массива структур:\n");
    printf("1. Ввод заранее заданного количества структур \n");
    printf("2. Ввод до появления структуры с заданным признаком\n");
    printf("3. Диалог с пользователем о необходимости продолжать ввод\n");

    while (true)
    {
        getline(std::cin, temp_str);

        if (temp_str == "1")
        {
            // 1. Формирования динамического одномерного массива структур - ввод заранее заданного количества структур
            // вводим кол-во поездов и выделяем под поезда необходимое количество памяти
            amountoftr = NumberOfTrains();
            trains = new depo[amountoftr + 1];
            // заполняем информацию о поездах вводом с клавиатуры
            FillTrains1(trains, amountoftr);
            break;
        }

        if (temp_str == "2")
        {
            // 2. Формирования динамического одномерного массива структур - ввод до появления структуры с заданным признаком
            // вводится номер поезда, после которого ввод информации завершится
            amountoftr = 1;
            trains = new depo[amountoftr + 1];
            FillTrains2(trains, &amountoftr);
            break;
        }

        if (temp_str == "3")
        {
            // 3. Формирования динамического одномерного массива структур - Диалог с пользователем о необходимости продолжать ввод
            // вводим информацию о поездах, пока пользователь не завершит ввод
            amountoftr = 1;
            trains = new depo[amountoftr + 1];
            // заполняем информацию о поездах вводом с клавиатуры и выводим на экран
            FillTrains3(trains, &amountoftr);
            //PrintTrains(trains, amountoftr);
            break;
        }

        if ((temp_str != "1") || (temp_str != "2") || (temp_str != "3"))
        {
            printf("Некорректный ввод. Повторите ввод.\n");
            std::cin.clear();
        }
    }

    int searchNumber;
    int foundTrain;
    int editNumber;
    int repeat = 0;

    while (std::cin.get() != '\n');
    do
    {
        while (true)
        {
            printf("\nВыберите функции работы с динамическим одномерным массивом структур:\n");
            printf("4. Просмотр содержимого динамического массива структур\n");
            printf("5. Дополнение уже существующего массива структур новыми структурами\n");
            printf("6. Поиск и вывод на экран структур с заданным значением элемента\n");
            printf("7. Удаление элемента массива структур с заданным значением элемента\n");
            printf("8. Изменение элемента массива структур с заданным значением элемента\n");
            printf("9. Упорядочения массива структур по числу свободных мест в поездах (сортировка вставкой по убыванию)\n");
            printf("0. Выход из программы\n");

            getline(std::cin, temp_str);

            if (temp_str == "4")
            {
                // 4. Просмотр содержимого динамического массива структур
                // выводим на экран массив
                PrintTrains(trains, amountoftr);
                break;
            }

            if (temp_str == "5")
            {
                // 5. Дополнение уже существующего массива структур новыми структурами
                // добавляем новый поезд выводим на экран результат
                AddNewTrain(trains, &amountoftr);
                PrintTrains(trains, amountoftr);
                break;
            }

            if (temp_str == "6")
            {
                // 6. Поиск и вывод на экран структур с заданным значением элемента
                // ищем номер поезда и выводим на экран результат
                printf("\nВведите номер искомого поезда: ");
                scanf_s("%d", &searchNumber);
                foundTrain = SearchTrainByNumber(trains, &amountoftr, searchNumber);
                if (foundTrain != -1)
                {
                    printf("Поезд с заданным номером успешно найден.\n");
                    PrintSearchTrain(trains, amountoftr, foundTrain);
                }
                else
                {
                    printf("Поезд с заданным номером не найден.\n");
                }

                break;
            }

            if (temp_str == "7")
            {
                // 7. Удаление элемента массива структур с заданным значением элемента
                // удаляем поезд с заданным номером и выводим на экран результат
                DeleteTrainByNumber(trains, &amountoftr);
                PrintTrains(trains, amountoftr);
                break;
            }

            if (temp_str == "8")
            {
                // 8. Изменение элемента массива структур с заданным значением элемента
                // редактируем поезд и выводим на экран результат
                printf("\nВведите номер редактируемого поезда: ");
                scanf_s("%d", &editNumber);
                foundTrain = SearchTrainByNumber(trains, &amountoftr, editNumber);
                if (foundTrain != -1)
                {
                    EditTrain(trains, amountoftr, foundTrain);
                }
                else
                {
                    printf("Поезд с заданным номером не найден.\n");
                }
                PrintTrains(trains, amountoftr);
                break;
            }

            if (temp_str == "9")
            {
                // 9. Упорядочения массива структур по числу свободных мест в поездах (сортировка вставкой по убыванию)
                SortDescendingTrain(trains, &amountoftr);
                PrintTrains(trains, amountoftr);
                break;
            }

            if (temp_str == "0")
            {
                // 0. Выход из программы
                printf("Программа завершила свою работу\n");
                break;
            }
            if ((temp_str != "4") || (temp_str != "5") || (temp_str != "6") || (temp_str != "7") || (temp_str != "8") || (temp_str != "9") || (temp_str != "0"))
            {
                printf("Некорректный ввод. Повторите ввод.\n");
                std::cin.clear();
            }
        }

        if (temp_str == "0")
        {
            repeat = 0;
            break;
        }
        else
        {
            while (std::cin.get() != '\n');
            printf("Для продолжения работы введите ДА, для завершения - любой символ:  ");
            getline(std::cin, temp_str1);
            if (temp_str1 == "ДА")
            {
                repeat = 1;
            }
            else
            {
                printf("Программа завершила свою работу\n");
                repeat = 0;
                break;
            }
        }
    } while (repeat == 1);


    // очищаем память из-под массива поездов
    delete[] trains;

    return 0;
}
