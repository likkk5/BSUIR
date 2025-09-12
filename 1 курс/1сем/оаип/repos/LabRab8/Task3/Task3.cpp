#include <iostream>     
#include <fstream>   
#include <windows.h>
#include <stdio.h>		// для ввода, вывода (scanf, printf)
#include <conio.h>		// для задержки программы (getch)
#include <string>
#include <string.h>

//#define MAX_COUNT_EMPLOYEE 100 // максимальное количество сотрудников в динамическом массиве структур
#define MAX_LENGHT_STRING 31 // максимальная длина строки для ФИО
#define MAX_LENGHT_PERSONAL_NUMBER 5 // максимальный табельный номер (четырехзначный код - ХХХХ)
#define MAX_PERSONAL_NUMBER 9999 // максимальный табельный номер
#define MAX_HOURS_MOUNTH 200 // максимальное количество отработанных часов в месяц
#define MAX_HOURLY_RATE 100.00 // максимальный почасовой тариф

// о сотруднике
class Employee
{
public:
    char last_name[MAX_LENGHT_STRING];  // фамилия сотрудника
    char first_name[MAX_LENGHT_STRING]; // отчество сотрудника
    char midle_name[MAX_LENGHT_STRING]; // имя сотрудника
    char personal_number[MAX_LENGHT_PERSONAL_NUMBER]; // табельный номер (четырехзначный код - ХХХХ)
    int hours;                                        // количество отработанных часов в месяц
    double hourly_rate;                               // почасовой тариф
    union {
        double salary_b;                             // заработная плата до расчета
        double salary_c;                             // заработная плата после расчета
    } ZP;
};

// для работы с файлом
class EmployeeRW
{
public:
    void readAll(Employee* employees, int& amount);
    void save(Employee* employee);
    void add(Employee employee);
    void edit(Employee employee, int position);  //заменяем одну строку
    Employee* remove(Employee* employees, int& count, int position); 
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
            printf("Введите номер сотрудника для поиска: ");
        }
        if (ii == 5)
        {
            printf("Введите номер сотрудника для удаления: ");
        }
        if (ii == 6)
        {
            printf("Введите номер сотрудника для редактирования: ");
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
            }
        }
    }
}

// печать динамического массива структур
void PrintEmployees(Employee* femployees, const int famountofem)
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
            i, femployees->last_name, femployees->first_name, femployees->midle_name, femployees->personal_number, femployees->hours, femployees->hourly_rate, femployees->ZP);
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

// чтение файла
void EmployeeRW::readAll(Employee* employees, int& amount)
{
    std::ifstream readStream("employee.data", std::ifstream::binary);

    int  i = 0;
    Employee employee;

    if (!readStream)
    {
        printf("Не удалось открыть файл для чтения. Файл не создан.");
    }

    while (readStream.read((char*)&employee, (int)sizeof(Employee))) {
        employees[i] = employee;
        i++; amount++;
    }

    readStream.close();
}

void EmployeeRW::save(Employee* employees)
{
    std::ofstream writeStream("employee.data", std::ofstream::binary);

    for (int i = 0; i < (sizeof(employees) / sizeof(Employee)); i++)
    {
        writeStream.write((char*)&employees[i], (int)sizeof(Employee));
    }

    writeStream.close();
}

void EmployeeRW::add(Employee employee)
{
    std::ofstream stream;
    if (!stream.is_open()) {
        stream.open("employee.data", std::ofstream::binary | std::ofstream::app | std::ofstream::ate);
    }
    stream.clear();
    stream.write((char*)&employee, sizeof(employee));
    stream.close();
}

void EmployeeRW::edit(Employee employee, int position)
{
    std::ofstream stream("employee.data", std::ofstream::binary | std::ofstream::in);
    stream.clear();
    stream.seekp(sizeof(employee) * position);
    stream.write((char*)&employee, sizeof(Employee));
    stream.close();
}

