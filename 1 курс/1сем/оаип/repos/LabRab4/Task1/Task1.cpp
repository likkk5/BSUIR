#include <iostream>
#include <string>

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << "Задание 1. Ввести одномерный статический массив из k чисел." << '\n';
    std::cout << "Вариант 13. Определить количество элементов, значение которых больше среднего значения всех элементов массива." << '\n';
    std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

    std::string temp_input, check_string;
    int array_size = 0, more_average, repeat = 1;
    double a[10000]{}, array_sum, array_average;

    do
    {
        array_sum = 0,
        array_average = 0;
        more_average = 0;

        // Ввод размерности массива и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
        while (true)
        {
            std::cout << "Введите размерность массива (натуральное число): ";
            getline(std::cin, temp_input);

            if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
            {
                // <=2147483647
                if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
                {
                    array_size = std::stoi(temp_input);
                    check_string = std::to_string(array_size);

                    if ((check_string.length() != temp_input.length()) || (array_size < 1))
                    {
                        std::cout << "Повторите ввод. Некорректное значение." << "\n";
                        std::cin.clear();
                    }
                    else
                    {
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

        // Ввод элементов массива и проверка на корректность ввода (вещественные числа, не содержит буквы)
        for (int i = 0; i < array_size; i++)
        {
            while (true)
            {
                std::cout << "Введите " << i << " элемент массива: ";
                std::cin >> a[i];
                
                if (std::cin.fail() || std::cin.peek() != '\n')
                {
                    std::cout << "Повторите ввод. Некорректное значение." << "\n";
                    std::cin.clear();
                    while (std::cin.get() != '\n');
                }
                else
                {
                    break;
                }
            }
        }

        std::cout << "\n" << "Введены следующие данные:" << "\n";

        std::cout << "Размерность массива k = " << array_size << "\n";

        std::cout << "Элементы массива: ";
        for (int i = 0; i < array_size; i++)
        {
            std::cout << a[i] << " ";
            array_sum = a[i] + array_sum;
        }

        array_average = array_sum / array_size;

        std::cout << "\n" << "Сумма элементов массива: " << array_sum << "\n";
        std::cout << "Среднее значение элементов массива: " << array_average << "\n";

        for (int i = 0; i < array_size; i++)
        {
            if (a[i] > array_average)
                more_average++;
        }

        std::cout << "Количество элементов массива больше среднего значения: " << more_average << "\n";


        // Повторный запуск программы
        std::cout << '\n' << "Для повторного ввода данных введите 1 и нажать ENTER; для окончания работы - любой другой символ и нажать ENTER: ";
        std::cin >> temp_input;

        if ((temp_input[0] == '1') && (temp_input.length() == 1))
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

