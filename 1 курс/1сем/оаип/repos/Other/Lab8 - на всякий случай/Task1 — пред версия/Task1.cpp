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

int SearchTrainByNumber(depo* ftrains, int* famountoftr, int searchNumber);

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
                    while (getchar() != '\n');
                    //std::cin.clear();
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
                while (getchar() != '\n');
                //std::cin.clear();
            }
        }
        else
        {
            printf("Повторите ввод. Некорректное значение.\n");
            while (getchar() != '\n');
            //std::cin.clear();
        }
    }
    printf("\n");
}

// проверка строки символов (пункт отправления/назначения)
bool CheckInputPoint(char symbols[], int max)
{
    int jj = 0, kk = 0, ll = 0;
    bool check;

    while (symbols[jj] != '\0')
    {
        jj++;
    }
    ll = jj;
    
    if (ll > max)
    {
        check = false;
        printf("Повторите ввод. Некорректное значение.\n");
        while (getchar() != '\n');
        //std::cin.clear();
    }
    else
    {
        for (jj = 0;jj < ll;jj++)
        {
            if ((symbols[jj] < -64)|| ((symbols[jj] > -1) && (symbols[jj] < 65)) || ((symbols[jj] > 90) && (symbols[jj] < 97)) || (symbols[jj] > 122))
            {
                kk++;
            }
        }

        if (kk != 0)
        {
            check = false;
            printf("Повторите ввод. Некорректное значение.\n");
            while (getchar() != '\n');
            //std::cin.clear();
        }
        else
        {
            check = true;
        }
    }
    return check;
}

// проверка времени (формат ЧЧ:ММ)
bool CheckInputTime(char symbols[], int max)
{
    int jj = 0, kk = 0, ll = 0;
    bool check;

    while (symbols[jj] != '\0')
    {
        jj++;
    }
    ll = jj;
 
    if (ll > max)
    {
        printf("Повторите ввод. Некорректное значение.\n");
        while (getchar() != '\n');
        //std::cin.clear();
    }
    else
    {
        if (symbols[2] == ':')
        {
            kk++;
        }

        for (jj = 0;jj < ll;jj++)
        {
            if ((symbols[jj] >= 48) && (symbols[jj] <= 57) && (jj != 2))
            {
                kk++;
            }
        }

        if (kk != ll)
        {
            check = false;
            printf("Повторите ввод. Некорректное значение.\n");
            while (getchar() != '\n');
            //std::cin.clear();
        }
        else
        {
            int hour = 0, min = 0;
            hour = (symbols[0] - 48) * 10 + (symbols[1] - 48);
            min = (symbols[3] - 48) * 10 + (symbols[4] - 48);
            if ((hour >= 0) && (hour <= 23) && (min >= 0) && (min <= 59))
            {
                check = true;
            }
            else
            {
                check = false;
                printf("Повторите ввод. Некорректное значение.\n");
                while (getchar() != '\n');
                //std::cin.clear();
            }
        }
    }
    return check;
}

// Введите количество поездов в динамическом массиве структур
int NumberOfTrains(void)
{
    return InputNumber(1, MAX_COUNT_TRAIN);
}

void FillTrains1(depo* ftrains, int famountoftr)
{
    int i,j,l;
    int num;
    bool correctInput;
    int editNumber, foundTrain;

    printf_s("\nВам предстоит ввести с клавиатуры информацию о %d поездах.\n", famountoftr);

    for (i = 1; i <= famountoftr; i++, ftrains++)
    {
        printf("\nВвод информации по %d-му поезду.\n", i);
        
        do
        {
            l = 0;  
            editNumber = InputNumber(2, MAX_NUMBER_TRAIN);
            foundTrain = SearchTrainByNumber(ftrains, &famountoftr, editNumber);
            if ((foundTrain == -1) && (i != 1))
            {
                printf("Повторите ввод. Такой номер поезда уже есть.\n");
                l++;
            }
         } while (l == 1);
        ftrains->amount = editNumber;

        correctInput = false;
        do
        {
            printf("Введите пункт отправления: ");
            scanf_s("%s", ftrains->departure, MAX_LENGHT_STRING);
            correctInput = CheckInputPoint(ftrains->departure, MAX_LENGHT_STRING);
            
        } while (correctInput == false);

        correctInput = false;
        do
        {
            printf("Введите пункт назначения: ");
            scanf_s("%s", ftrains->destination, MAX_LENGHT_STRING);
            correctInput = CheckInputPoint(ftrains->destination, MAX_LENGHT_STRING);
        } while (correctInput == false);

        correctInput = false;
        do
        {
            printf("Введите время отправки поезда (формат ЧЧ:ММ): ");
            scanf_s("%s", ftrains->departure_time, MAX_COUNT_TIME);
            correctInput = CheckInputTime(ftrains->departure_time, MAX_COUNT_TIME);
        } while (correctInput == false);

        while (getchar() != '\n');

        ftrains->number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);
    }
}