Employee* EmployeeRW::remove(Employee* employees, int& count, int position)
{
    position--;
    Employee employee;
    Employee* newEmployees = new Employee[count];
    int length = 0;

    for (int i = 0; i < count; i++) {
        if (i != position) {
            newEmployees[length] = employees[i];
            length++;
        }
    }
    count--;

    std::ofstream writeStream("employee.data", std::ofstream::binary | std::ofstream::trunc);

    if (!writeStream)
    {
        printf("Не удалось открыть файл для чтения. Файл не создан.");
    }

    for (int i = 0; i < count; i++)
    {
        writeStream.write((char*)&newEmployees[i], (int)sizeof(Employee));
    }

    writeStream.close();

    return newEmployees;
}

// добавить элемент в динамический массив структур
void AddNewEmployee(Employee* femployees, int& famountofem, EmployeeRW readWrite)
{
    int add = famountofem++;
    char* ch1 = nullptr;
    ch1 = new char [MAX_LENGHT_STRING] {'\0'};
    char* ch2 = nullptr;
    ch2 = new char [MAX_LENGHT_PERSONAL_NUMBER] {'\0'};

    printf("\nДобавьте информацию о новом сотруднике\n");

    ch1 = InputString(1, MAX_LENGHT_STRING);
    strcpy_s(femployees[add].last_name, ch1);

    ch1 = InputString(2, MAX_LENGHT_STRING);
    strcpy_s(femployees[add].first_name, ch1);

    ch1 = InputString(3, MAX_LENGHT_STRING);
    strcpy_s(femployees[add].midle_name, ch1);

    ch2 = InputPersonalNumber(1, MAX_LENGHT_PERSONAL_NUMBER);
    strcpy_s(femployees[add].personal_number, strlen(ch2) + 1, ch2);

    femployees[add].hours = InputNumber(1, MAX_HOURS_MOUNTH);
    femployees[add].hourly_rate = InputNumberDouble(1, MAX_HOURLY_RATE);
    femployees[add].ZP.salary_b = 0.00;
    femployees[add].ZP.salary_c = 0.00;

    readWrite.add(femployees[add]);

    printf("\nИнформация о новом сотруднике успешно сохранена в файл. Необходимо расчитать заработную плату.\n");
}


// печать сотрудника по номеру в динамическом массиве структур
void PrintSearchEmployee(Employee* femployees, int foundEmployee)
{
    foundEmployee--;
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| № П/п  |        Фамилия сотрудника       |            Имя сотрудника           |          Отчество сотрудника        |  Табельный номер  |  Кол-во часов/месяц  |    Почасовой тариф   |    Заработная плата   |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");

    printf("| %6d | %31s | %35s | %35s | %17s | %20d | %20.2f | %21.2f |\n",
        foundEmployee + 1, femployees[foundEmployee].last_name, femployees[foundEmployee].first_name, femployees[foundEmployee].midle_name, femployees[foundEmployee].personal_number, femployees[foundEmployee].hours, femployees[foundEmployee].hourly_rate, femployees[foundEmployee].ZP);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

// удаление сотрудника по номеру в динамическом массиве структур
void DeleteEmployeeByIndex(Employee*& femployees, int& famountofem, EmployeeRW readWrite)
{
    int i, j;
    int countdel = 0;
    int temp_number = 0;
    int deleteNumber = InputNumber(5, MAX_PERSONAL_NUMBER);

    if (deleteNumber <= famountofem)
    {
        femployees = readWrite.remove(femployees, famountofem, deleteNumber);
        printf("\nСотрудник с заданным номером успешно удален.\n");
    }
    else
    {
        printf("\nСотрудник с заданным номером не найден.\n");
    }
}

// изменение сотрудника по номеру в динамическом массиве структур
void EditEmployee(Employee* femployees, int editIndex, EmployeeRW readWrite)
{
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};
    char* ch2 = new char [MAX_LENGHT_PERSONAL_NUMBER] {'\0'};
    printf("Измените данные для сотрудника с номером %d : \n", editIndex);
    editIndex--;

    ch1 = InputString(1, MAX_LENGHT_STRING);
    strcpy_s(femployees[editIndex].last_name, ch1);

    ch1 = InputString(2, MAX_LENGHT_STRING);
    strcpy_s(femployees[editIndex].first_name, ch1);

    ch1 = InputString(3, MAX_LENGHT_STRING);
    strcpy_s(femployees[editIndex].midle_name, ch1);

    ch2 = InputPersonalNumber(1, MAX_LENGHT_PERSONAL_NUMBER);
    strcpy_s(femployees[editIndex].personal_number, strlen(ch2) + 1, ch2);

    femployees[editIndex].hours = InputNumber(1, MAX_HOURS_MOUNTH);

    femployees[editIndex].hourly_rate = InputNumberDouble(1, MAX_HOURLY_RATE);

    femployees[editIndex].ZP.salary_b = 0.00;
    femployees[editIndex].ZP.salary_c = 0.00;

    readWrite.edit(femployees[editIndex], editIndex);

    printf("\nИнформация о сотруднике успешно изменена в файле. Необходимо осуществить расчет заработной платы.\n");
}

