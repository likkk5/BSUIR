#include "number.h"

char menu(void);

int main(void)
{
	puts("enter the first number");
	NumberPtr num1 = inputNumber(Hexadecimal);
	puts("enter the second number");
	NumberPtr num2 = inputNumber(Hexadecimal);
	NumberPtr numRes = NULL;
	char action = menu();
	switch (action)
	{
	case '+':
		numRes = addNumber(num1, num2);
		break;
	case '-':
		numRes = subNumber(num1, num2);
		break;
	case '*':
		numRes = mulNumber(num1, num2);
		break;
	}
	outputNumber(numRes, Hexadecimal);
	deleteNumber(num1);
	deleteNumber(num2);
	deleteNumber(numRes);
	return 0;
}

char menu(void)
{
	fflush(stdin);
	puts("Enter action you wanted to calculate: +, - or *");
	char result = (char)getchar();
	if (result == '+' || result == '-' || result == '*')
		return result;
	else
	{
		puts("error input");
		return menu();
	}
}
