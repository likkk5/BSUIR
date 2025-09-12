#include <iostream>
#include <string>

// перевод из 10СС в 3СС O(n)
std::string Convert(long long Number)
{
    std::string temp_str;
    long long i=0, len;
    char ch;

    while (Number != 0)
    {
        temp_str += Number % 3 + 48;
        Number = Number / 3;
        i = i + 1;
    }
    
    len = i;

    for (i = 0; i < len/2;i++)
    {
        ch = temp_str[i];
        temp_str[i] = temp_str[len - 1 - i] ;
        temp_str[len - 1 - i] = ch;
    }

    return temp_str;
}

// Замена "10" на "03", "20" на "13", "30" на "23" O(n)
std::string Change(std::string input_str)
{
    long long pos;
    long long len = input_str.length();

    pos = input_str.find("10");
    while (pos+1)
    {
        input_str[pos] = '0';
        input_str[pos+1] = '3';
        pos = input_str.find("10");
    }
    
    pos = input_str.find("20");
    while (pos + 1)
    {
        input_str[pos] = '1';
        input_str[pos + 1] = '3';
        pos = input_str.find("20");
    }

    pos = input_str.find("30");
    while (pos + 1)
    {
        input_str[pos] = '2';
        input_str[pos + 1] = '3';
        pos = input_str.find("30");
    }
    
    if (input_str[0] == '0')
    {
        input_str.erase(0,1);
    }

    return input_str;
}

int main()
{
    long long n;
    std::cin >> n;
    if ((n >= 1) && (n <= 2 * 1000000000))
    {
        std::string str = Convert(n);
        std::cout << Change(str);
    }
    return 0;
}
