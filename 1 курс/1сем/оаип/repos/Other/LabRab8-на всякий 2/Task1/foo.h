#pragma once
#include <iostream>                   
#include <windows.h>
#include <stdio.h>		// для ввода, вывода (scanf, printf)
#include <conio.h>		// для задержки программы (getch)
#include <string>


int SearchTrainByNumber(depo* ftrains, int* famountoftr, int searchNumber);

// ввод и проверка на корректность ввода: натуральное число - не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647
int InputNumber(int ii, int max)
{
    int number;
    std::string temp_input, check_string;

    while (true)
    {
        if (ii == 1)
        {
            printf("Введите количество поездов из отрезка [1 .. %d]: ", max);
        }
        if (ii == 2)
        {
            printf("Введите номер поезда из отрезка [1 .. %d]: ", max);
        }
        if (ii == 3)
        {
            printf("Введите количество свободных мест из отрезка [1 .. %d]: ", max);
        }
        if (ii == 4)
        {
            printf("Введите номер поезда, после которого ввод информации завершится: ");
        }
        if (ii == 6)
        {
            printf("Введите номер искомого поезда: ");
        }
        if (ii == 7)
        {
            printf("Введите номер удаляемого поезда: ");
        }
        if (ii == 8)
        {
            printf("Введите номер редактируемого поезда: ");
        }
        getline(std::cin, temp_input);

        if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
        {
            // <=2147483647
            if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
            {
                number = std::stoi(temp_input);
                check_string = std::to_string(number);

                if ((check_string.length() != temp_input.length()) || (number < 1) || (number > max))
                {
                    printf("Повторите ввод. Некорректное значение.\n");
                    //while (getchar() != '\n');
                }
                else
                {
                    return number;
                    break;
                }
            }

            else
            {
                printf("Повторите ввод. Некорректное значение.\n");
                //while (getchar() != '\n');
            }
        }
        else
        {
            printf("Повторите ввод. Некорректное значение.\n");
            //while (getchar() != '\n');
        }
    }
    printf("\n");
}

// ввод строки символов и проверка (пункт отправления/назначения)
char* InputString(int ii, int max)
{
    int jj, kk = 0;
    std::string temp_input;
    char ch[MAX_LENGHT_STRING]{ '\0' };

    while (true)
    {
        if (ii == 1)
        {
            printf("Введите пункт отправления: ");
        }
        if (ii == 2)
        {
            printf("Введите пункт направления: ");
        }

        getline(std::cin, temp_input);
        if ((temp_input.length() == 0) || (temp_input.length() > max))
        {
            printf("Повторите ввод. Некорректное значение.\n");
            //while (getchar() != '\n');
        }
        else
        {
            kk = 0;
            for (jj = 0;jj < temp_input.length();jj++)
            {
                if ((temp_input[jj] < -64) || ((temp_input[jj] > -1) && (temp_input[jj] < 65)) || ((temp_input[jj] > 90) && (temp_input[jj] < 97)) || (temp_input[jj] > 122))
                {
                    kk++;
                }
            }
            if (kk != 0)
            {
                printf("Повторите ввод. Некорректное значение.\n");
                //while (getchar() != '\n');
            }
            else
            {
                for (jj = 0;jj < temp_input.length();jj++)
                {
                    ch[jj] = temp_input[jj];
                }
                return ch;
                break;
            }
        }
    }
}

// ввод времени и проверка (формат ЧЧ:ММ)
char* InputTime(int ii, int max)
{
    int jj, kk = 0;
    std::string temp_input;
    char ch[MAX_COUNT_TIME]{ '\0' };

    while (true)
    {
        if (ii == 1)
        {
            printf("Введите время отправки поезда (формат ЧЧ:ММ): ");
        }
        getline(std::cin, temp_input);
        if ((temp_input.length() == 0) || (temp_input.length() > max))
        {
            printf("Повторите ввод. Некорректное значение.\n");
            while (getchar() != '\n');
        }
        else
        {
            kk = 0;
            if (temp_input[2] == ':')
            {
                kk++;
            }

            for (jj = 0;jj < temp_input.length();jj++)
            {
                if ((temp_input[jj] >= 48) && (temp_input[jj] <= 57) && (jj != 2))
                {
                    kk++;
                }
            }

            if (kk != temp_input.length())
            {
                printf("Повторите ввод. Некорректное значение.\n");
                //while (getchar() != '\n');
            }
            else
            {
                int hour = 0, min = 0;
                hour = (temp_input[0] - 48) * 10 + (temp_input[1] - 48);
                min = (temp_input[3] - 48) * 10 + (temp_input[4] - 48);
                if ((hour >= 0) && (hour <= 23) && (min >= 0) && (min <= 59))
                {
                    for (jj = 0;jj < temp_input.length();jj++)
                    {
                        ch[jj] = temp_input[jj];
                    }
                    return ch;
                    break;
                }
                else
                {
                    printf("Повторите ввод. Некорректное значение.\n");
                    //while (getchar() != '\n');
                }
            }
        }
    }
}

// ввод количества поездов в динамическом массиве структур
int NumberOfTrains(void)
{
    return InputNumber(1, MAX_COUNT_TRAIN);
}

// ввод элементов структуры динамического массива с введенным количеством поездов
void FillTrains1(depo* ftrains, int famountoftr)
{
    int i;
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};

    printf_s("\nВам предстоит ввести с клавиатуры информацию о %d поездах.\n", famountoftr);

    for (i = 1; i <= famountoftr; i++, ftrains++)
    {
        printf("\nВвод информации по %d-му поезду.\n", i);

        ftrains->amount = InputNumber(2, MAX_NUMBER_TRAIN);

        ch1 = InputString(1, MAX_LENGHT_STRING);
        strcpy_s(ftrains->departure, ch1);

        ch1 = InputString(2, MAX_LENGHT_STRING);
        strcpy_s(ftrains->destination, ch1);

        ch1 = InputTime(1, MAX_COUNT_TIME);
        strcpy_s(ftrains->departure_time, ch1);

        ftrains->number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);
    }
    //delete[] ch1;
}

