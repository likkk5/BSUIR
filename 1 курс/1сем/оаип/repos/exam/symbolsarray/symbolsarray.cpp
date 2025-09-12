//Дан массив символов, убрать лишние пробелы в словах, чтобы их было не больше одного между буквами и другими символами
#include <iostream>

char* Deleteprob(char s1[], int sizes)
{
	for (int i = 0; i < sizes - 1; i++)
	{
		if ((s1[i] == ' ') && (s1[i+1] == ' '))
		{
			for (int j = i+1; j < sizes - 1; j++)
			{
	 			s1[j] = s1[j + 1];
			}
			i--;
		}
	}
    return s1;
}
void Print(char s1[], int sizes)
{
	int i = 0;
	while (s1[i] != '\n')
	{
		std::cout << s1[i];
		i++;
	}
	std::cout << "\n";
}


int main()
{
	const int max_size = 200;

	char* ar = nullptr;
	ar = new char[max_size] {'\0'};

	int i = 0;
	int size = 0;
	char c;
	do
	{
	    c = getchar();
		ar[i] = c;
		i++;
	} while (c != '\n');
	size = i;

	ar = Deleteprob(ar, size);
	Print(ar, size);

	delete[] ar;

}