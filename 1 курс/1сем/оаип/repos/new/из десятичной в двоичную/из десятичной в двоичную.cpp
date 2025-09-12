// из десятичной в двоичную

#include <iostream>

// конвертация числа из 10СС в 2СС 
std::string ConvertDecimalBinary(int k)//, int m)
{
    std::string temp_str;

    while (k != 0)
    {
        temp_str += k % 2 + 48;
        k = k / 2;
    }
    std::reverse(temp_str.begin(), temp_str.end());

    /*while (temp_str.length() < m)
    {
        temp_str = '0' + temp_str;
    }*/
    return temp_str;
}

int main()
{
    int n;
    std::cin >> n;

    std::cout << ConvertDecimalBinary(n) << "\n";
}