void FillTrains2(depo* ftrains, int* famountoftr)
{
    int i = 0;
    int repeat3 = 0;
    std::string temp_str3;
    int lastTrain;
    bool correctInput;

    //printf("Введите номер поезда, после которого ввод информации завершится: ");
    //scanf_s("%d", &lastTrain);
    lastTrain = InputNumber(4, MAX_NUMBER_TRAIN);

    printf_s("\nВам предстоит ввести с клавиатуры информацию о поездах пока не введете поезд номер %d", lastTrain);
    do
    {
        i++;
        *famountoftr = *famountoftr + 1;
        printf("\nВвод информации по %d-му поезду.\n", i);
       
        //printf("Введите номер поезда: ");
        //scanf_s("%d", &ftrains[i - 1].amount);
        //printf("Введите пункт отправления: ");
        //scanf_s("%s", &ftrains[i - 1].departure, MAX_LENGHT_STRING);
        //printf("Введите пункт назначения: ");
        //scanf_s("%s", &ftrains[i - 1].destination, MAX_LENGHT_STRING);
        //printf("Введите время отправки поезда: ");
        //scanf_s("%s", &ftrains[i - 1].departure_time, MAX_COUNT_TIME);
        //printf("Введите количество свободных мест: ");
        //scanf_s("%d", &ftrains[i - 1].number_of_seats_available);

        ftrains[i-1].amount = InputNumber(2, MAX_NUMBER_TRAIN);

        correctInput = false;
        do
        {
            printf("Введите пункт отправления: ");
            scanf_s("%s", ftrains[i - 1].departure, MAX_LENGHT_STRING);
            correctInput = CheckInputPoint(ftrains[i - 1].departure, MAX_LENGHT_STRING);
        } while (correctInput == false);

        correctInput = false;
        do
        {
            printf("Введите пункт назначения: ");
            scanf_s("%s", ftrains[i - 1].destination, MAX_LENGHT_STRING);
            correctInput = CheckInputPoint(ftrains[i - 1].destination, MAX_LENGHT_STRING);
        } while (correctInput == false);

        correctInput = false;
        do
        {
            printf("Введите время отправки поезда (формат ЧЧ:ММ): ");
            scanf_s("%s", ftrains[i - 1].departure_time, MAX_COUNT_TIME);
            correctInput = CheckInputTime(ftrains[i - 1].departure_time, MAX_COUNT_TIME);
        } while (correctInput == false);

        while (getchar() != '\n');

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
}


void FillTrains3(depo* ftrains, int* famountoftr)
{
    int i = 0;
    int repeat3 = 0;
    std::string temp_str3;
    bool correctInput;

    printf_s("\nВам предстоит ввести с клавиатуры информацию о поездах.\n");
    do
    {
        i++;
        *famountoftr = *famountoftr + 1;
        printf("\nВвод информации по %d-му поезду.\n", i);
    
        //printf("Введите номер поезда: ");
        //scanf_s("%d", &ftrains[i-1].amount);
        //printf("Введите пункт отправления: ");
        //scanf_s("%s", &ftrains[i - 1].departure, MAX_LENGHT_STRING);
        //printf("Введите пункт назначения: ");
        //scanf_s("%s", &ftrains[i - 1].destination, MAX_LENGHT_STRING);
        //printf("Введите время отправки поезда: ");
        //scanf_s("%s", &ftrains[i - 1].departure_time, MAX_COUNT_TIME);
        //printf("Введите количество свободных мест: ");
        //scanf_s("%d", &ftrains[i - 1].number_of_seats_available);

        ftrains[i - 1].amount = InputNumber(2, MAX_NUMBER_TRAIN);

        correctInput = false;
        do
        {
            printf("Введите пункт отправления: ");
            scanf_s("%s", ftrains[i - 1].departure, MAX_LENGHT_STRING);
            correctInput = CheckInputPoint(ftrains[i - 1].departure, MAX_LENGHT_STRING);

        } while (correctInput == false);

        correctInput = false;
        do
        {
            printf("Введите пункт назначения: ");
            scanf_s("%s", ftrains[i - 1].destination, MAX_LENGHT_STRING);
            correctInput = CheckInputPoint(ftrains[i - 1].destination, MAX_LENGHT_STRING);
        } while (correctInput == false);

        correctInput = false;
        do
        {
            printf("Введите время отправки поезда (формат ЧЧ:ММ): ");
            scanf_s("%s", ftrains[i - 1].departure_time, MAX_COUNT_TIME);
            correctInput = CheckInputTime(ftrains[i - 1].departure_time, MAX_COUNT_TIME);
        } while (correctInput == false);

        while (getchar() != '\n');

        ftrains[i - 1].number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);

        //while (getchar() != '\n');
        
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
    bool correctInput;

    printf("\nДобавьте новый поезд\n");
    //printf("Введите номер поезда: ");
    //scanf_s("%d", &ftrains[add].amount);
    //printf("Введите пункт отправления: ");
    //scanf_s("%s", &ftrains[add].departure, MAX_LENGHT_STRING);
    //printf("Введите пункт назначения: ");
    //scanf_s("%s", &ftrains[add].destination, MAX_LENGHT_STRING);
    //printf("Введите время отправки поезда: ");
    //scanf_s("%s", &ftrains[add].departure_time, MAX_COUNT_TIME);
    //printf("Введите количество свободных мест: ");
    //scanf_s("%d", &ftrains[add].number_of_seats_available);

    ftrains[add].amount = InputNumber(2, MAX_NUMBER_TRAIN);

    correctInput = false;
    do
    {
        printf("Введите пункт отправления: ");
        scanf_s("%s", ftrains[add].departure, MAX_LENGHT_STRING);
        correctInput = CheckInputPoint(ftrains[add].departure, MAX_LENGHT_STRING);
    } while (correctInput == false);

    correctInput = false;
    do
    {
        printf("Введите пункт назначения: ");
        scanf_s("%s", ftrains[add].destination, MAX_LENGHT_STRING);
        correctInput = CheckInputPoint(ftrains[add].destination, MAX_LENGHT_STRING);
    } while (correctInput == false);

    correctInput = false;
    do
    {
        printf("Введите время отправки поезда (формат ЧЧ:ММ): ");
        scanf_s("%s", ftrains[add].departure_time, MAX_COUNT_TIME);
        correctInput = CheckInputTime(ftrains[add].departure_time, MAX_COUNT_TIME);
    } while (correctInput == false);

    while (getchar() != '\n');

    ftrains[add].number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);
   
    printf("\nИнформация о новом поезде успешно добавлена\n");
}


