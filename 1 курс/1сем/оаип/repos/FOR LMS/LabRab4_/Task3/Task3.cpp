#include <iostream>
#include <string>

int main()
{
    setlocale(LC_ALL, "rus");
	std::cout << "Задание 3. Память для массива выделить динамически." << '\n';
	std::cout << "Вариант 13. Дана действительная квадратная матрица порядка N. Найти сумму и произведение элементов, расположенных в верхнем и нижнем треугольниках матрицы." << '\n';
	std::cout << "Лишик Ксения. Группа 253505" << '\n' << '\n';

    std::string temp_input, check_string;
    int array_size_N = 0, repeat = 1;
    int i, j, k;
    double sum = 0, mult = 1;

    do
    {
        sum = 0;
        mult = 1;

        // Ввод размерности квадратной матрицы и проверка на корректность ввода (натуральное число, не 0, не отрицательное, не вещественное, не содержит буквы, не превышает 2147483647)
        while (true)
        {
            std::cout << "Введите порядок квадратной матрицы N = ";
            getline(std::cin, temp_input);

            if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
            {
                // <=2147483647
                if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
                {
                    array_size_N = std::stoi(temp_input);
                    check_string = std::to_string(array_size_N);

                    if ((check_string.length() != temp_input.length()) || (array_size_N < 1))
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

        double* a = nullptr;
        a = new double[array_size_N * array_size_N];
                
        // Ввод элементов массива и проверка на корректность ввода (вещественные числа, не содержит буквы)
        std::cout << "Введите элементы матрицы (вещественные числа)" << "\n";
        for (int i = 0; i < array_size_N; i++)
        {
            for (int j = 0; j < array_size_N; j++)
            {
                while (true)
                {
                    std::cout << "Введите a[" << i << "][" << j << "] = ";
                    std::cin >> *(a + i * array_size_N + j);
                    
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
        }

        std::cout << "\n" << "Введены следующие данные:" << "\n";

        std::cout << "Порядок квадратной матрицы N = " << array_size_N << "\n";

        std::cout << "Элементы матрицы: " << "\n ";
        for (int i = 0; i < array_size_N; i++)
        {
            for (int j = 0; j < array_size_N; j++)
            {
                std::cout << *(a + i * array_size_N + j) << " ";
            }
            std::cout << "\n ";
        }
               
        k = array_size_N / 2;
        
        std::cout << "\n";
        // сумма и произведение элементов, расположенных в верхнем треугольнике матрицы
        for (i = 0; i <= k - 1; i++)
        {
            for (j = i;j <= array_size_N - 1 - i; j++)
            {
                //std::cout << *(a + i * array_size_N + j) << "\t";
                sum = sum + (* (a + i * array_size_N + j));
                mult = mult * ( * (a + i * array_size_N + j));
            }
            //std::cout << "\n";
        }
        
        // + сумма и произведение элементов, расположенных в нижнем треугольнике матрицы
        for (i = k; i <= array_size_N - 1; i++)
        {
            for (j = array_size_N - 1 - i;j <= i; j++)
            {
               // std::cout << *(a + i * array_size_N + j) << "\t";
                sum = sum + (* (a + i * array_size_N + j));
                mult = mult * (*(a + i * array_size_N + j));
            }
            //std::cout << "\n";
        }

        std::cout << "\n" << "Сумма элементов, расположенных в верхнем и нижнем треугольниках матрицы: " << sum << "\n";
        std::cout << "\n" << "Произведение элементов, расположенных в верхнем и нижнем треугольниках матрицы: " << mult << "\n";

        delete [] a;
        a = nullptr;

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