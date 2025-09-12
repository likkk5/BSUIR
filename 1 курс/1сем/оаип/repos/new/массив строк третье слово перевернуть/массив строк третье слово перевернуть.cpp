// массив строк третье слово перевернуть

#include <iostream>
#include <string>

std::string* Input(std::string* s, int nn)
{
    for (int i = 0; i < nn; i++)
    {
         std::cin>>s[i];
    }
    return s;
}

/*
std::string* ConvertWord(std::string* s, int nn)
{
    int count, begin3;
    int len3 = 0;
    for (int i = 0; i < nn;i++)
    {
        count = 0;
        for (int j = 0; j < s[i].length() - 1;j++)
        {
            if ((s[i][j] == ' ') && (s[i][j + 1] != ' '))
            {
                count++;
                if (count == 2)
                {
                    begin3 = j;
                    while (s[i][j] != ' ')
                    {
                        len3++;
                    }
                    for (int k = begin3; k < len3 / 2;k++)
                        s[i][j] = s[i][len3 - 1 - k];
                    break;
                }
            }
        }
    }
    return s;
}*/

std::string* Convert3Words(std::string* s, int nn)
{
    int i , j , len;
    for (i = 0; i < nn;i++)
    {
        if ((i + 1) % 3 == 0)
        {
            len = s[i].length();
            for (int j = 0; j < len / 2; j++)
                std::swap(s[i][j],s[i][len - 1 - j]);
        }
    }
    return s;
}


void Print(std::string* s, int nn)
{
    for (int i = 0; i < nn; i++)
    {
        std::cout << s[i] << "\n";
    }
}

int main()
{
    int n;
    std::cin >> n; // количество строк в массиве

    // Выделение динамической памяти для массива строк
    std::string* str;
    str = new std::string[n];
    str = Input(str, n);
    
    str = Convert3Words(str, n);

    Print(str, n);

    delete[] str;
    return 0;
}
