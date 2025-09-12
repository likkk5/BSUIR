#include <iostream>


// Ввод строки (не более max символов)
char* InputString(char* input_str, int max)
{
    int c, i = 0, len = 0;
    while (true)
    {
        std::cout << "Введите строку: ";

        do
        {
            c = getchar();
            *(input_str + i) = c;
            i++;
        } while (c != '\n');
        len = i;

        if (len > max)
        {
            std::cout << "Повторите ввод. Вы ввели строку больше " << max << " символов. Количество символов в строке: " << i << "\n" << "\n";
            for (i = 0;i < len;i++)
            {
                *(input_str + i) = '\0';
            }
            i = 0;
        }
        else
        {
            return input_str;
            break;
        }
    }
}

// Вывод строки, длины строки
int OutputString(char* input_str)
{
    int i = 0;
    std::cout << "\n" << "Вы ввели строку: ";
    while (*(input_str + i) != '\n')
    {
        std::cout << *(input_str + i);
        i = i + 1;
    }
    std::cout << "\n";

    return i;
}

char* CreateArrayWords(char* input_str, int len, char* array_words)
{
    int p = 1, q = 1, k = 0;
   
    for (int i = 0;i < len; i++)
    {
        if ((*(input_str + i) != ' ') && (i != len - 1))
        {
            *(array_words + p * len + q) = *(input_str + i);
             q = q + 1;
        }
        else
        {
            if ((*(input_str + i) != ' ') && (i == len - 1))
            {
                *(array_words + p * len + q) = *(input_str + i);
                q = q + 1;
            }
            
            if (q != 1)
            {
                // в каждой строке в 0-м столбце хранится количество букв в слове 
                *(array_words + p * len + 0) = q - 1;
                p = p + 1;
            }
            
            q = 1;
        }
    }
   
    // количество слов в тексте (как код)
    *(array_words + 0 + 0) = p - 1;
 
   /*
   //Вывод массива слов на экран
    std::cout << int(*(array_words + 0 * len + 0)) << "\n";
   for (int i = 1; i < p;i++)
    {
       std::cout << int(* (array_words + i * len + 0)) << "   ";
       for (int j = 1; j <= len; j++)
       {
            std::cout << *(array_words + i * len + j);
       }
        std::cout << "\n";
    }
    */

    return array_words;
}

// Максимальная строка, в которой слова располагаются так, чтобы последняя буква каждого слова, совпадала с первой буквой последующего слова
void CreateMaxString(char* array_words, int len, int CountWords)
{
    int ii, jj, qq, k;
    
    // массивы первых и последних символов слов
    char* wordStarts = nullptr;
    wordStarts = new char[CountWords];
    char* wordEnds = nullptr;
    wordEnds = new char[CountWords];

    int CountSymbol = 0;
    for (ii = 1; ii <= CountWords;ii++)
    {
        wordStarts[ii - 1] = *(array_words + ii * len + 1);
        CountSymbol = *(array_words + ii * len + 0);
        wordEnds[ii - 1] = *(array_words + ii * len + CountSymbol);
    }

    // поиск максимальной строки
    if (CountWords > 1)
    {
        int maxLength = 0;
        int length;
        int iteration;
        int currentIndex;
        int last, last_fw;
        int max_len = 0;

        char* new_str = nullptr;
        new_str = new char[len + 3] {'\0'};

        char* max_str = nullptr;
        max_str = new char[len + 3] {'\0'};

        int* wordUsed = nullptr;
        wordUsed = new int[CountWords];


        for (ii = 0; ii < CountWords; ii++)
        {
            iteration = 0;
            currentIndex = ii;
            length = 1;

            last_fw = *(array_words + (currentIndex + 1) * len + 0);
            *(new_str + 0) = length;
            for (qq = 1;qq <= last_fw;qq++)
            {
                *(new_str + qq) = *(array_words + (currentIndex + 1) * len + qq);
            }
            *(new_str + qq) = ' ';
            last = qq;

            for (k = 0;k < CountWords;k++)
            {
                wordUsed[k] = 0;
            }
            wordUsed[ii] = 1;

            while (iteration < CountWords)
            {
                for (jj = 0; jj < CountWords; jj++)
                {
                    for (k = 0; k < CountWords;k++)
                    {
                        if ((wordUsed[k] == 0) && (currentIndex != jj) && (wordStarts[jj] == wordEnds[currentIndex]))
                        {
                            currentIndex = jj;
                            length++;
                            wordUsed[jj] = 1; // слово в этой итерации уже использовали

                            last_fw = *(array_words + (currentIndex + 1) * len + 0);
                            *(new_str + 0) = length;
                            for (qq = 1;qq <= last_fw;qq++)
                            {
                                last = last + 1;
                                *(new_str + last) = *(array_words + (currentIndex + 1) * len + qq);
                            }
                            last = last + 1;
                            *(new_str + last) = ' ';

                            break;
                        }
                    }
                }
                
               iteration++;
            }

            if (length > maxLength) {
                maxLength = length;
               // maxLengthStartIndex = ii;
                max_len = last;
                for (k = 0;k <= max_len; k++)
                {
                    *(max_str + k) = *(new_str + k);
                }
                for (k = 0;k <= last; k++)
                {
                    *(new_str + k) = { '\0' };
                }
            }
        }

        std::cout << "Максимальная длина строки, в которой слова располагаются так, чтобы последняя буква каждого слова, совпадала с первой буквой последующего слова: " << maxLength << "\n";
        for (k = 1;k <= max_len; k++)
        {
            std::cout << *(max_str + k);
        }

        delete[] new_str;
        new_str = nullptr;
        delete[] max_str;
        max_str = nullptr;
        delete[] wordUsed;
        wordUsed = nullptr;
    }
    else
    {
        std::cout << "Введена строка из 1 слова" << "\n";
    }

    delete[] wordStarts;
    wordStarts = nullptr;

    delete[] wordEnds;
    wordEnds = nullptr;
}