// расчет заработной платы
void CalculateSalaryEmployees(Employee* femployees, int* famountofem, EmployeeRW readWrite)
{
    for (int j = 0; j < *famountofem; j++)
    {
        if (femployees[j].hours > 144)
        {
            femployees[j].ZP.salary_c = (femployees[j].hours - 144) * 2 * femployees[j].hourly_rate + 144 * femployees[j].hourly_rate;
        }
        else
        {
            femployees[j].ZP.salary_c = femployees[j].hours * femployees[j].hourly_rate;
        }
        femployees[j].ZP.salary_c = femployees[j].ZP.salary_c * (1 - 0.12);

        readWrite.edit(femployees[j], j);
        //femployees[j].ZP.salary_b = femployees[j].ZP.salary_c;
    }
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
    Employee* employees = nullptr;// указатель на массив сотрудников
    int amountofem; // количество сотрудников в файле
    int searchEmployee;
    int foundEmployee;
    int editPersonalNumber;
    int readFileAmount = 0; //посмотреть файл после выполненных действий

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

        EmployeeRW readWrite;
        while (true)
        {
            printf("\nВаш выбор: ");
            getline(std::cin, temp_str);

            if (temp_str == "1")
            {
                // 1. Инициализация данных: формирования динамического одномерного массива структур из файла
                amountofem = 0;
                employees = new Employee[amountofem + 1];
                readWrite.readAll(employees, amountofem);
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
                    AddNewEmployee(employees, amountofem, readWrite);
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
                    // 4. Поиск данных сотрудника по номеру
                    foundEmployee = InputNumber(4, MAX_PERSONAL_NUMBER);
                    if (foundEmployee <= amountofem)
                    {
                        printf("\nСотрудник с заданным номером успешно найден.\n");
                        PrintSearchEmployee(employees, foundEmployee);
                    }
                    else
                    {
                        printf("\nСотрудник с заданным номером не найден.\n");
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
                    // 5. Удаление данных сотрудника по номеру 
                    DeleteEmployeeByIndex(employees, amountofem, readWrite);
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
                    foundEmployee = InputNumber(6, MAX_PERSONAL_NUMBER);
                    if (foundEmployee <= amountofem)
                    {
                        EditEmployee(employees, foundEmployee, readWrite);
                    }
                    else
                    {
                        printf("\nСотрудник с заданным номером не найден.\n");
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
                    CalculateSalaryEmployees(employees, &amountofem, readWrite);
                    PrintEmployees(employees, amountofem);
                    printf("\nОсуществлен расчет заработной платы.\n");
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
                    printf("\nДанные о сотрудниках, записанные в файле:");
                    readFileAmount = 0;
                    readWrite.readAll(employees, readFileAmount);
                    PrintEmployees(employees, readFileAmount);
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

    return 0;

}