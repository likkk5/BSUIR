#include <iostream>
#include <bitset>

// конвертация числа из 10СС в 2СС 
std::string ConvertDecimalBinary(int k, int m)
{
    int ii = 0;
    std::string temp_str;

    while (k != 0)
    {
        //temp_str += k % 2 + 48;
        //k = k / 2;
        temp_str += (k & 1) + 48;
        k = k >> 1;

        ii = ii + 1;
    }
    std::reverse(temp_str.begin(), temp_str.end());

    while (temp_str.length() < m)
    {
        temp_str = '0' + temp_str;
    }
    return temp_str;
}

int main()
{
    
    for (int i = 65;i <= 90;i++) // заглавные буквы англ.алфавита
    {
        //std::cout << std::bitset<8> (i) << "\n";
        std::cout << ConvertDecimalBinary(i, 8) << "\n";
    }

    for (int i = 97;i <= 122;i++) // строчные буквы англ.алфавита
    {
        //std::cout << std::bitset<8> (i) << "\n";
        std::cout << ConvertDecimalBinary(i, 8) << "\n";
    }
}