int SearchTrainByNumber(depo* ftrains, int* famountoftr, int searchNumber)
{// поиск элемента по номеру поезда в динамическом массиве структур
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
    //printf("\nВведите номер удаляемого поезда: ");
    //scanf_s("%d", &deleteNumber);
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
    bool correctInput;
    printf("Измените данные для поезда номер %d : ", ftrains[editIndex].amount);
      
    //printf("Введите пункт отправления: ");
    //scanf_s("%s", &ftrains[editIndex].departure, MAX_LENGHT_STRING);
    //printf("Введите пункт назначения: ");
    //scanf_s("%s", &ftrains[editIndex].destination, MAX_LENGHT_STRING);
    //printf("Введите время отправки поезда: ");
    //scanf_s("%s", &ftrains[editIndex].departure_time, MAX_COUNT_TIME);
    //printf("Введите количество свободных мест: ");
    //scanf_s("%d", &ftrains[editIndex].number_of_seats_available);

    //ftrains[editIndex].amount = InputNumber(2, MAX_NUMBER_TRAIN);

    correctInput = false;
    do
    {
        printf("Введите пункт отправления: ");
        scanf_s("%s", ftrains[editIndex].departure, MAX_LENGHT_STRING);
        correctInput = CheckInputPoint(ftrains[editIndex].departure, MAX_LENGHT_STRING);
    } while (correctInput == false);

    correctInput = false;
    do
    {
        printf("Введите пункт назначения: ");
        scanf_s("%s", ftrains[editIndex].destination, MAX_LENGHT_STRING);
        correctInput = CheckInputPoint(ftrains[editIndex].destination, MAX_LENGHT_STRING);
    } while (correctInput == false);

    correctInput = false;
    do
    {
        printf("Введите время отправки поезда (формат ЧЧ:ММ): ");
        scanf_s("%s", ftrains[editIndex].departure_time, MAX_COUNT_TIME);
        correctInput = CheckInputTime(ftrains[editIndex].departure_time, MAX_COUNT_TIME);
    } while (correctInput == false);

    while (getchar() != '\n');

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

    while (getchar() != '\n');
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
                //printf("\nВведите номер искомого поезда: ");
                //scanf_s("%d", &searchNumber);
                searchNumber = InputNumber(6, MAX_NUMBER_TRAIN);
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
                //printf("\nВведите номер редактируемого поезда: ");
                //scanf_s("%d", &editNumber);
                editNumber = InputNumber(8, MAX_NUMBER_TRAIN);
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
                while (getchar() != '\n');
                //std::cin.clear();
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
