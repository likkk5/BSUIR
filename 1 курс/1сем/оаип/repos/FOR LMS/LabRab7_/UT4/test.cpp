#include "pch.h"
//UT4 - Task4

std::string to_roman(unsigned int num);

TEST(Test_to_roman, Test_to_roman1)
{
    ASSERT_EQ(to_roman(1), "I");
}

TEST(Test_to_roman, Test_to_roman2)
{
    ASSERT_EQ(to_roman(3), "III");
}

TEST(Test_to_roman, Test_to_roman3)
{
    ASSERT_EQ(to_roman(4), "IV");
}

TEST(Test_to_roman, Test_to_roman4)
{
    ASSERT_EQ(to_roman(5), "V");
}

TEST(Test_to_roman, Test_to_roman5)
{
    ASSERT_EQ(to_roman(8), "VIII");
}

TEST(Test_to_roman, Test_to_roman6)
{
    ASSERT_EQ(to_roman(9), "IX");
}

TEST(Test_to_roman, Test_to_roman7)
{
    ASSERT_EQ(to_roman(10), "X");
}

TEST(Test_to_roman, Test_to_roman8)
{
    ASSERT_EQ(to_roman(12), "XII");
}

TEST(Test_to_roman, Test_to_roman9)
{
    ASSERT_EQ(to_roman(40), "XL");
}

TEST(Test_to_roman, Test_to_roman10)
{
    ASSERT_EQ(to_roman(0), "");
}


std::string to_roman(unsigned int num)
{
    int p = 13;
    unsigned int a_num[13] = { 1,4,5,9,10,40,50,90,100,400,500,900,1000 };
    std::string r_str[13] = { "I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M" };
    std::string result;

    while (p--)
    {
        while (num >= a_num[p])
        {
            num -= a_num[p];
            result += r_str[p];
        }
    }

    return result;
}