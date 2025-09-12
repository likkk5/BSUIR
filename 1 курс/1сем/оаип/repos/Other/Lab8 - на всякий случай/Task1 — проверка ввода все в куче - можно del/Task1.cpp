#include <iostream>                   
#include <windows.h>
#include <stdio.h>		// для ввода, вывода (scanf, printf)
#include <conio.h>		// для задержки программы (getch)
#include <string.h>		// для работы со строковыми функциями
#include <string>


#define MAX_COUNT_TRAIN 100 // максимальное количество поездов в динамическом массиве структур
#define MAX_NUMBER_TRAIN 999999 // максимальный номер поезда
#define MAX_LENGHT_STRING 31 // максимальная длина строки для пункт отправления/назначения
#define MAX_COUNT_TIME 6 // максимальная количество сиволов для времени отправления (XX::XX)
#define MAX_NUMBER_FREE_SEAT 999 // максимальное число свободных мест в поезде

typedef struct depo //объявляем шаблон структуры
{
    int amount; //номер поезда
    char departure[MAX_LENGHT_STRING]{'\0'};  //пункт отправления
    char destination[MAX_LENGHT_STRING]{'\0'};  //пункт назначения 
    char departure_time[MAX_COUNT_TIME]{'\0'}; //время отправления
    int	number_of_seats_available; //число свободных мест

};

// Ввод и проверка на корректность ввода: натуральное число - не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647
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
                    std::cin.clear();
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
                std::cin.clear();
            }
        }
        else
        {
            printf("Повторите ввод. Некорректное значение.\n");
            std::cin.clear();
        }
    }
    printf("\n");
}

// ввод строки символов (пункт отправления/назначения)
std::string InputString(int ii, int max)
{
    int jj, kk = 0;
    std::string temp_input;

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

        if (temp_input.length() > max)
        {
            printf("Повторите ввод. Некорректное значение.\n");
            std::cin.clear();
        }
        else
        {
            for (jj = 0; jj < temp_input.length(); jj++)
            {
                if (((temp_input[ii] >= 65) && (temp_input[ii] <= 90)) || ((temp_input[ii] >= 97)) && (temp_input[ii] <= 122))
                {
                    kk++;
                }
            }

            if (kk != temp_input.length())
            {
                printf("Повторите ввод. Некорректное значение.\n");
                std::cin.clear();
            }
            else
            {
                return temp_input;
                break;
            }
        }
    }
}

// ввод времени (формат ЧЧ:ММ)
std::string InputTime(int ii, int max)
{
    int jj, kk = 0;
    std::string temp_input;

    while (true)
    {
        if (ii == 1)
        {
            printf("Введите время отправки поезда (формат ЧЧ:ММ): ");
        }
       
        getline(std::cin, temp_input);

        if (temp_input.length() > max)
        {
            printf("Повторите ввод. Некорректное значение.\n");
            std::cin.clear();
        }
        else
        {
            kk = 0;
            if((temp_input[2] <= ':'))

            for (jj = 0; jj < temp_input.length(); jj++)
            {
                if (((temp_input[ii] >= 48) && (temp_input[ii] <= 52)))
                {
                    kk++;
                }
            }

            if (kk != temp_input.length())
            {
                printf("Повторите ввод. Некорректное значение.\n");
                std::cin.clear();
            }
            else
            {
                int hour = 0, min = 0;
                hour = (temp_input[0] - 48) * 10 + (temp_input[1] - 48);
                min = (temp_input[3] - 48) * 10 + (temp_input[4] - 48);
                std::cout << "hour = " << hour << "\n";
                std::cout << "min = " << min << "\n";
                if ((hour >= 0) && (hour <= 23) && (min >= 0) && (min <= 59))
                {
                    return temp_input;
                    break;
                }
                else 
                {
                    printf("Повторите ввод. Некорректное значение.\n");
                    std::cin.clear();
                }
            }
        }
    }
}


