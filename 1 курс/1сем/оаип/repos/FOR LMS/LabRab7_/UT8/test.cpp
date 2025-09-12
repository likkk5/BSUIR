#include "pch.h"
//UT8 - Task8

std::string Convert(long long Number);
std::string Change(std::string input_str);

//7
TEST(TestConvert, TestConvert1)
{
    ASSERT_EQ(Convert(7), "21");
}

TEST(TestConvertChange, TestConvertChange1)
{
   ASSERT_EQ(Change(Convert(7)),"21");
}


//22
TEST(TestConvert, TestConvert2)
{
    ASSERT_EQ(Convert(22), "211");
}

TEST(TestConvertChange, TestConvertChange2)
{
    ASSERT_EQ(Change(Convert(22)), "211");
}



//222
TEST(TestConvert, TestConvert3)
{
    ASSERT_EQ(Convert(222), "22020");
}
TEST(TestConvertChange, TestConvertChange3)
{
    ASSERT_EQ(Change(Convert(222)), "21313");
}


//9
TEST(TestConvert, TestConvert4)
{
    ASSERT_EQ(Convert(9), "100");
}

TEST(TestConvertChange, TestConvertChange4)
{
    ASSERT_EQ(Change(Convert(9)), "23");
}


//2000000000
TEST(TestConvert, TestConvert5)
{
    ASSERT_EQ(Convert(2000000000), "12011101100112020002");
}

TEST(TestConvertChange, TestConvertChange5)
{
    ASSERT_EQ(Change(Convert(2000000000)), "11233323323111312232");
}


std::string Convert(long long Number)
{
    std::string temp_str;
    long long i = 0, len;
    char ch;

    while (Number != 0)
    {
        temp_str += Number % 3 + 48;
        Number = Number / 3;
        i = i + 1;
    }

    len = i;

    for (i = 0; i < len / 2;i++)
    {
        ch = temp_str[i];
        temp_str[i] = temp_str[len - 1 - i];
        temp_str[len - 1 - i] = ch;
    }

    return temp_str;
}

std::string Change(std::string input_str)
{
    long long pos;
    long long len = input_str.length();

    pos = input_str.find("10");
    while (pos + 1)
    {
        input_str[pos] = '0';
        input_str[pos + 1] = '3';
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
        input_str.erase(0, 1);
    }

    return input_str;
}
