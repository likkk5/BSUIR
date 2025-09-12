#include <iostream>

bool CheckBinaryBit(std::string dec_str, int kk)
{
    bool check = false;
    std::string temp_str, bin_str = "";
    int i = 0, j = 0, q;
    int p = 0;

    for (q = 1;q <= kk;q++)
    {
        // деление на 2
        p = 0;
        j = 0;
        i = 0;
        while (i < dec_str.length() - 1)
        {
            p = p * 10 + (dec_str[i] - 48);
            if (p == 1)
            {
                    p = p * 10 + (dec_str[i + 1] - 48);
                    if (i != 0)
                    {
                        j = j + 1;
                    }
                    i = i + 1;
            }
    
             if (j == 1)
             {
                    temp_str += '0';
                    j = 0;
             }
    
                temp_str += (p / 2 + 48);
                p = p % 2;

       
            i = i + 1;

        }

        if (i == dec_str.length() - 1)
        {
            p = p * 10 + (dec_str[i] - 48);
            temp_str += (p / 2 + 48);
            p = p % 2;
        }

        bin_str += (p + 48); // строка двоичного представления в обратном порядке
        std::cout << "bin_str =" << bin_str << "\n";

        dec_str = "";
        dec_str = temp_str;
        std::cout << "dec_str =" << dec_str << "\n";
        temp_str = "";
        std::cout << "temp_str =" << temp_str << "\n";
        if (dec_str == "")
        {
            break;
        }
    }

    std::cout << "bin_str[" << bin_str.length() - 1 << "] = " << bin_str[bin_str.length() - 1] << "\n";

    if (bin_str.length() < kk)
    {
        for (q = 0;q < kk - bin_str.length();q++)
        {
            bin_str += '0';
        }
    }
    std::cout << "bin_str =" << bin_str << "\n";
    std::cout << "bin_str.length() = " << bin_str.length() << "\n";

    if (bin_str[bin_str.length() - 1] == '0')
    {
        check = true;
    }

    return check;
}


int main()
{
    std::string dec_str;

    std::cin >> dec_str;

    // проверка: k-ый бит в бинарном представлении десятичной строки = 0
    int k = 7;
    std::cout << CheckBinaryBit(dec_str, k) << "\n";
    
}

