#include "pch.h"

// Task7-Test
int MaxNoPalindrom(std::string str, int len_str);

TEST(TestMaxNoPalindrom, TestMaxNoPalindrom1)
{
	std::string s = "asdfgh";
	int len_s = s.length();
	EXPECT_EQ(MaxNoPalindrom(s, len_s), 6);
}

TEST(TestMaxNoPalindrom, TestMaxNoPalindrom2)
{
	std::string s = "aaaaaaaaa";
	int len_s = s.length();
	EXPECT_EQ(MaxNoPalindrom(s, len_s), -1);
}

TEST(TestMaxNoPalindrom, TestMaxNoPalindrom3)
{
	std::string s = "ababa";
	int len_s = s.length();
	EXPECT_EQ(MaxNoPalindrom(s, len_s), 4);
}

int MaxNoPalindrom(std::string str, int len_str)
{
	long long i, c = 0;

	// если все символы в строке одинаковые, то не будет не палиндрома 
	for (i = 1; i < len_str;i++)
	{
		if (str[i] == str[0])
		{
			c = c + 1;
		}
	}
	if (c == len_str - 1)
	{
		return -1;
	}
	else
	{
		c = 0;
		// является ли строка палиндромом
		for (i = 0; i < len_str / 2;i++)
		{
			if (str[i] == str[len_str - 1 - i])
			{
				c = c + 1;
			}
		}
		if (c == len_str / 2)
		{
			return len_str - 1;
		}
		else
		{
			return len_str;
		}
	}
}
