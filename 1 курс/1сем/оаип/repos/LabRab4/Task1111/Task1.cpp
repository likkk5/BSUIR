#include <iostream>
#include <string>
#include <cstring>
#include <fstream>


using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 1. Ввести одномерный статический массив из k чисел." << '\n';
    std::cout << "Вариант 13. Определить количество элементов, значение которых больше среднего значения всех элементов массива." << '\n';
    std::cout << "Лишик Ксения" << '\n' << '\n';

    string temp_input, sum_check;
    int repeat = 0;

    do
    {
        int array_size = 0;
        int a[10000];
        double array_sum = 0;
        double array_average = 0;

        bool is_number;
        int more_average = 0;

        do
        {
            is_number = true;
            std::cout << "Введите размерность массива: ";
            std::cin >> temp_input;
            try
            {
                array_size = std::stoi(temp_input); //transform to int
                sum_check = std::to_string(array_size); //transform back to string
                if (temp_input.length() != sum_check.length() || (array_size <= 0)) //check if new string have same symbols amount with input one or nergtive
                {
                    throw invalid_argument ("Wrong Input");
                }
            }
            catch (std::invalid_argument e) {
                std::cout << "Повторите ввод - не все введенные символы цифры или размерность отрицательна, или равна 0.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                is_number = false;
            }
        } while (!is_number);
//        std::cout << "Принята размерность: " << array_size << '\n';


        for (int i = 0; i < array_size; i++)
        {
            do
            {
                is_number = true;
                std::cout << "Введите " << i << " элемент массива: ";
                std::cin >> temp_input;
                try
                {
                    a[i] = std::stoi(temp_input);
                    sum_check = std::to_string(a[i]);
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

//            std::cout << "Принято " << i << "-й элемент массива:" << a[i] << '\n';
            array_sum = a[i] + array_sum;
        }

        std::cout << '\n' << "Сумма элементов массива: " << array_sum << '\n' << "Размерность массива: " << array_size << '\n';
        
        array_average = array_sum / array_size;

        std::cout << "Элементы массива: ";

        for (int i = 0; i < array_size; i++)
        {
            std::cout << a[i] << " ";
            if (a[i] > array_average)
                more_average++;
        }

        std::cout <<'\n' << "Среднее элементов массива: " << array_average << '\n';

        std::cout <<'\n' << "Количество элементов больше среднего: " << more_average << '\n';

        std::cout << '\n' << "Введите 1 + ENTER  для повторного ввода данных или любой другой символ + ENTER для окончания работы : ";

        std::cin >> temp_input;
        
        try
        {
            repeat = std::stoi(temp_input); 
            sum_check = std::to_string(repeat);
            if (temp_input.length() != sum_check.length() || repeat !=1)
            {
                throw invalid_argument("Wrong Input");
            }
        }
        catch (std::invalid_argument e) 
        {
            std::cin.clear();
            std::cin.ignore(100000, '\n');
            std::cout << "До свидания.";
            repeat = 0;
        }


    } while (repeat == 1);


    return 0;
}
