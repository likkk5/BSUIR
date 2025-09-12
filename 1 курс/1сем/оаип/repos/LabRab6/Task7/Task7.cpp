#include <iostream>
#include <string>

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

int main()
{
	std::string s;
	long long len_s;
	
	std::cin >> s;
	len_s = s.length();

	if ((len_s >= 1) && (len_s <= 100000))
	{
		std::cout << MaxNoPalindrom(s, len_s);
	}
	
	return 0;
}

