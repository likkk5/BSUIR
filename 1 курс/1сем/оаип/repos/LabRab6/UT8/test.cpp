#include "pch.h"

// Task8-Test
std::string CheckStrings(std::string s, std::string t, int len_s, int len_t);

TEST(TestCheckStrings, TestCheckStrings1)
{
	std::string ss = "asdfgh";
	std::string tt = "asdfgh";
	int len_ss = ss.length();
	int len_tt = tt.length();
    EXPECT_EQ(CheckStrings(ss, tt, len_ss, len_tt), "YES");
}

TEST(TestCheckStrings, TestCheckStrings2)
{
	std::string ss = "asdfghjkl";
	std::string tt = "asdfghjklkjhgfdsa";
	int len_ss = ss.length();
	int len_tt = tt.length();
	EXPECT_EQ(CheckStrings(ss, tt, len_ss, len_tt), "YES");
}

TEST(TestCheckStrings, TestCheckStrings3)
{
	std::string ss = "asdfghjkl";
	std::string tt = "asdfghjkll";
	int len_ss = ss.length();
	int len_tt = tt.length();
	EXPECT_EQ(CheckStrings(ss, tt, len_ss, len_tt), "NO");
}

TEST(TestCheckStrings, TestCheckStrings4)
{
	std::string ss = "asdfghjkl";
	std::string tt = "bsdfghjkl";
	int len_ss = ss.length();
	int len_tt = tt.length();
	EXPECT_EQ(CheckStrings(ss, tt, len_ss, len_tt), "NO");
}

TEST(TestCheckStrings, TestCheckStrings5)
{
	std::string ss = "asdfghjkl";
	std::string tt = "rty";
	int len_ss = ss.length();
	int len_tt = tt.length();
	EXPECT_EQ(CheckStrings(ss, tt, len_ss, len_tt), "NO");
}

TEST(TestCheckStrings, TestCheckStrings6)
{
	std::string ss = "asdfghjkl";
	std::string tt = "dfghjklkjhg";
	int len_ss = ss.length();
	int len_tt = tt.length();
	EXPECT_EQ(CheckStrings(ss, tt, len_ss, len_tt), "YES");
}

TEST(TestCheckStrings, TestCheckStrings7)
{
	std::string ss = "aaa";
	std::string tt = "aaaaa";
	int len_ss = ss.length();
	int len_tt = tt.length();
	EXPECT_EQ(CheckStrings(ss, tt, len_ss, len_tt), "YES");
}

std::string CheckStrings(std::string s, std::string t, int len_s, int len_t)
{
	int j, pos, pred_pos, stop_pos, len_check;
	char ch;

	stop_pos = 0;
	pred_pos = 0;
	len_check = 0;

	// идем направо
	for (j = 0; j < len_t; j++)
	{
		pos = s.find(t[j], pred_pos);

		if (pos != std::string::npos)
		{
			pred_pos = pos + 1;
			len_check = len_check + 1;
			stop_pos = j;
		}
		else
		{
			stop_pos = stop_pos + 1;
			pred_pos = 1;
			break;
		}
	}

	if (len_check == len_t)
	{
		return "YES";
	}
	else
	{
		// идем налево
		// переворачиваем строку s 
		for (j = 0;j < len_s / 2;j++)
		{
			ch = s[j];
			s[j] = s[len_s - 1 - j];
			s[len_s - 1 - j] = ch;
		}

		for (j = stop_pos; j < len_t; j++)
		{
			pos = s.find(t[j], pred_pos);

			if (pos != std::string::npos)
			{
				pred_pos = pos + 1;
				len_check = len_check + 1;
			}
			else
			{
				break;
			}
		}

		if (len_check == len_t)
		{
			return "YES";
		}
		else
		{
			return "NO";
		}
	}
}