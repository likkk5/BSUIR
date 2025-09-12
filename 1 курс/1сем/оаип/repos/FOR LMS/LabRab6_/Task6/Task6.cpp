#include <iostream>

long long Factorial(int x)
{
    if (x == 0)
    {
        return 1;
    }
    else
    {
        return x * Factorial(x - 1);
    }
}

long long CountAnagram(char s[], int len_s)
{
    int i = 0, j, p = 0, q = 0;
    long long anagram=0;
    int count_symbols[14]{ 0 };

    for (j = 0;j < 127; j++)
    {
        q = 0;
        for (i = 0;i < len_s;i++)
        {
            if (s[i] == j)
            {
                q = q + 1;
            }
        }

        if (q != 0)
        {
            count_symbols[p] = q;
            p = p + 1;
        }
    }

    anagram = Factorial(len_s);

    for (i = 0; i < p; i++)
    {
        anagram = anagram / Factorial((count_symbols[i]));
    }
    return anagram;

}

int main()
{
    int ii = 0, len_str;
    char str[256]{'\0'};
    char c;

    std::cin >> str;
       
    ii = 0;
    do
    {
       ii++;
    } while (str[ii] != '\0');
    len_str = ii;

    if (len_str <= 14)
    {
        std::cout << CountAnagram (str, len_str);
    }

    return 0;
}
