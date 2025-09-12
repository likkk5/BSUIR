#include <iostream>     
#include <fstream>   
#include <windows.h>
#include <stdio.h>		// для ввода, вывода (scanf, printf)
#include <conio.h>		// для задержки программы (getch)
#include <string>
#include <string.h>

#define MAX_LENGHT_STRING 31 // максимальная длина строки для ФИО
#define MAX_LENGHT_PERSONAL_NUMBER 5 // максимальный табельный номер (четырехзначный код - ХХХХ)
#define MAX_HOURS_MOUNTH 200 // максимальное количество отработанных часов в месяц
#define MAX_HOURLY_RATE 100.00 // максимальный почасовой тариф

typedef class spisok //объявляем шаблон структуры
{
  public:
    int amount;                                 // порядковый номер сотрудника в списке
    char last_name[MAX_LENGHT_STRING]{ '\0' };  // фамилия сотрудника
    char first_name[MAX_LENGHT_STRING]{ '\0' }; // отчество сотрудника
    char midle_name[MAX_LENGHT_STRING]{ '\0' }; // имя сотрудника
    char personal_number[MAX_LENGHT_PERSONAL_NUMBER]{ '\0' }; // табельный номер (четырехзначный код - ХХХХ)
    union zp
    {
        int hours;                                  // количество отработанных часов в месяц
        double hourly_rate;                         // почасовой тариф
        double salary;                              // заработная плата в месяц
    }ZP;
 };

// ввод и проверка на корректность ввода: натуральное число - не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647
int InputNumber(int ii, int max)
{
    int number;
    std::string temp_input, check_string;

    while (true)
    {
        if (ii == 1)
        {
            printf("Введите количество отработанных часов в месяц (0..%d): ", max);
        }

        if (ii == 4)
        {
            printf("Введите номер студента для поиска: ");
        }
        if (ii == 5)
        {
            printf("Введите номер студента для удаления: ");
        }
        if (ii == 6)
        {
            printf("Введите номер студента для редактирования: ");
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
            }
        }
        else
        {
            printf("Повторите ввод. Некорректное значение.\n");
        }
    }
    printf("\n");
}

// ввод и проверка на корректность ввода: вещественное число, не содержит буквы
double InputNumberDouble(int ii, int max)
{
    double number;
    int jj, kk, ll, mm;
    std::string temp_input, check_string;

    while (true)
    {
        if (ii == 1)
        {
            printf("Введите почасовой тариф [0 .. %d]: ", max);
        }

        getline(std::cin, temp_input);

        if ((temp_input[0] == 45) && (temp_input[1] == 44))
        {
            std::cout << "Повторите ввод. Некорректное значение." << "\n";
            std::cin.clear();
        }
        else
        {
            kk = 0;
            ll = 0;
            mm = 0;
            for (jj = 0;jj < temp_input.length(); jj++)
            {
                if (((temp_input[jj] < 48) || (temp_input[jj] > 57)) && (temp_input[jj] != 46) && (temp_input[jj] != 45))
                {
                    kk = kk + 1;
                }
                if (temp_input[jj] == 46)
                {
                    ll = ll + 1;
                }
                if ((temp_input[jj] == 45) && (jj != 0))
                {
                    mm = mm + 1;
                }
            }

            if ((kk == 0) && (ll < 2) && (mm == 0))
            {
                number = std::stod(temp_input);
                if ((number >= 0) && (number <= max))
                {
                    return number;
                    break;
                }
                else
                {
                    printf("Повторите ввод. Некорректное значение.\n");
                }
            }
            else
            {
                printf("Повторите ввод. Некорректное значение.\n");
            }
        }
    }
    printf("\n");
}

