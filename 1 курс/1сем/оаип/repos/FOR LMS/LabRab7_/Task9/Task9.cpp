#include <iostream>
#include <string>

// Ввод номера бочки с отравленным вином и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
int InputNumber(std::string input, int Max_Number)
{
    int Number;
    std::string temp_input, check_string;

    while (true)
    {
        std::cout << input << " (от 1 до " << Max_Number << "): ";
        getline(std::cin, temp_input);

        if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
        {
            // <=2147483647
            if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
            {
                Number = std::stoi(temp_input);
                check_string = std::to_string(Number);

                if ((check_string.length() != temp_input.length()) || (Number < 1) || (Number > Max_Number))
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                }
                else
                {
                    return Number;
                    break;
                }
            }

            else
            {
                std::cout << "Повторите ввод. Некорректное значение." << "\n";
                std::cin.clear();
            }
        }
        else
        {
            std::cout << "Повторите ввод. Некорректное значение." << "\n";
            std::cin.clear();
        }
    }
    std::cout << "\n";
}

// расчет комбинаций O(n^2) 
int BinominalCoefficient(int n, int k)
{
    if ((n == k) || (k == 0))
    {
        return 1;
    }
    else
    {
        return BinominalCoefficient(n - 1, k - 1) + BinominalCoefficient(n - 1, k);
    }
}

// конвертация числа из 10СС в 2СС O(n)
std::string ConvertDecimalBinary(int k, int m)
{
    int ii = 0;
    std::string temp_str;

    while (k != 0)
    {
        temp_str += k % 2 + 48;
        k = k / 2;
        ii = ii + 1;
    }
    std::reverse(temp_str.begin(), temp_str.end());

    while (temp_str.length() < m)
    {
        temp_str = '0' + temp_str;
    }
    return temp_str;
}

// генерация массива из различных комбинаций рабов, которые вместе дегустируют группы бочек (биномиальный коэффициент)
// в массиве в i-ой строке в j-ом столбце стоит 1, если j-ый раб пил из соответствующей группы бочек, 0 - если не пил
//O(n^2)
int* GenerationBinaryArray(int* array_binary, int n, int m)
{
    std::string str;
    int ii = 0;

    for (int kk = 0;kk < n;kk++)
    {
        str = ConvertDecimalBinary(kk, m);
        for (int jj = 0;jj < m;jj++)
        {
            *(array_binary + ii * m + jj) = str[jj] - 48;
        }
        ii++;
    }
    return array_binary;
}

// сортировка массива по количеству рабов, одновременно дегустирующие одни и те же группы бочек
//O(n^2)
int* SortBinaryArray(int* array_binary, int row, int Slaves)
{
    int* array_new = nullptr;
    array_new = new int[row * Slaves];

    int ones = 1;
    int count_1 = 0;
    int kk = 0;

    while (ones <= Slaves)
    {
        for (int ii = 1;ii < row;ii++)
        {
            count_1 = 0;
            for (int jj = 0;jj < Slaves;jj++)
            {
                if (*(array_binary + ii * Slaves + jj) == 1)
                {
                    count_1 = count_1 + 1;
                }
            }

            if (count_1 == ones)
            {
                for (int jj = 0;jj < Slaves;jj++)
                {
                    *(array_new + kk * Slaves + jj) = *(array_binary + ii * Slaves + jj);
                }
                kk++;
            }
        }
        ones++;
    }

    for (int jj = 0;jj < Slaves;jj++)
    {
        *(array_new + kk * Slaves + jj) = *(array_binary + 0 * Slaves + jj);
    }
    return array_new;
}

