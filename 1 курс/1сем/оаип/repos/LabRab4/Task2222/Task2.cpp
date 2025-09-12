#include <iostream>
#include <string>
#include <cstring>
#include <fstream>


using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 2. Инициализировать при объявлении статический двумерный массив целых чисел размером N*M." << '\n';
    std::cout << "Вариант 13. Найти сумму элементов, расположенных в четных (по номеру) строках матрицы." << '\n';
    std::cout << "Лишик Ксения" << '\n' << '\n';

    string temp_input, sum_check;
    int repeat = 0;

    do
    {
        int array_size_N = 0;
        int array_size_M = 0;
        int a[100][100];
        int array_sum = 0;
        

        bool is_number;
        int more_average = 0;

        do
        {
            is_number = true;
            std::cout << "Введите количество строк массива N: ";
            std::cin >> temp_input;
            try
            {
                array_size_N = std::stoi(temp_input); //transform to int
                sum_check = std::to_string(array_size_N); //transform back to string
                if (temp_input.length() != sum_check.length() || (array_size_N <= 0)) //check if new string have same symbols amount with input one or nergtive
                {
                    throw invalid_argument("Wrong Input");
                }
            }
            catch (std::invalid_argument e) {
                std::cout << "Повторите ввод - не все введенные символы цифры или размерность отрицательна, или равна 0.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                is_number = false;
            }
        } while (!is_number);
        //        std::cout << "Принята размерность N: " << array_size_N << '\n';

        do
        {
            is_number = true;
            std::cout << "Введите количество столбцов массива M: ";
            std::cin >> temp_input;
            try
            {
                array_size_M = std::stoi(temp_input); //transform to int
                sum_check = std::to_string(array_size_M); //transform back to string
                if (temp_input.length() != sum_check.length() || (array_size_M <= 0)) //check if new string have same symbols amount with input one or nergtive
                {
                    throw invalid_argument("Wrong Input");
                }
            }
            catch (std::invalid_argument e) {
                std::cout << "Повторите ввод - не все введенные символы цифры или размерность отрицательна, или равна 0.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                is_number = false;
            }
        } while (!is_number);
        //        std::cout << "Принята размерность M: " << array_size_M << '\n';



        for (int i = 0; i < array_size_N; i++)
            for (int j = 0; j < array_size_M; j++)
            {
                do
                {
                is_number = true;
                std::cout << "Введите a[" << i << "][" << j << "] = ";
                std::cin >> temp_input;
                try
                {
                    a[i][j] = std::stoi(temp_input);
                    sum_check = std::to_string(a[i][j]);
                    if (temp_input.length() != sum_check.length())
                    {
                        throw invalid_argument("Wrong Input");
                    }
                }
                catch (const std::invalid_argument& e) {
                    std::cout << "Повторите ввод (не все введенные символы цифры).\n";
                    is_number = false;
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
            } while (!is_number);

            // std::cout << "Принято a[" << i << "][" << j << "]" << a[i][j] << '\n';
            }

        
        std::cout << '\n' << "Размерность массива: " << array_size_N << "x" << array_size_M << '\n';
        
        for (int i = 0; i < array_size_N; i++)
        {
            if ((i+1) % 2 == 0)
            {
                for (int j = 0; j < array_size_M; j++)
                    array_sum = array_sum + a[i][j];
            }
        }
       
        std::cout << "Элементы массива: " << '\n';

        for (int i = 0; i < array_size_N; i++)
        {
            for (int j = 0; j < array_size_M; j++)
            {
                std::cout << a[i][j] << " ";
            }
            std::cout << '\n';

        }

        std::cout << "Cумма элементов, расположенных в четных (по номеру) строках матрицы: " << array_sum << '\n';

        std::cout << '\n' << "Введите 1 + ENTER  для повторного ввода данных или любой другой символ + ENTER для окончания работы : ";

        std::cin >> temp_input;

        try
        {
            repeat = std::stoi(temp_input);
            sum_check = std::to_string(repeat);
            if (temp_input.length() != sum_check.length() || repeat != 1)
            {
                throw invalid_argument("Wrong Input");
            }
        }
        catch (std::invalid_argument e) {
            std::cin.clear();
            std::cin.ignore(100000, '\n');
            std::cout << "До свидания.";
            repeat = 0;
        }


    } while (repeat == 1);


    return 0;
}