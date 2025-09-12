#include <iostream>
#include <string>

std::string symbols = "01"; //Алфавит для двоичной системы счисления

/*// число 10СС в строку 
std::string DecimalString(long long k)
{
    long long ii = 0;
    std::string temp_str;

    while (k != 0)
    {
        temp_str += k % 10 + 48;
        k = k / 10;
        ii = ii + 1;
    }
    std::reverse(temp_str.begin(), temp_str.end());
    return temp_str;
}

long long DecimalStringToNumber(std::string dec_str)
{
    long long num, ii;
    num = 0;

    for (ii = 0; ii < dec_str.length(); ii++)
    {
        num = num * 10 + (int(dec_str[ii]) - 48);
    }
    return num;
}*/

// Сложение
std::string sum(std::string firstNumber, std::string secondNumber, int numberBase)
{
    std::string tempFirst, tempSecond, result;
    int add = 0, i = 0;
    int sum = 0;

    // переворачиваем строки
    std::reverse(firstNumber.begin(), firstNumber.end());
    std::reverse(secondNumber.begin(), secondNumber.end());

    tempFirst = firstNumber;
    tempSecond = secondNumber;

    for (i = 0; i < tempFirst.length(); i++)
    {
        std::size_t foundFirst = symbols.find(tempFirst[i]);
        if (i < tempSecond.length())
        {
            std::size_t foundSecond = symbols.find(tempSecond[i]);
            sum = foundFirst + foundSecond + add;
        }
        else
        {
            sum = foundFirst + add;
        }

        if (sum >= numberBase)
        {
            add = 1;
            result += symbols[sum - numberBase];
        }
        else
        {
            result += symbols[sum];
            add = 0;
        }
    }

    if (add != 0)
    {
        i++;
        result += symbols[1];
    }

    std::reverse(result.begin(), result.end());

    return result;
}

// создание строки на 1 больше, чем предыдущая
std::string CreateDecimalBinary(std::string new_str)
{
    new_str = sum(new_str, "1", 2);
    //std::cout<< new_str<< "\n";
    return new_str;
}

// конвертация строки 10СС  в бинарную строку 
std::string ConvertDecimalStringBinaryString(std::string dec_str)
{
    std::string bin_str;
    return bin_str;
}


// конвертация числа из 10СС в 2СС 
std::string ConvertDecimalBinary(long long k)
{
    long long ii = 0;
    std::string temp_str;

    while (k != 0)
    {
        temp_str += k % 2 + 48;
        k = k / 2;
        ii = ii + 1;
    }
    std::reverse(temp_str.begin(), temp_str.end());
    return temp_str;
}

// проверка является ли десятичное число двудесятичным
bool CheckDecimalBinary(std::string dec_str, std::string bin_str)
{
    bool ch = false;
    long long pos = bin_str.length() - dec_str.length();
    bin_str = bin_str.substr(pos, bin_str.length());
    //std::cout << bin_str << "\n";
    if (dec_str == bin_str)
    {
        ch = true;
    }
    return ch;
}


int main()
{
    long long n, i, count, decimal_num;
    bool check;
    std::string decimal_str;
    std::string binary_str;
    std::cin >> n;

    
    decimal_str += '0';

    if ((n >= 1) && (n <= 10000))
    {
        /*if (n == 1)
        {
            std::cout << "1" << "\n";
        }
        else
        {*/
            i = 2;
            count = 1;
            while (count <= n)
            {
                check = false;
                //binary_str = ConvertDecimalBinary(i);
                decimal_str = CreateDecimalBinary(decimal_str);
                std::cout << decimal_str << "\n";
                count++;
                /*
                binary_str = ConvertDecimalStringBinaryString(decimal_str);
                count++;

                check = CheckDecimalBinary(decimal_str, binary_str);
                //std::cout << check << "\n";
                if (check)
                {
                    count++;
                }

                i = i++;*/
            }
            //std::cout << decimal_num;
         //}
    }
}