// генерируется матрица диапазонов и номеров бочек в группах для 1 дня 
// O(n^2)
int* GenerationGroupBarrels(int* array, int MaxNumber, int Slaves)
{
    // в массиве 32 строки с диапазонами номеров бочек в группах
    // (5 групп по 16 бочек в каждой, 10 групп - по 8 бочек, 10 групп - по 4 бочки, 5 групп - по 2 бочки, 1 группа - из 1 бочки, 1 группа - из 29 бочек)
    // количество строк = 2^k, количество групп - биноминальным коэффициентом: 1 из 5, 2 из 5, 3 из 5, 4 из 5, 5 из 5 и осточным способом

    int step = 1;
    int group;
    int ii, jj;
    int ones = 0;

    for (jj = 0;jj < Slaves;jj++)
    {
        step = step * 2;
    }

    int k = 1;
    *(array + (k - 1) * 2 + 1) = 0;
    for (jj = 0;jj < Slaves;jj++)
    {
        step = step / 2;
        group = BinominalCoefficient(Slaves, jj + 1);
        for (ii = 1;ii <= group; ii++)
        {
            *(array + k * 2 + 0) = *(array + (k - 1) * 2 + 1) + 1;
            *(array + k * 2 + 1) = *(array + k * 2 + 0) + step - 1;
            //std::cout << *(array + k * 2 + 0) << "  " << *(array + k * 2 + 1) << "\n";
            k++;
        }
    }
    *(array + k * 2 + 0) = *(array + (k - 1) * 2 + 1) + 1;
    *(array + k * 2 + 1) = MaxNumber;

    return array;
}

// печать количества выживших рабов в i-ый день
void PrintSurvivingSlaves(int day, int surviving_slaves)
{
    switch (surviving_slaves)
    {
    case 1:
        std::cout << "После " << day << "-ого дня дегустации выжил " << surviving_slaves << " раб" << "\n";
        break;
    case 2:
        std::cout << "После " << day << "-ого дня дегустации выжило " << surviving_slaves << " раба" << "\n";
        break;
    case 3:
        std::cout << "После " << day << "-ого дня дегустации выжило " << surviving_slaves << " раба" << "\n";
        break;
    case 4:
        std::cout << "После " << day << "-ого дня дегустации выжило " << surviving_slaves << " раба" << "\n";
        break;
    case 5:
        std::cout << "После " << day << "-ого дня дегустации все выжили." << "\n";
        break;
    case 0:
        std::cout << "После " << day << "-ого дня дегустации все умерли.";
        break;
    }
}

// поиск бочки с отравленным вином во 2 день
//O(n^2)
int FindNumberBarrel(int* array, int NumberBarrel, int find_row, int day, int Slaves, int died_slaves)
{
    // В первый день дегустации умер 1 раб
    // Во второй день 4 раба дегустируют 16 бочек (в группе 1 бочка)
    // может умереть 1 - 4 рабов либо никто из выживших в первый день
    // в массиве 16 строк - 16 комбинаций:
    // 1, 2, 3, 4 (4 комбинаций)
    // 1 - 2, 1 - 3, 1 - 4, 2 - 3, 2 - 4, 3 - 4 (+6 = 10к)
    // 1-2-3, 1-2-4, 1-3-4, 2-3-4  (+4=14к)
    // 1-2-3-4 (+1=15к)
    // из одной бочки никто не пьет (+1=16к) 
    // в массиве в i-ой строке в j-ом столбце стоит 1, если j-ый раб пил из соответствующей группы бочек, 0 - если не пил
    // array_slave (16,4)

     // В первый день дегустации умерло 2 раба
     // Во второй день 3 раба дегустируют 8 бочек (в группе 1 бочка)
     // может умереть 1 - 3 рабов либо никто из выживших в первый день
     // в массиве 8 строк - 8 комбинаций:
     // 1, 2, 3 (3 комбинаций)
     // 1 - 2, 1 - 3, 2 - 3 (+3 = 6к)
     // 1-2-3  (+1=7к)
     // из одной бочки никто не пьет (+1=16к) 
     // array_slave (8,3)

     // В первый день дегустации умерло 3 раба
     // Во второй день 2 раба дегустируют 4 бочки (в группе 1 бочка)
     // может умереть 1 - 2 раба либо никто из выживших в первый день
     // в массиве 4 строки - 4 комбинаций:
     // 1, 2 (2 комбинаций)
     // 1 - 2 (+1 = 3к)
     // из одной бочки никто не пьет (+1=4к) 
     // в массиве в i-ой строке в j-ом столбце стоит 1, если j-ый раб пил из соответствующей группы бочек, 0 - если не пил
     // array_slave (4,2)

     // В первый день дегустации умерло 4 раба
     // Во второй день 1 раб дегустирует 2 бочки (в группе 1 бочка)
     // может или умереть 1 раб, или нет
     // в массиве 4 строки - 4 комбинаций:
     // 1 (2 комбинаций)
     // из одной бочки никто не пьет (+1=1к) 
     // в массиве в i-ой строке в j-ом столбце стоит 1, если j-ый раб пил из соответствующей группы бочек, 0 - если не пил
     // array_slave (2,1)

    int FindNumBarrel;
    int d_slaves = died_slaves;
    int step = *(array + find_row * 2 + 1) - (*(array + find_row * 2 + 0)) + 1; // количество бочек в группе
    int find_row2;

    int* array_slave = nullptr;
    array_slave = new int[step * (Slaves - died_slaves)];
    array_slave = GenerationBinaryArray(array_slave, step, Slaves - died_slaves);

    for (int ii = 1;ii <= step; ii++)
    {
        if (NumberBarrel == *(array + (find_row) * 2 + 0) + (ii - 1))
        {
            FindNumBarrel = *(array + (find_row) * 2 + 0) + (ii - 1);
            find_row2 = ii;
            break;
        }
    }

    for (int jj = 0; jj < Slaves - died_slaves; jj++)
    {
        if (*(array_slave + (find_row2 - 1) * (Slaves - died_slaves) + jj) == 1)
        {
            d_slaves = d_slaves + 1;
        }
    }

    PrintSurvivingSlaves(day, Slaves - d_slaves);
    delete[] array_slave;
    array_slave = nullptr;
    return FindNumBarrel;
}