int main()
{
    setlocale(LC_ALL, "rus");

    std::cout << "Задание 2. Лишик Ксения. Группа 253505" << "\n";
    std::cout << "В тексте нет слов, начинающихся с одинаковых букв." << "\n";
    std::cout << "Напечатать слова текста в таком порядке, чтобы последняя буква каждого слова, совпадала с первой буквой последующего слова." << "\n";
    std::cout << "Если все слова нельзя напечатать в таком порядке, найти такую цепочку, состоящую из наибольшего количества слов." << "\n" << "\n";

    int Max_Len = 256, max_str = 255, len_str, WordsCount, SameFirstSymbol, l, m;

    int repeat = 1;
    std::string temp_input1;

    do
    {
        // Выделение динамической памяти для массива символов char
        char* str = nullptr;
        str = new char[Max_Len];
        
        while (true)
        {
            // Ввод строки (не более max_str символов)
            str = InputString(str, max_str);

            // Вывод строки, длины строки
            len_str = OutputString(str);

            // Выделение динамической памяти для массива символов char
            char* str1 = nullptr;
            str1 = new char[(len_str+1) * (len_str+1)] {'\0'};

            // Массив слов
            str1 = CreateArrayWords(str, len_str, str1);

            // количество слов
            WordsCount = *(str1 + 0 + 0);
            //std::cout << "NumberWords = " << NumberWords << "\n";

            // проверка, есть ли слова, начинающиеся с одинаковых символов
            SameFirstSymbol = 0;
            for (l = 1; l <= WordsCount;l++)
            {
                for (m = 1; m <= WordsCount;m++)
                {
                    if ((m != l) && (*(str1 + l * len_str + 1) == *(str1 + m * len_str + 1)))
                    {
                        SameFirstSymbol = SameFirstSymbol + 1;
                        break;
                    }
                }
                if (SameFirstSymbol == 1)
                {
                    break;
                }
            }
            //std::cout << "SameFirstSymbol = " << SameFirstSymbol << "\n";

            if (SameFirstSymbol != 0)
            {
                std::cout << "Повторите ввод. Вы ввели в строке слова, начинающиеся с одинаковых букв." << "\n";
                for (l = 0;l < len_str;l++)
                {
                    *(str + l) = '\0';
                }
                delete[] str1;
                str1 = nullptr;
            }
            else
            {
                CreateMaxString(str1, len_str, WordsCount);
                delete[] str1;
                str1 = nullptr;
                break;
            }
        }

        // Освобождение динамической памяти
        delete[] str;
        str = nullptr;

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