// Введите количество поездов в динамическом массиве структур
int NumberOfTrains(void)
{
    return InputNumber(1, MAX_COUNT_TRAIN);
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
    int i,j;
    std::string temp_str;

    printf_s("\nВам предстоит ввести с клавиатуры информацию о %d поездах.\n", famountoftr);

    for (i = 1; i <= famountoftr; i++, ftrains++)
    {
        printf("\nВвод информации по %d-му поезду.\n", i);

        ftrains->amount = InputNumber(2, MAX_NUMBER_TRAIN);

        temp_str = InputString(1, MAX_LENGHT_STRING);
        for (j = 0;j < temp_str.length(); j++)
        {
            ftrains->departure[i] = temp_str[i];
            printf("%c", ftrains->departure[i]);
        }
        
        temp_str = InputString(2, MAX_LENGHT_STRING);
        for (j = 0;j < temp_str.length(); j++)
        {
            ftrains->destination[i] = temp_str[i];
        }

        temp_str = InputTime(1, MAX_COUNT_TIME);
        for (j = 0;j < temp_str.length(); j++)
        {
            ftrains->departure_time[i] = temp_str[i];
        }

       
        
        // рабочий кусок, но не функции
        /*
        int jj, kk, ll;
        while (true)
        {
            kk = 0;
            jj = 0;
            ll = 0;
          
            printf("Введите пункт отправления: ");
            scanf_s("%s", ftrains->departure, MAX_LENGHT_STRING);
            
            while (ftrains->departure[jj] != '\0')
            {
                jj++;
            }
            ll = jj;
      
            
            if (ll > MAX_LENGHT_STRING)
            {
                printf("Повторите ввод. Некорректное значение.\n");
                std::cin.clear();
            }
            else
            {
                jj = 0;
                for (jj = 0;jj < ll;jj++)
                {
                    if ((ftrains->departure[jj] < 65) || ((ftrains->departure[jj] > 90) && (ftrains->departure[jj] < 97)) || (ftrains->departure[jj] > 122))
                    {
                        kk++;
                    }
                }
         
                if (kk != 0)
                {
                    printf("Повторите ввод. Некорректное значение.\n");
                    std::cin.clear();
                }
                else
                {
                    break;
                }
            }
            while (std::cin.get() != '\n');
        }

        while (true)
        {
            kk = 0;
            jj = 0;
            ll = 0;

            printf("Введите пункт назначения: ");
            scanf_s("%s", ftrains->destination, MAX_LENGHT_STRING);

            while (ftrains->destination[jj] != '\0')
            {
                jj++;
            }
            ll = jj;
      
            if (ll > MAX_LENGHT_STRING)
            {
                printf("Повторите ввод. Некорректное значение.\n");
                std::cin.clear();
            }
            else
            {
                jj = 0;
                for (jj = 0;jj < ll;jj++)
                {
                    if ((ftrains->destination[jj] < 65) || ((ftrains->destination[jj] > 90) && (ftrains->destination[jj] < 97)) || (ftrains->destination[jj] > 122))
                    {
                        kk++;
                    }
                }

                if (kk != 0)
                {
                    printf("Повторите ввод. Некорректное значение.\n");
                    std::cin.clear();
                }
                else
                {
                    break;
                }
            }
            while (std::cin.get() != '\n');
        }

        while (true)
        {
            kk = 0;
            jj = 0;
            ll = 0;

            printf("Введите время отправки поезда (формат ЧЧ:ММ): ");
            scanf_s("%s", ftrains->departure_time, MAX_COUNT_TIME);
       
            while (ftrains->departure_time[jj] != '\0')
            {
                jj++;
            }
            ll = jj;
       
            if (ll > MAX_COUNT_TIME)
            {
                printf("Повторите ввод. Некорректное значение.\n");
                std::cin.clear();
            }
            else
            {
                jj = 0;
                kk = 0;
                
                if (ftrains->departure_time[2] == ':')
                {
                    kk++;
                }

                for (jj = 0;jj < ll;jj++)
                {
                    if ((ftrains->departure_time[jj] >=48) && (ftrains->departure_time[jj] <= 57) && (jj != 2))
                    {
                        kk++;
                    }
                }
        
                if (kk != ll)
                {
                    printf("Повторите ввод. Некорректное значение.\n");
                    std::cin.clear();
                }
                else
                {
                    int hour = 0, min = 0;
                    hour = (ftrains->departure_time[0] - 48) * 10 + (ftrains->departure_time[1] - 48);
                    min = (ftrains->departure_time[3] - 48) * 10 + (ftrains->departure_time[4] - 48);
                    if ((hour >= 0) && (hour <= 23) && (min >= 0) && (min <= 59))
                    {
                        break;
                    }
                    else
                    {
                        printf("Повторите ввод. Некорректное значение.\n");
                        std::cin.clear();
                    }

                }
            }
        }

        while (std::cin.get() != '\n');*/


        ftrains->number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);
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
