#include <iostream>
//#include <string>

std::string Input()
{
	char symbol;
	std::string s = "";
	do
	{
		symbol = getchar();
		s += symbol;

	} while (symbol != '\n');
	
	return s;
}

int Length(std::string s)
{
	int len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	len--;
	return len;
}

int main()
{
	std::string str;
	//getline(std::cin, str);
	str = Input();
	std::cout << Length(str);
	return 0;
}