int main()
{
    setlocale(LC_ALL, "RUS");
    std::cout << "Задание 9. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "Патриций решил устроить праздник и для этого приготовил 240 бочек вина.Однако к нему пробрался недоброжелатель, который подсыпал яд в одну из бочек." << "\n";
    std::cout << "Про яд известно, что человек, его выпивший, умирает в течение 24 часов.До праздника осталось два дня, то есть 48 часов." << "\n";
    std::cout << "У Патриция есть пять рабов, которыми он готов пожертвовать, чтобы узнать в какой именно бочке яд." << "\n" << "\n";

    const int MaxNumber = 240;
    const int Slaves = 5;
    const int row = 32; //2^5

    int repeat = 1;
    std::string temp_input1;

    do
    {
        setlocale(LC_ALL, "rus");
        int NumberBarrel;
        int step;
        int find_row;
        int died_slaves = 0;
        int i, j;
        int day = 1;

        NumberBarrel = InputNumber("Введите номер бочки с отравленным вином", MaxNumber);

        // массив из 32 различных комбинаций рабов, которые вместе дегустируют группы бочек (биномиальный коэффициент)
        // 1, 2, 3, 4, 5 (5 комбинаций)
        // 1 - 2, 1 - 3, 1 - 4, 1 - 5, 2 - 3, 2 - 4, 2 - 5, 3 - 4, 3 - 5, 4 - 5 (+10 = 15к)
        // 1-2-3, 1-2-4, 1-2-5, 1-3-4, 1-3-5, 1-4-5, 2-3-4, 2-3-5, 2-4-5, 3-4-5 (+10=25к)
        // 1 - 2 - 3 - 4, 1 - 2 - 3 - 5, 1 - 2 - 4 - 5, 1 - 3 - 4 - 5, 2 - 3 - 4 - 5 (+5 = 30к)
        // 1 - 2 - 3 - 4 - 5 (+1 = 31к)
        // никто не пил (+1 = 32к)
        // в массиве в i-ой строке в j-ом столбце стоит 1, если j-ый раб пил из соответствующей группы бочек, 0 - если не пил
        int* array_slave1 = nullptr;
        array_slave1 = new int[row * Slaves];
        array_slave1 = GenerationBinaryArray(array_slave1, row, Slaves);
        array_slave1 = SortBinaryArray(array_slave1, row, Slaves);

        // в массиве 32 строки с диапазонами номеров бочек в группах
        // (5 групп по 16 бочек в каждой, 10 групп - по 8 бочек, 10 групп - по 4 бочки, 5 групп - по 2 бочки, 1 группа - из 1 бочки, 1 группа - из 29 бочек)
        // количество строк = 2^k, количество групп - биноминальным коэффициентом: 1 из 5, 2 из 5, 3 из 5, 4 из 5, 5 из 5 и осточным способом
        int* array = nullptr;
        array = new int[(row + 1) * 2];
        array = GenerationGroupBarrels(array, MaxNumber, Slaves);

        // 1-ый день
        std::cout << "\n" << day << " день" << "\n";

        // найдем мз 32 диапазонов тот диапазон, в котором находится введенный пользователем номер
        for (i = 1;i <= row; i++)
        {
            if ((NumberBarrel >= *(array + i * 2 + 0)) && (NumberBarrel <= *(array + i * 2 + 1)))
            {
                std::cout << "Найден диапазон: " << *(array + i * 2 + 0) << " - " << *(array + i * 2 + 1) << "\n";
                find_row = i;
                break;
            }
        }

        for (j = 0; j < Slaves; j++)
        {
            if (*(array_slave1 + (find_row - 1) * Slaves + j) == 1)
            {
                died_slaves = died_slaves + 1;
            }
        }

        if (died_slaves == 5)
        {
            PrintSurvivingSlaves(day, Slaves - died_slaves);
            std::cout << " Бочка найдена в первый день: " << *(array + find_row * 2 + 0) << "\n";
          }
        else
        {
            PrintSurvivingSlaves(day, Slaves - died_slaves);
        }

        // 2-ый день
        if (died_slaves != 5)
        {
            day = day + 1;
            std::cout << "\n" << day << " день" << "\n";

            if (died_slaves != 0)
            {
                std::cout << "Номер бочки с отравленным вином: " << FindNumberBarrel(array, NumberBarrel, find_row, day, Slaves, died_slaves) << "\n";
            }
            if (died_slaves == 0)
            {
                // В первый день дегустации никто не умер
                // Во второй день 5 рабов дегустируют 29 бочек (в группе 1 бочка)
                // может умереть 1 - 5 рабов либо никто из выживших в первый день
                // в массиве 29 строк - 29 комбинаций:
                // 1, 2, 3, 4, 5 (5 комбинаций)
                // 1 - 2, 1 - 3, 1 - 4, 1 - 5, 2 - 3, 2 - 4, 2 - 5, 3 - 4, 3 - 5, 4 - 5 (+10 = 15к)
                // 1-2-3, 1-2-4, 1-2-5, 1-3-4, 1-3-5, 1-4-5, 2-3-4, 2-3-5, 2-4-5, 3-4-5 (+10=25к)
                // 1 - 2 - 3 - 4, 1 - 2 - 3 - 5, 1 - 2 - 4 - 5, 1 - 3 - 4 - 5, 2 - 3 - 4 - 5 (+5 = 30к)
                // 1 - 2 - 3 - 4 - 5 (+1 = 31к)
                // в массиве в i-ой строке в j-ом столбце стоит 1, если j-ый раб пил из соответствующей группы бочек, 0 - если не пил

                step = *(array + find_row * 2 + 1) - (*(array + find_row * 2 + 0)) + 1; // количество бочек в группе

                for (i = 1;i <= step; i++)
                {
                    if (NumberBarrel == *(array + (find_row) * 2 + 0) + (i - 1))
                    {
                        std::cout << "Номер бочки с отравленным вином: " << *(array + (find_row) * 2 + 0) + (i - 1) << "\n";
                        find_row = i;
                        break;
                    }
                }

                for (j = 0; j < Slaves; j++)
                {

                    if (*(array_slave1 + (find_row - 1) * Slaves + j) == 1)
                    {
                        died_slaves = died_slaves + 1;
                    }
                }

                PrintSurvivingSlaves(day, Slaves - died_slaves);
            }
        }

        delete[]array;
        array = nullptr;

        delete[]array_slave1;
        array_slave1 = nullptr;


        // Повторный запуск программы
        std::cout << '\n' << "Для повторного ввода данных введите 1 и нажать ENTER; для окончания работы - любой другой символ и нажать ENTER: ";
        std::cin >> temp_input1;
        if ((temp_input1[0] == '1') && (temp_input1.length() == 1))
        {
            repeat = 1;
            while (std::cin.get() != '\n');
        }
        else
        {
            std::cout << "Программа завершила работу." << "\n";
            repeat = 0;
        }
    } while (repeat == 1);

    return 0;
}