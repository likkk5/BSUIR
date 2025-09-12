#include <iostream>
#include <string>

// O(log n)
std::string to_roman(unsigned int num) 
{
    int p = 13;
    unsigned int a_num[13] = { 1,4,5,9,10,40,50,90,100,400,500,900,1000 };
    std::string r_str[13] = { "I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M" };
    std::string result;

    while (p--)
    {
        //std::cout << "p = " << p << "\n";
        while (num >= a_num[p])
        {
            num -= a_num[p];
            //std::cout << "num = " << num << "\n";
            result += r_str[p];
            //std::cout << r_str[p] << "\n";
        }
    }

    return result;
}

int main()
{
    unsigned int arabian;
    std::cin >> arabian;
   
    if ((arabian >= 1)&&(arabian <= 3999))
    {
        std::cout << to_roman(arabian);
    }
}