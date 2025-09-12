#include <iostream>
#include <string>


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
	int leng,i=0, count=0;
	std::string str, newstr;
	getline(std::cin, str);
	leng = Length(str);
	for (int j = 0; j < leng; leng++)
	{
		if (str[j] = ' ')
		{
			while ((str[i] != ' ') || str[i] != '\n')
			{
				newstr += str[i];
				leng++; 
				{
					for (i = 0; i < leng / 2; i++)
					{
						if (newstr[i] == newstr[leng - 1 - i])
							count++;
						if (count == leng / 2)
						{
							for (i = 0; i < leng; i++)
							{
								std::cout << newstr[i];
							}
							std::cout << "\n";
						}
					}
				}
			}
			count = 0; leng = 0;
		}
	}


	return 0;

}