// ввод элементов структуры динамического массива пока пользователь не введет поезд номер lastTrain
void FillTrains2(depo* ftrains, int* famountoftr)
{
    int i = 0, repeat3 = 0, lastTrain;
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};

    //номер поезда, после которого ввод информации завершится
    lastTrain = InputNumber(4, MAX_NUMBER_TRAIN);
    printf_s("\nВам предстоит ввести с клавиатуры информацию о поездах пока не введете поезд номер %d", lastTrain);
    do
    {
        i++;
        *famountoftr = *famountoftr + 1;
        printf("\nВвод информации по %d-му поезду.\n", i);

        ftrains[i - 1].amount = InputNumber(2, MAX_NUMBER_TRAIN);

        ch1 = InputString(1, MAX_LENGHT_STRING);
        strcpy_s(ftrains[i - 1].departure, ch1);

        ch1 = InputString(2, MAX_LENGHT_STRING);
        strcpy_s(ftrains[i - 1].destination, ch1);

        ch1 = InputTime(1, MAX_COUNT_TIME);
        strcpy_s(ftrains[i - 1].departure_time, ch1);

        ftrains[i - 1].number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);


        if (ftrains[i - 1].amount == lastTrain)
        {
            printf("Ввод динамического одномерного массива структур завершен\n");
            repeat3 = 0;
            break;
        }
        else
        {
            repeat3 = 1;
        }
    } while (repeat3 == 1);

    *famountoftr = *famountoftr - 1;
    //delete ch1;
}

// ввод элементов структуры динамического массива пока пользователь хочет вводить информацию
void FillTrains3(depo* ftrains, int* famountoftr)
{
    int i = 0, repeat3 = 0;
    std::string temp_str3;
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};

    printf_s("\nВам предстоит ввести с клавиатуры информацию о поездах.\n");
    do
    {
        i++;
        *famountoftr = *famountoftr + 1;
        printf("\nВвод информации по %d-му поезду.\n", i);

        ftrains[i - 1].amount = InputNumber(2, MAX_NUMBER_TRAIN);

        ch1 = InputString(1, MAX_LENGHT_STRING);
        strcpy_s(ftrains[i - 1].departure, ch1);

        ch1 = InputString(2, MAX_LENGHT_STRING);
        strcpy_s(ftrains[i - 1].destination, ch1);

        ch1 = InputTime(1, MAX_COUNT_TIME);
        strcpy_s(ftrains[i - 1].departure_time, ch1);

        ftrains[i - 1].number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);

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
    //delete ch1;
}

// печать динамического массива структур
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

// добавить элемент в динамический массив структур
void AddNewTrain(depo* ftrains, int* famountoftr)
{

    int add = (*famountoftr)++;
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};

    printf("\nДобавьте новый поезд\n");

    ftrains[add].amount = InputNumber(2, MAX_NUMBER_TRAIN);

    ch1 = InputString(1, MAX_LENGHT_STRING);
    strcpy_s(ftrains[add].departure, ch1);

    ch1 = InputString(2, MAX_LENGHT_STRING);
    strcpy_s(ftrains[add].destination, ch1);

    ch1 = InputTime(1, MAX_COUNT_TIME);
    strcpy_s(ftrains[add].departure_time, ch1);

    ftrains[add].number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);

    printf("\nИнформация о новом поезде успешно добавлена\n");
}

// поиск элемента по номеру поезда в динамическом массиве структур
int SearchTrainByNumber(depo* ftrains, int* famountoftr, int searchNumber)
{
    int i;
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

// печать элемента по номеру поезда в динамическом массиве структур
void PrintSearchTrain(depo* ftrains, const int famountoftr, int foundIndex)
{

    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| № Поезда |          Пункт отправления          |          Пункт назначения           | Время отправки | Количество свободных мест |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------- \n");
    printf("| %-8d | %35s | %35s | %14s | %-25d |\n",
        ftrains[foundIndex].amount, ftrains[foundIndex].departure, ftrains[foundIndex].destination, ftrains[foundIndex].departure_time, ftrains[foundIndex].number_of_seats_available);
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

// удаление элемента по номеру поезда в динамическом массиве структур
void DeleteTrainByNumber(depo* ftrains, int* famountoftr)
{
    int i, j;
    int countdel = 0;
    int deleteNumber;

    //номер удаляемого поезда
    deleteNumber = InputNumber(7, MAX_NUMBER_TRAIN);

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

// изменение элемента по номеру поезда в динамическом массиве структур
void EditTrain(depo* ftrains, const int famountoftr, int editIndex)
{
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};

    printf("Измените данные для поезда номер %d : \n", ftrains[editIndex].amount);

    //ftrains[editIndex].amount = InputNumber(2, MAX_NUMBER_TRAIN);

    ch1 = InputString(1, MAX_LENGHT_STRING);
    strcpy_s(ftrains[editIndex].departure, ch1);

    ch1 = InputString(2, MAX_LENGHT_STRING);
    strcpy_s(ftrains[editIndex].destination, ch1);

    ch1 = InputTime(1, MAX_COUNT_TIME);
    strcpy_s(ftrains[editIndex].departure_time, ch1);

    ftrains[editIndex].number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);

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

    for (j = (*famountoftr - 2); j >= 0; j--)
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
            if (k > *famountoftr - 1)
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
