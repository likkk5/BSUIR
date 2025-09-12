// Ввести две даты и определить количество лет между ними

#include <iostream>
int Convert(std::string s)
{
	int year;
	year = (s[6] - 48) * 1000 + (s[7] - 48) * 100 + (s[8] - 48) * 10 + (s[9] - 48);
	return year;
}

int main()
{
	std::string s1, s2;
	std::cin >> s1;
	std::cin >> s2;
	
	int year1, year2, sub;
	year1 = Convert(s1);
	year2 = Convert(s2);
	sub = abs(year1-year2);
	std::cout << sub;
	return 0;
}