// ввод строки символов и проверка (фамилия/имя/отчество)
char* InputString(int ii, int max)
{
    int jj, kk = 0;
    std::string temp_input;
    char ch[MAX_LENGHT_STRING]{ '\0' };

    while (true)
    {
        if (ii == 1)
        {
            printf("Введите фамилию сотрудника: ");
        }
        if (ii == 2)
        {
            printf("Введите имя сотрудника: ");
        }
        if (ii == 3)
        {
            printf("Введите отчество сотрудника: ");
        }

        getline(std::cin, temp_input);
        if ((temp_input.length() == 0) || (temp_input.length() > max - 1))
        {
            printf("Повторите ввод. Некорректное значение.\n");
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

// ввод табельного номера (четырехзначный цифровой код - ХХХХ)
char* InputPersonalNumber(int ii, int max)
{
    int jj, kk = 0;
    std::string temp_input;
    char ch[MAX_LENGHT_PERSONAL_NUMBER]{ '\0' };

    while (true)
    {
        if (ii == 1)
        {
            printf("Введите табельный номер (четырехзначный цифровой код - ХХХХ): ");
        }

        getline(std::cin, temp_input);
        if ((temp_input.length() != max - 1))
        {
            printf("Повторите ввод. Некорректное значение.\n");
        }
        else
        {
            kk = 0;
            for (jj = 0;jj < temp_input.length();jj++)
            {
                if ((temp_input[jj] < 48) || (temp_input[jj] > 57))

                {
                    kk++;
                }
            }
            if (kk != 0)
            {
                printf("Повторите ввод. Некорректное значение.\n");
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

// заполнение динамического массива из файла
void FillEmployees(spisok* femployees, int* famountofem)
{
    std::ifstream file_load("Text.txt", std::ios_base::binary);
    spisok empl;
    if (!file_load.is_open())
    {
        printf("\nНе удалось открыть файл. Файл не создан.\n");
    }
    else
    {
        std::string line;
        file_load >> line;
        int n = std::stod(line);
        int i = 0;
        //while (!file_load.eof())
        for(int i=0;i<n;i++)
        {
            file_load >> femployees[i].amount;
            file_load >> femployees[i].last_name;
            file_load >> femployees[i].first_name;
            file_load >> femployees[i].midle_name;
            file_load >> femployees[i].personal_number;
            file_load >> femployees[i].ZP.hours;
            file_load >> femployees[i].ZP.hourly_rate;
            file_load >> femployees[i].ZP.salary;
            //file_load.read((char*)& femployees[i], sizeof(femployees[i]));
            *famountofem = *famountofem + 1;
            //i++;
        }
        *famountofem = *famountofem - 1;
        printf("\nИнициализация данных прошла успешно. Данные загружены.\n");
    }
    file_load.close();
}

// печать динамического массива структур
void PrintEmployees(spisok* femployees, const int famountofem)
{
    int i;
    if (famountofem == 0)
    {
        printf("\nНет ни одного сотрудника в списке. Печать информации невозможна.\n");
        return;
    }
    printf_s("\nИнформация о %d сотрудниках имеет вид:\n", famountofem);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| № П/п  |        Фамилия сотрудника       |            Имя сотрудника           |          Отчество сотрудника        |  Табельный номер  |  Кол-во часов/месяц  |    Почасовой тариф   |    Заработная плата   |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");
    for (i = 1; i <= famountofem; i++, femployees++)
    {
        printf("| %6d | %31s | %35s | %35s | %17s | %20d | %20.2f | %21.2f |\n",
            femployees->amount, femployees->last_name, femployees->first_name, femployees->midle_name, femployees->personal_number, femployees->ZP.hours, femployees->ZP.hourly_rate, femployees->ZP.salary);
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

// добавить элемент в динамический массив структур
void AddNewEmployee(spisok* femployees, int* famountofem)
{
    int add = (*famountofem)++;
    char* ch1 = nullptr;
    ch1 = new char [MAX_LENGHT_STRING] {'\0'};
    char* ch2 = nullptr;
    ch2 = new char [MAX_LENGHT_PERSONAL_NUMBER] {'\0'};
   
    printf("\nДобавьте информацию о новом сотруднике\n");

    femployees[add].amount = add + 1;

    ch1 = InputString(1, MAX_LENGHT_STRING);
    strcpy_s(femployees[add].last_name, ch1);

    ch1 = InputString(2, MAX_LENGHT_STRING);
    strcpy_s(femployees[add].first_name, ch1);

    ch1 = InputString(3, MAX_LENGHT_STRING);
    strcpy_s(femployees[add].midle_name, ch1);

    ch2 = InputPersonalNumber(1, MAX_LENGHT_PERSONAL_NUMBER);
    strcpy_s(femployees[add].personal_number, ch2);

    femployees[add].ZP.hours = InputNumber(1, MAX_HOURS_MOUNTH);

    femployees[add].ZP.hourly_rate = InputNumberDouble(1, MAX_HOURLY_RATE);

    femployees[add].ZP.salary = 0.00;
    femployees[add].ZP.salary = 0.00;
    if (femployees[add].ZP.hours > 144)
    {
        femployees[add].ZP.salary = (femployees[add].ZP.hours - 144) * 2 * femployees[add].ZP.hourly_rate + 144 * femployees[add].ZP.hourly_rate;
    }
    else
    {
        femployees[add].ZP.salary = femployees[add].ZP.hours * femployees[add].ZP.hourly_rate;
    }
    femployees[add].ZP.salary = femployees[add].ZP.salary * (1 - 0.12);

    // запись в файл
    std::ofstream file_out("Text.txt", std::ios_base::binary| std::ios_base::in);
    if (!file_out) 
    {
        printf("\nНе удалось открыть файл для сохранения.\n");
    }
    else
    {
        file_out.seekp(sizeof(femployees) * (1), std::ios_base::beg);
        file_out << add + 1;
    }
    file_out.close();


    //НАДО ЕЩЕ ПОМЕНЯТЬ ПЕРВОЕ ДАННОЕ В ФАЙЛЕ

    printf("\nИнформация о новом сотруднике успешно сохранена в файл. Расчет заработной платы осуществлен.\n");

    //delete[] ch1;
    //ch1 = nullptr;
    //delete[] ch2;
    //ch2 = nullptr;
}

// поиск сотрудника по табельному номеру в динамическом массиве структур
int SearchEmployeeByPersonalNumber(spisok* femployees, int* famountofem, int searchStudent)
{
    int i;
    int countsearch = 0;
    int temp_number = 0;
    int foundEmployee = -1;
    for (i = (*famountofem - 1); i >= 0; i--)
    {
        temp_number = 1000 * (femployees[i].personal_number[0] - 48) + 100 * (femployees[i].personal_number[1] - 48) + 10 * (femployees[i].personal_number[2] - 48) + (femployees[i].personal_number[3] - 48);
        if (temp_number == searchStudent)
        {
            foundEmployee = i;
            countsearch++;
            break;
        }
    }
    return foundEmployee;
}

// печать студента по номеру в динамическом массиве структур
void PrintSearchEmployee(spisok* femployees, const int famountofem, int foundStudent)
{
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| № П/п  |        Фамилия сотрудника       |            Имя сотрудника           |          Отчество сотрудника        |  Табельный номер  |  Кол-во часов/месяц  |    Почасовой тариф   |    Заработная плата   |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");

    printf("| %6d | %31s | %35s | %35s | %17s | %20d | %20.2f | %21.2f |\n",
        femployees[foundStudent].amount, femployees[foundStudent].last_name, femployees[foundStudent].first_name, femployees[foundStudent].midle_name, femployees[foundStudent].personal_number, femployees[foundStudent].ZP.hours, femployees[foundStudent].ZP.hourly_rate, femployees[foundStudent].ZP.salary);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

// удаление сотрудника по табельному номеру в динамическом массиве структур
void DeleteEmployeeByPersonalNumber(spisok* femployees, int* famountofem)
{
    int i, j;
    int countdel = 0;
    int temp_number = 0;
    int deleteNumber;

    //табельный номер удаляемого сотрудника
    char* ch2 = nullptr;
    ch2 = new char [MAX_LENGHT_PERSONAL_NUMBER] {'\0'};
    ch2 = InputPersonalNumber(1, MAX_LENGHT_PERSONAL_NUMBER);
    deleteNumber = 1000 * (ch2[0] - 48) + 100 * (ch2[1] - 48) + 10 * (ch2[2] - 48) + (ch2[3] - 48);

    for (i = 0; i < *famountofem; i++)
    {
        temp_number = 1000 * (femployees[i].personal_number[0] - 48) + 100 * (femployees[i].personal_number[1] - 48) + 10 * (femployees[i].personal_number[2] - 48) + (femployees[i].personal_number[3] - 48);
        if (temp_number == deleteNumber)
        {
            countdel++;
            if (*famountofem != 1)
            {
                for (j = i + 1; j < *famountofem; j++)
                {
                    femployees[j - 1].amount = femployees[j].amount;
                    strcpy_s(femployees[j - 1].last_name, femployees[j].last_name);
                    strcpy_s(femployees[j - 1].first_name, femployees[j].first_name);
                    strcpy_s(femployees[j - 1].midle_name, femployees[j].midle_name);
                    strcpy_s(femployees[j - 1].personal_number, femployees[j].personal_number);
                    femployees[j - 1].ZP.hours = femployees[j].ZP.hours;
                    femployees[j - 1].ZP.hourly_rate = femployees[j].ZP.hourly_rate;
                    femployees[j - 1].ZP.salary = femployees[j].ZP.salary;
                }
            }
        }
    }
    if (countdel == 0)
    {
        printf("\nСотрудник с заданным табельным номером не найден.\n");
    }
    else
    {
        printf("\nСотрудник с заданным табельным номером успешно удален.\n");
    }
    *famountofem = *famountofem - countdel;
}

// изменение сотрудника по табельному номеру в динамическом массиве структур
void EditEmployees(spisok* femployees, const int famountofem, int editIndex)

{
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};
    char* ch2 = new char [MAX_LENGHT_PERSONAL_NUMBER] {'\0'};

    printf("Измените данные для сотрудника с табельным номером %s : \n", femployees[editIndex].personal_number);

    ch1 = InputString(1, MAX_LENGHT_STRING);
    strcpy_s(femployees[editIndex].last_name, ch1);

    ch1 = InputString(2, MAX_LENGHT_STRING);
    strcpy_s(femployees[editIndex].first_name, ch1);

    ch1 = InputString(3, MAX_LENGHT_STRING);
    strcpy_s(femployees[editIndex].midle_name, ch1);

    //ch2 = InputPersonalNumber(1, MAX_LENGHT_PERSONAL_NUMBER);
    //strcpy_s(femployees[editIndex].personal_number, ch2);

    femployees[editIndex].ZP.hours = InputNumber(1, MAX_HOURS_MOUNTH);

    femployees[editIndex].ZP.hourly_rate = InputNumberDouble(1, MAX_HOURLY_RATE);

    femployees[editIndex].ZP.salary = 0.00;
    if (femployees[editIndex].ZP.hours > 144)
    {
        femployees[editIndex].ZP.salary = (femployees[editIndex].ZP.hours - 144) * 2 * femployees[editIndex].ZP.hourly_rate + 144 * femployees[editIndex].ZP.hourly_rate;
    }
    else
    {
        femployees[editIndex].ZP.salary = femployees[editIndex].ZP.hours * femployees[editIndex].ZP.hourly_rate;
    }
    femployees[editIndex].ZP.salary = femployees[editIndex].ZP.salary * (1 - 0.12);

    // запись в файл
    std::ofstream file_out("Text.txt", std::ios_base::binary|std::ios_base::in);
    if (!file_out)
    {
        printf("\nНе удалось открыть файл для сохранения.\n");
    }
    else
    {
        file_out.seekp(sizeof(editIndex - 2), std::ios_base::beg);
        file_out.write((char*)&femployees[editIndex], sizeof(femployees[editIndex]));
    }
    file_out.close();


    printf("\nИнформация о сотруднике успешно изменена в файле. Расчет заработной платы осуществлен.\n");
}

void CalculateSalaryEmployees(spisok* femployees, int* famountofem)
{
    for (int j = 0; j < *famountofem; j++)
    {
        if (femployees[j].ZP.hours > 144)
        {
            femployees[j].ZP.salary = (femployees[j].ZP.hours - 144) * 2 * femployees[j].ZP.hourly_rate + 144 * femployees[j].ZP.hourly_rate;
        }
        else
        {
            femployees[j].ZP.salary = femployees[j].ZP.hours * femployees[j].ZP.hourly_rate;
        }
        femployees[j].ZP.salary = femployees[j].ZP.salary * (1 - 0.12);
    }
}

/*/
// cохранение списка очередности предоставления общежития в файл
void CreateFileOut(spisok* femployees, int* famountofem)
{
    std::ofstream file_out("Output.txt", std::ios_base::out);
    file_out << *famountofem << "\n";
    for (int i = 0; i < *famountofem; i++)
    {
        file_out << femployees[i].amount << "\t" << femployees[i].last_name << "\t" << femployees[i].first_name << "\t" << femployees[i].midle_name << "\t" << femployees[i].group << "\t" << femployees[i].score << "\t" << femployees[i].income << "\n";
    }
    printf("Cписок очередности предоставления мест в общежитии успешно сохранен.\n");
    file_out.close();
}
*/
// печать файла на экран
void PrintFile()
{
    std::ifstream file_out("Text.txt", std::ios_base::binary);
    std::string line;
    int i, j, n;
    file_out >> line;
    n = std::stod(line);
    printf("Информация, записанная в файле: \n");
    for (j = 0; j < n; j++)
    {
        for (i = 1; i <= 7;i++)
        {
            file_out >> line;
            std::cout << line << "\t";
        }
        std::cout << "\n";
    }
    file_out.close();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("Задание 3. Лишик Ксения. Группа 253505 \n");
    printf("Задание 2. Вариант 11. Информация о сотрудниках фирмы включает: Ф.И.О., табельный номер, количество отработанных часов за месяц, почасовой тариф.\n");
    printf("Рабочее время свыше 144 часов считается сверхурочным и оплачивается в двойном размере.\n");
    printf("Вывести размер заработной платы каждого сотрудника фирмы за вычетом подоходного налога, который составляет 12 процентов от суммы заработка.\n \n");
    printf("\n");

    std::string temp_str, temp_str1;
    int repeat = 0, repeat1 = 0;
    spisok* employees = nullptr;// указатель на массив cотрудников
    int amountofem; // количество cотрудников в файле
    int searchEmployee;
    int foundEmployee;
    int editPersonalNumber;

    do
    {
        printf("Выберите действие:\n");
        printf("1. Инициализация данных\n");
        printf("2. Просмотр данных\n");
        printf("3. Дополнение данных\n");
        printf("4. Поиск данных\n");
        printf("5. Удаление данных\n");
        printf("6. Редактирование данных\n");
        printf("7. Расчет заработной платы\n");
        printf("8. Просмотр записей файла\n");
        printf("0. Выход из программы\n");

        while (true)
        {
            printf("\nВаш выбор: ");
            getline(std::cin, temp_str);

            if (temp_str == "1")
            {
                // 1. Инициализация данных: формирования динамического одномерного массива структур из файла
                amountofem = 1;
                employees = new spisok[amountofem + 1];
                FillEmployees(employees, &amountofem);
                repeat1 = 1;
                break;
            }

            if (temp_str == "2")
            {
                if (repeat1 != 0)
                {
                    // 2. Просмотр данных
                    PrintEmployees(employees, amountofem);
                }
                else
                {
                    printf("\nДля работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            int editNumber;

            if (temp_str == "3")
            {
                if (repeat1 != 0)
                {
                    // 3. Дополнение данных
                    AddNewEmployee(employees, &amountofem);
                    PrintEmployees(employees, amountofem);
                }
                else
                {
                    printf("\nДля работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            if (temp_str == "4")
            {
                if (repeat1 != 0)
                {
                    // 4. Поиск данных сотрудника по табельному номеру
                    char* ch = nullptr;
                    ch = new char [MAX_LENGHT_PERSONAL_NUMBER] {'\0'};
                    ch = InputPersonalNumber(1, MAX_LENGHT_PERSONAL_NUMBER);
                    searchEmployee = 1000 * (ch[0] - 48) + 100 * (ch[1] - 48) + 10 * (ch[2] - 48) + (ch[3] - 48);
                    foundEmployee = SearchEmployeeByPersonalNumber(employees, &amountofem, searchEmployee);
                    if (foundEmployee != -1)
                    {
                        printf("\nСотрудник с заданным табельным номером успешно найден.\n");
                        PrintSearchEmployee(employees, amountofem, foundEmployee);
                    }
                    else
                    {
                        printf("\nСотрудник с заданным табельным номером не найден.\n");
                    }
                }
                else
                {
                    printf("\nДля работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            if (temp_str == "5")
            {
                if (repeat1 != 0)
                {
                    // 5. Удаление данных студента по номеру 
                    DeleteEmployeeByPersonalNumber(employees, &amountofem);
                    PrintEmployees(employees, amountofem);
                }
                else
                {
                    printf("\nДля работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            if (temp_str == "6")
            {
                if (repeat1 != 0)
                {
                    // 6. Редактирование данных сотрудника по табельному номеру
                    char* ch = nullptr;
                    ch = new char [MAX_LENGHT_PERSONAL_NUMBER] {'\0'};
                    ch = InputPersonalNumber(1, MAX_LENGHT_PERSONAL_NUMBER);
                    editPersonalNumber = 1000 * (ch[0] - 48) + 100 * (ch[1] - 48) + 10 * (ch[2] - 48) + (ch[3] - 48);
                    foundEmployee = SearchEmployeeByPersonalNumber(employees, &amountofem, editPersonalNumber);
                    if (foundEmployee != -1)
                    {
                        EditEmployees(employees, amountofem, foundEmployee);
                    }
                    else
                    {
                        printf("\nСотрудник с заданным табельным номером не найден.\n");
                    }
                    PrintEmployees(employees, amountofem);
                }
                else
                {
                    printf("\nДля работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            if (temp_str == "7")
            {
                if (repeat1 != 0)
                {
                    // 7. Расчет заработной платы
                    // Рабочее время свыше 144 часов считается сверхурочным и оплачивается в двойном размере
                    // заработная плата = кол-во часов в месяц * почасовой тариф за вычетом подоходного налога, который составляет 12% от суммы заработка
                    CalculateSalaryEmployees(employees, &amountofem);
                    PrintEmployees(employees, amountofem);
                }
                else
                {
                    printf("\nДля работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }
            
              if (temp_str == "8")
              {
                  if (repeat1 != 0)
                  {
                      // 7. Просмотр записей файла
                      PrintFile();
                  }
                  else
                  {
                      printf("Для работы сначала необходимо инициализировать данные.\n");
                  }
                  break;
              }
              
            if (temp_str == "0")
            {
                // 0. Выход из программы
                printf("Программа завершила свою работу\n");
                while (getchar() != '\n');
                repeat = 0;
                break;
            }
            if ((temp_str != "0") || (temp_str != "1") || (temp_str != "2") || (temp_str != "3") || (temp_str != "4") || (temp_str != "5") || (temp_str != "6") || (temp_str != "7") || (temp_str != "8"))
            {
                printf("Некорректный ввод. Повторите ввод.\n");
                //while (getchar() != '\n');
            }
        }

        if (temp_str != "0")
        {
            printf("\nХотите продолжить свою работу? ");
            repeat = 1;
        }
    } while (repeat == 1);

    // очищаем память из-под массива 
    //delete[] students;
    //students = nullptr;

    //while (getchar() != '\n');
    //getch();

    return 0;

}