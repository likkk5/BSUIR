#include "pch.h"

// Task5-Test
int CountStrings(int l, int m, std::string s1, std::string s2);
unsigned long long x(unsigned long long kk, unsigned long long nn, unsigned long long mm);
unsigned long long IncludeString(std::string str1, std::string str2, unsigned long long len_str1);


TEST(TestCountStrings, TestCountStrings1)
{
	EXPECT_EQ(CountStrings(9, 1000, "code", "cup"), 352);
}

TEST(TestCountStrings, TestCountStrings2)
{
	EXPECT_EQ(CountStrings(7, 1000, "code", "cup"), 2);
}

TEST(TestCountStrings, TestCountStrings3)
{
	EXPECT_EQ(CountStrings(6, 1000, "code", "cup"), 0);
}

TEST(TestCountStrings, TestCountStrings4)
{
	EXPECT_EQ(CountStrings(11, 1000, "codecup", "cupcode"), 1);
}

TEST(TestCountStrings, TestCountStrings5)
{
	EXPECT_EQ(CountStrings(10, 1000, "codecup", "cupcode"), 1);
}

TEST(TestCountStrings, TestCountStrings6)
{
	EXPECT_EQ(CountStrings(8, 1000, "codecup", "cupcode"), 0);
}

TEST(TestCountStrings, TestCountStrings7)
{
	EXPECT_EQ(CountStrings(1000000000, 10000, "russia", "cup"), 9552);
}

TEST(TestCountStrings, TestCountStrings8)
{
	EXPECT_EQ(CountStrings(6, 10000, "cup", "cup"), 1);
}

TEST(TestCountStrings, TestCountStrings9)
{
	EXPECT_EQ(CountStrings(5, 10000, "codecup", "cup"), 0);
}

TEST(TestCountStrings, TestCountStrings10)
{
	EXPECT_EQ(CountStrings(5, 10000, "codec", "c"), 1);
}

TEST(TestCountStrings, TestCountStrings11)
{
	EXPECT_EQ(CountStrings(6, 10000, "upde", "deup"), 2);
}

TEST(TestCountStrings, TestCountStrings12)
{
	EXPECT_EQ(CountStrings(2, 10000, "cup", "cup"), 0);
}

TEST(TestCountStrings, TestCountStrings13)
{
	EXPECT_EQ(CountStrings(8, 10000, "cup", "cup"), 676);
}

int CountStrings(int l, int m, std::string s1, std::string s2)
{
	unsigned long long k = 26, n;
	unsigned long long pos1, pos2;

	unsigned long long len1 = s1.length();
	unsigned long long len2 = s2.length();


	if ((l > len1 + len2) && (s1 == s2))
	{
		n = l - len1 - len2;
		return (1 * x(k % m, n, m)) % m;
	}

	if ((l > len1 + len2) && (s1 != s2))
	{
		n = l - len1 - len2;
		return (2 * x(k % m, n, m)) % m;
	}

	if ((l == len1 + len2) && (s1 == s2))
	{
		return 1;
	}
	if ((l == len1 + len2) && (s1 != s2))
	{
		return 2;
	}

	if (l < len1 + len2)
	{
		if ((len1 > l) || (len2 > l))
		{
			return 0;
		}
		else
		{
			// префикс и суффикс идентичны и их длина совпадает с длиной строки
			if ((s1 == s2) && (len1 == l))
			{
				return 1;
			}
			else
			{
				pos1 = IncludeString(s1, s2, len1);
				pos2 = IncludeString(s2, s1, len2);

				// префикс и суффикс не имеют пересечений
				if ((pos1 == -1) && (pos2 == -1))
				{
					return 0;
				}

				// часть префикса входит в суффикс
				if ((pos1 == -1) && (pos2 != -1))
				{
					if (pos2 + len1 == l)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}

				// часть суффикса входит в префикс
				if ((pos1 != -1) && (pos2 == -1))
				{
					if (pos1 + len2 == l)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}

				// часть префикса входит в суффикс и наоборот
				if ((pos1 != -1) && (pos2 != -1))
				{
					if ((pos1 + len2 == l) && (pos2 + len1 == l) && (len1 < l) && (len2 < l))
					{
						return 2;
					}
					else
					{
						if (((pos1 + len2 == l) && (pos2 + len1 != l)) || ((pos1 + len2 != l) && (pos2 + len1 == l)) || (len1 == l) || (len2 == l))
						{
							return 1;
						}
						else
						{

							return 0;
						}
					}
				}
			}
		}
	}
}

unsigned long long x(unsigned long long kk, unsigned long long nn, unsigned long long mm)
{
	if (nn == 0)
	{
		return 1;
	}
	if (nn % 2 != 0)
	{
		return (kk * x((kk * kk) % mm, nn / 2, mm)) % mm;
	}
	return x((kk * kk) % mm, nn / 2, mm);
}

unsigned long long IncludeString(std::string str1, std::string str2, unsigned long long len_str1)
{
	long long p = -1, count = 0, ii = 0;
	for (unsigned long long j = 0; j < len_str1;j++)
	{
		if (str2[0] == str1[len_str1 - 1 - j])
		{
			p = len_str1 - 1 - j;
			break;
		}
	}

	if (p != -1)
	{
		count = 0;
		ii = 0;
		for (unsigned long long j = p; j < len_str1;j++)
		{
			if (str2[ii] == str1[j])
			{
				count = count + 1;
			}
			ii = ii + 1;
		}
		if (count != len_str1 - p)
		{
			p = -1;
		}
	}

	return p;
}