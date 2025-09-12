#include <iostream>     
#include <fstream>   
#include <windows.h>
#include <stdio.h>		// для ввода, вывода (scanf, printf)
#include <conio.h>		// для задержки программы (getch)
#include <string>


#define MAX_COUNT_STUDENT 100 // максимальное количество студентов в динамическом массиве структур
#define MAX_LENGHT_STRING 31 // максимальная длина строки для ФИО
#define MAX_LENGHT_GROUP 11 // максимальная количество символов для номера группы
#define MAX_SCOPE 10 // максимальный средний балл
#define MAX_INCOME 10000 // максимальный доход на члена семьи

#define MIN_SALARY 457 // минимальная заработная плата в РБ в ноябре 2022

typedef struct spisok //объявляем шаблон структуры
{
    int amount;                                 // порядковый номер студента в спискеs
    char last_name[MAX_LENGHT_STRING]{ '\0' };  // фамилия студента
    char first_name[MAX_LENGHT_STRING]{ '\0' }; // отчество студента
    char midle_name[MAX_LENGHT_STRING]{ '\0' }; // имя студента
    char group[MAX_LENGHT_GROUP]{ '\0' };        // номер группы
    double score;                                // средний балл студента
    double income;                               // доход на члена семьи
};

// ввод и проверка на корректность ввода: натуральное число - не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647
int InputNumber(int ii, int max)
{
    int number;
    std::string temp_input, check_string;

    while (true)
    {
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
            printf("Введите средний балл студента [0 .. %d]: ", max);
        }
        if (ii == 2)
        {
            printf("Введите доход на члена семьи [0 .. %d]: ", max);
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
            printf("Введите фамилию студента: ");
        }
        if (ii == 2)
        {
            printf("Введите имя студента: ");
        }
        if (ii == 3)
        {
            printf("Введите отчество студента: ");
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

// ввод номера группы (буквы и цифры)
char* InputGroup(int ii, int max)
{
    int jj, kk = 0;
    std::string temp_input;
    char ch[MAX_LENGHT_STRING]{ '\0' };

    while (true)
    {
        if (ii == 1)
        {
            printf("Введите номер группы: ");
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
                if ((temp_input[jj] < 48) || ((temp_input[jj] > 57) && (temp_input[jj] < 65)) || ((temp_input[jj] > 90) && (temp_input[jj] < 97)) || (temp_input[jj] > 122))

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
void FillStudents(spisok* fstudents, int* famountofst)
{
    std::ifstream file_load("Input.txt", std::ios_base::binary);
    if (!file_load.is_open())
    {
        printf("\nНе удалось открыть файл. Файл не создан.\n");
    }
    else
    {
        int i = 0;
        while (!file_load.eof())
        {
            file_load >> fstudents[i].amount;
            file_load >> fstudents[i].last_name;
            file_load >> fstudents[i].first_name;
            file_load >> fstudents[i].midle_name;
            file_load >> fstudents[i].group;
            file_load >> fstudents[i].score;
            file_load >> fstudents[i].income;
            *famountofst = *famountofst + 1;
            i++;
        }
        *famountofst = *famountofst - 1;
        printf("\nИнициализация данных прошла успешно. Данные загружены.\n");
    }
    file_load.close();
}

// печать динамического массива структур
void PrintStudents(spisok* fstudents, const int famountofst)
{
    int i;
    if (famountofst == 0)
    {
        printf("\nНет ни одного студента в списке. Печать информации невозможна.\n");
        return;
    }
    printf_s("\nИнформация о %d студентах имеет вид:\n", famountofst);
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| № П/п  |           Фамилия студента          |               Имя студента              |             Отчество студента           |  Номер группы  |  Средний балл  |    Доход на члена семьи   |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
    for (i = 1; i <= famountofst; i++, fstudents++)
    {
        printf("| %6d | %35s | %39s | %39s | %14s | %14.2f | %25.1f |\n",
            fstudents->amount, fstudents->last_name, fstudents->first_name, fstudents->midle_name, fstudents->group, fstudents->score, fstudents->income);
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

// добавить элемент в динамический массив структур
void AddNewStudent(spisok* fstudents, int* famountofsr)
{
    int add = (*famountofsr)++;
    char* ch1 = nullptr;
    ch1 = new char [MAX_LENGHT_STRING] {'\0'};
    char* ch2 = nullptr;
    ch2 = new char [MAX_LENGHT_GROUP] {'\0'};

    printf("\nДобавьте информацию о новом студенте\n");

    fstudents[add].amount = add + 1;

    ch1 = InputString(1, MAX_LENGHT_STRING);
    strcpy_s(fstudents[add].last_name, ch1);

    ch1 = InputString(2, MAX_LENGHT_STRING);
    strcpy_s(fstudents[add].first_name, ch1);

    ch1 = InputString(3, MAX_LENGHT_STRING);
    strcpy_s(fstudents[add].midle_name, ch1);

    ch2 = InputGroup(1, MAX_LENGHT_GROUP);
    strcpy_s(fstudents[add].group, ch2);

    fstudents[add].score = InputNumberDouble(1, MAX_SCOPE);

    fstudents[add].income = InputNumberDouble(2, MAX_INCOME);

    printf("\nИнформация о новом студенте успешно добавлена\n");

    //delete[] ch1;
    //ch1 = nullptr;
    //delete[] ch2;
    //ch2 = nullptr;
}

// поиск студента по номеру в динамическом массиве структур
int SearchStudentByNumber(spisok* fstudents, int* famountofsr, int searchStudent)
{
    int i;
    int countsearch = 0;
    int foundStudent = -1;
    for (i = (*famountofsr - 1); i >= 0; i--)
    {
        if (fstudents[i].amount == searchStudent)
        {
            foundStudent = i;
            countsearch++;
            break;
        }
    }
    return foundStudent;
}

// печать студента по номеру в динамическом массиве структур
void PrintSearchStudent(spisok* fstudents, const int famountofst, int foundStudent)
{
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| № П/п  |           Фамилия студента          |               Имя студента              |             Отчество студента           |  Номер группы  |  Средний балл  |    Доход на члена семьи   |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");

    printf("| %6d | %35s | %39s | %39s | %14s | %14.2f | %25.1f  |\n",
        fstudents[foundStudent].amount, fstudents[foundStudent].last_name, fstudents[foundStudent].first_name, fstudents[foundStudent].midle_name, fstudents[foundStudent].group, fstudents[foundStudent].score, fstudents[foundStudent].income);
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

// удаление студента по номеру в динамическом массиве структур
void DeleteStudentByNumber(spisok* fstudents, int* famountofst)
{
    int i, j;
    int countdel = 0;
    int deleteNumber;

    //номер удаляемого студента
    deleteNumber = InputNumber(5, MAX_COUNT_STUDENT);

    for (i = 0; i < *famountofst; i++)
    {
        if (fstudents[i].amount == deleteNumber)
        {
            countdel++;
            if (*famountofst != 1)
            {
                for (j = i + 1; j < *famountofst; j++)
                {
                    fstudents[j - 1].amount = fstudents[j].amount;
                    strcpy_s(fstudents[j - 1].last_name, fstudents[j].last_name);
                    strcpy_s(fstudents[j - 1].first_name, fstudents[j].first_name);
                    strcpy_s(fstudents[j - 1].midle_name, fstudents[j].midle_name);
                    strcpy_s(fstudents[j - 1].group, fstudents[j].group);
                    fstudents[j - 1].score = fstudents[j].score;
                    fstudents[j - 1].income = fstudents[j].income;
                }
            }
        }
    }
    if (countdel == 0)
    {
        printf("Студент с заданным номером не найден.\n");
    }
    else
    {
        printf("Студент с заданным номером успешно удален.\n");
    }
    *famountofst = *famountofst - countdel;
}

// изменение студента по номеру в динамическом массиве структур
void EditStudent(spisok* fstudents, const int famountofst, int editIndex)

{
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};
    char* ch2 = new char [MAX_LENGHT_GROUP] {'\0'};

    printf("Измените данные для студента номер %d : \n", fstudents[editIndex].amount);

    ch1 = InputString(1, MAX_LENGHT_STRING);
    strcpy_s(fstudents[editIndex].last_name, ch1);

    ch1 = InputString(2, MAX_LENGHT_STRING);
    strcpy_s(fstudents[editIndex].first_name, ch1);

    ch1 = InputString(3, MAX_LENGHT_STRING);
    strcpy_s(fstudents[editIndex].midle_name, ch1);

    ch2 = InputGroup(1, MAX_LENGHT_GROUP);
    strcpy_s(fstudents[editIndex].group, ch2);

    fstudents[editIndex].score = InputNumberDouble(1, MAX_SCOPE);

    fstudents[editIndex].income = InputNumberDouble(2, MAX_INCOME);

    printf("\nИнформация о студенте успешно изменена\n");
}
// сортировка студентов по возрастанию дохода на члена семьи (сортировка вставкой по возрастанию)
void SortAscendingStudents(spisok* fstudents, int* famountofst)
{
    int j, k;
    spisok tempStudent;

    for (j = 1; j < *famountofst; j++)
    {
        tempStudent.amount = fstudents[j].amount;
        strcpy_s(tempStudent.last_name, fstudents[j].last_name);
        strcpy_s(tempStudent.first_name, fstudents[j].first_name);
        strcpy_s(tempStudent.midle_name, fstudents[j].midle_name);
        strcpy_s(tempStudent.group, fstudents[j].group);
        tempStudent.score = fstudents[j].score;
        tempStudent.income = fstudents[j].income;

        k = j - 1;
        while (tempStudent.income < fstudents[k].income)
        {
            fstudents[k + 1].amount = fstudents[k].amount;
            strcpy_s(fstudents[k + 1].last_name, fstudents[k].last_name);
            strcpy_s(fstudents[k + 1].first_name, fstudents[k].first_name);
            strcpy_s(fstudents[k + 1].midle_name, fstudents[k].midle_name);
            strcpy_s(fstudents[k + 1].group, fstudents[k].group);
            fstudents[k + 1].score = fstudents[k].score;
            fstudents[k + 1].income = fstudents[k].income;

            k--;
            if (k < 0)
            {
                break;
            }
        }

        fstudents[k + 1].amount = tempStudent.amount;
        strcpy_s(fstudents[k + 1].last_name, tempStudent.last_name);
        strcpy_s(fstudents[k + 1].first_name, tempStudent.first_name);
        strcpy_s(fstudents[k + 1].midle_name, tempStudent.midle_name);
        strcpy_s(fstudents[k + 1].group, tempStudent.group);
        fstudents[k + 1].score = tempStudent.score;
        fstudents[k + 1].income = tempStudent.income;
    }
}

// сортировка студентов по убыванию среднего балла, у которых доход на члена семьи выше 2МЗП (сортировка вставкой по убыванию)
void SortDescendingStudents(spisok* fstudents, int* famountofst)
{
    int j, find, k;
    spisok tempStudent;

    for (j = 1; j < *famountofst; j++)
    {
        if (fstudents[j].income >= 2 * MIN_SALARY)
        {
            find = j;
            break;
        }
    }

    for (j = (*famountofst - 2); j >= find; j--)
    {
        tempStudent.amount = fstudents[j].amount;
        strcpy_s(tempStudent.last_name, fstudents[j].last_name);
        strcpy_s(tempStudent.first_name, fstudents[j].first_name);
        strcpy_s(tempStudent.midle_name, fstudents[j].midle_name);
        strcpy_s(tempStudent.group, fstudents[j].group);
        tempStudent.score = fstudents[j].score;
        tempStudent.income = fstudents[j].income;

        k = j + 1;
        while (tempStudent.score < fstudents[k].score)
        {
            fstudents[k - 1].amount = fstudents[k].amount;
            strcpy_s(fstudents[k - 1].last_name, fstudents[k].last_name);
            strcpy_s(fstudents[k - 1].first_name, fstudents[k].first_name);
            strcpy_s(fstudents[k - 1].midle_name, fstudents[k].midle_name);
            strcpy_s(fstudents[k - 1].group, fstudents[k].group);
            fstudents[k - 1].score = fstudents[k].score;
            fstudents[k - 1].income = fstudents[k].income;

            k++;
            if (k > *famountofst - 1)
            {
                break;
            }
        }

        fstudents[k - 1].amount = tempStudent.amount;
        strcpy_s(fstudents[k - 1].last_name, tempStudent.last_name);
        strcpy_s(fstudents[k - 1].first_name, tempStudent.first_name);
        strcpy_s(fstudents[k - 1].midle_name, tempStudent.midle_name);
        strcpy_s(fstudents[k - 1].group, tempStudent.group);
        fstudents[k - 1].score = tempStudent.score;
        fstudents[k - 1].income = tempStudent.income;
    }
}

// cохранение списка очередности предоставления общежития в файл
void CreateFileOut(spisok* fstudents, int* famountofst)
{
    std::ofstream file_out("Output.txt", std::ios_base::binary);
    file_out << *famountofst << "\n";
    for (int i = 0; i < *famountofst; i++)
    {
        file_out << fstudents[i].amount << "\t" << fstudents[i].last_name << "\t" << fstudents[i].first_name << "\t" << fstudents[i].midle_name << "\t" << fstudents[i].group << "\t" << fstudents[i].score << "\t" << fstudents[i].income << "\n";
    }
    printf("Cписок очередности предоставления мест в общежитии успешно сохранен.\n");
    file_out.close();
}

// печать файла на экран
void PrintFileOut()
{
    std::ifstream file_out("Output.txt", std::ios_base::binary);
    std::string line;
    int i, j, n;
    file_out >> line;
    n = std::stod(line);
    printf("В нем содержатся следующие данные: \n");
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

    printf("Задание 2. Лишик Ксения. Группа 253505 \n");
    printf("Вариант 13. Для получения места в общежитии формируется список студентов, который включает: ");
    printf("Ф.И.О. студента, группу, средний балл, доход на члена семьи. \n");
    printf("Общежитие в первую очередь предоставляется тем, у кого доход на члена семьи меньше двух минимальных зарплат, затем остальным в порядке уменьшения среднего балла. \n");
    printf("Вывести список очередности предоставления мест в общежитии. \n \n");
    printf("\n");
    std::string temp_str, temp_str1;
    int repeat = 0, repeat1 = 0;
    spisok* students = nullptr;// указатель на массив студентов
    int amountofst; // количество студентов в файле
    int searchStudent;
    int foundStudent;
    int editNumber;

    do
    {
        printf("Выберите действие:\n");
        printf("1. Инициализация данных\n");
        printf("2. Просмотр данных\n");
        printf("3. Дополнение данных\n");
        printf("4. Поиск данных\n");
        printf("5. Удаление данных\n");
        printf("6. Редактирование данных\n");
        printf("7. Создание списка очередности предоставления мест в общежитии\n");
        printf("8. Просмотр записей файла\n");
        printf("0. Выход из программы\n");

        while (true)
        {
            printf("\n Ваш выбор: ");
            getline(std::cin, temp_str);

            if (temp_str == "1")
            {
                // 1. Инициализация данных: формирования динамического одномерного массива структур из файла
                amountofst = 1;
                students = new spisok[amountofst + 1];
                FillStudents(students, &amountofst);
                repeat1 = 1;
                break;
            }

            if (temp_str == "2")
            {
                if (repeat1 != 0)
                {
                    // 2. Просмотр данных
                    PrintStudents(students, amountofst);
                }
                else
                {
                    printf("Для работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            int editNumber;

            if (temp_str == "3")
            {
                if (repeat1 != 0)
                {
                    // 3. Дополнение данных
                    AddNewStudent(students, &amountofst);
                    PrintStudents(students, amountofst);
                }
                else
                {
                    printf("Для работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            if (temp_str == "4")
            {
                if (repeat1 != 0)
                {
                    // 4. Поиск данных студента по номеру
                    searchStudent = InputNumber(4, MAX_COUNT_STUDENT);
                    foundStudent = SearchStudentByNumber(students, &amountofst, searchStudent);
                    if (foundStudent != -1)
                    {
                        printf("Студент с заданным номером успешно найден.\n");
                        PrintSearchStudent(students, amountofst, foundStudent);
                    }
                    else
                    {
                        printf("Студент с заданным номером не найден.\n");
                    }
                }
                else
                {
                    printf("Для работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            if (temp_str == "5")
            {
                if (repeat1 != 0)
                {
                    // 5. Удаление данных студента по номеру 
                    DeleteStudentByNumber(students, &amountofst);
                    PrintStudents(students, amountofst);
                }
                else
                {
                    printf("Для работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            if (temp_str == "6")
            {
                if (repeat1 != 0)
                {
                    // 6. Редактирование данных студента
                    editNumber = InputNumber(6, MAX_COUNT_STUDENT);
                    foundStudent = SearchStudentByNumber(students, &amountofst, editNumber);
                    if (foundStudent != -1)
                    {
                        EditStudent(students, amountofst, foundStudent);
                    }
                    else
                    {
                        printf("Cтудент с заданным номером не найден.\n");
                    }
                    PrintStudents(students, amountofst);
                }
                else
                {
                    printf("Для работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            if (temp_str == "7")
            {
                if (repeat1 != 0)
                {
                    // 7. Создание списка очередности предоставления мест в общежитии
                    // Общежитие в первую очередь предоставляется тем, у кого доход на члена семьи меньше двух минимальных зарплат, 
                    // затем остальным в порядке уменьшения среднего балла
                    SortAscendingStudents(students, &amountofst);
                    SortDescendingStudents(students, &amountofst);
                    printf("Cписок очередности предоставления мест в общежитии создан.\n");
                    printf("Минимальная заработная плата в РБ в ноябре 2022 г. составила  %d руб.\n", MIN_SALARY);
                    PrintStudents(students, amountofst);
                }
                else
                {
                    printf("Для работы сначала необходимо инициализировать данные.\n");
                }
                break;
            }

            if (temp_str == "8")
            {
                if (repeat1 != 0)
                {
                    // 7. Просмотр записей файла
                    CreateFileOut(students, &amountofst);
                    PrintFileOut();
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

    while (getchar() != '\n');

    return 0;

}