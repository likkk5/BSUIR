#include "number.h"

NumberPtr num1 = NULL, num2 = NULL, numRes = NULL;

NumberPtr createNumber(Bitness bitness)
{
	NumberPtr result = (NumberPtr)malloc(sizeof(Number));
	if (result == NULL) return NULL;
	int _countBits = countBits(bitness);	
	if (bitness == wrong)
		result->data = NULL;
	else
		result->data = (bool*)malloc((unsigned int)_countBits*sizeof(bool));
	for (int i = --_countBits; i >= 0; i--)
		result->data[i] = false;
	result->bitness = bitness;
	return result;
}

NumberPtr copyNumber(NumberPtr number)
{
	if (!correctNumber(number))
		return NULL;
	NumberPtr result = createNumber(number->bitness);
	if (result == NULL) return NULL;
	int _countBits = countBits(result->bitness);
	for (int i = --_countBits; i >= 0; i--)
		result->data[i] = number->data[i];
	return result;
}

void deleteNumber(NumberPtr number)
{
	if (number == NULL)
		return;
	if (number->data != NULL)
		free(number->data);
	free(number);
}

bool correctNumber(NumberPtr number)
{
	if (number == NULL)
		return false;
	else if (number->bitness == wrong)
		return false;
	else if (number->data == NULL)
		return false;
	return true;
}

void setZeroNumber(NumberPtr number)
{
	if (!correctNumber(number))
		return;
	int _countBits = countBits(number->bitness);
	for (int i = --_countBits; i >= 0; i--)
		number->data[i] = false;
}

void incNumber(NumberPtr number)
{
	if (!correctNumber(number))
		return;
	int _countBits = countBits(number->bitness);
	/*
	 * bit over|bit over
	 * 0	0	0	0
	 * 0	1	1	0
	 * 1	0	1	0
	 * 1	1	0	1
	*/
	bool inc = true;
	bool overflow = false;//установка переполнения в 1
	bool sign = number->data[0];//знак числа
	for (int i = --_countBits; i >= 0; i--)
	{
		_inc3bits(number->data[i],inc,overflow,&number->data[i],&overflow);
		inc = false;
	}
	//проверка знака до проверки на переполнение
	if (sign != number->data[0])
		number->bitness = wrong;
	if (overflow)//если результат больше 11..11, то 0
		setZeroNumber(number);
}

void inverseNumber(NumberPtr number)
{
	if (!correctNumber(number))
		return;
	int _countBits = countBits(number->bitness);
	for (int i = --_countBits; i >= 0; i--)
		number->data[i] = !number->data[i];
}

void negateNumber(NumberPtr number)
{
	inverseNumber(number);
	incNumber(number);
}

void lshNumberDegree(NumberPtr number, int degree2, bool *correct)
{
	for (int i = 0; i < degree2; i++)
	{
		lshNumber(number, correct);
		if (*correct == false)
			return;
	}

}

void rshNumberDegree(NumberPtr number, int degree2)
{
	for (int i = 0; i < degree2; i++)
		rshNumber(number);
}

void lshNumber(NumberPtr number, bool *correct)
{
	if (!correctNumber(number))
	{
		*correct = false;
		return;
	}
	int _countBits = countBits(number->bitness);
	bool sign = number->data[0];

	//проверка на переполнение
	if (number->data[1] != sign)
	{
		*correct = false;
		return;
	}
	for (int i = 0, j = 1; i < _countBits; i++, j++)
		if (j < _countBits)
			number->data[i] = number->data[j];
		else
			number->data[i] = false;
	*correct = true;
}

void rshNumber(NumberPtr number)
{
	if (!correctNumber(number))
		return;
	int _countBits = countBits(number->bitness);//8
	int i = _countBits; i--;//7
	int j = _countBits; j--; j--;//6
	for (; j>=0 ; i--, j--)
		number->data[i] = number->data[j];
}

void expandBitnessNumber(NumberPtr number, Bitness bitness)
{
	if (!correctNumber(number))
		return;
	if (number->bitness >= bitness)
		return;
	bool sign = number->data[0];
	bool* temp = number->data;
	int _countBits = countBits(bitness);
	int _countBitsLast = countBits(number->bitness);
	number->data = (bool*)malloc((unsigned int)_countBits*sizeof(bool));
	for (int i = --_countBits, j = --_countBitsLast; i >= 0; i--, j--)
		if (j >= 0)
			number->data[i] = temp[j];
		else
			number->data[i] = sign;
	number->bitness = bitness;
	free(temp);
}

NumberPtr addNumber(NumberPtr number1, NumberPtr number2)
{
	if (!correctNumber(number1) || !correctNumber(number2))
		return NULL;
	if (number1->bitness != number2->bitness)
		return NULL;
	NumberPtr result = createNumber(number1->bitness);
	if (result == NULL) return NULL;
	int _countBits = countBits(number1->bitness);
	bool overflow = false;
	for (int i = --_countBits; i >= 0; i--)
		_inc3bits(number1->data[i],number2->data[i],overflow,&result->data[i],&overflow);
	return result;
}

NumberPtr subNumber(NumberPtr number1, NumberPtr number2)
{
	NumberPtr numcopy2 = copyNumber(number2);
	negateNumber(numcopy2);
	outputNumber(numcopy2,Binary);
	NumberPtr result = addNumber(number1, numcopy2);
	deleteNumber(numcopy2);
	return result;
}

NumberPtr mulNumber(NumberPtr number1, NumberPtr number2)
{
	if (!correctNumber(number1) || !correctNumber(number2))
		return NULL;
	if (number1->bitness != number2->bitness)
		return NULL;
	//проверка на максимальное количество бит
	int bitnessMax = (int)number1->bitness | (int)number2->bitness;
	if (bitnessMax == qword)
		return NULL;
	//увеличение разрядов, т.к. результат получится в два раза больше
	bitnessMax++;

	NumberPtr result = createNumber((Bitness)(bitnessMax));
	NumberPtr numcopy1 = copyNumber(number1);
	if (numcopy1 == NULL) return NULL;
	NumberPtr numcopy2 = copyNumber(number2);
	if (numcopy2 == NULL) return NULL;
	expandBitnessNumber(numcopy1, (Bitness)(bitnessMax));
	expandBitnessNumber(numcopy2, (Bitness)(bitnessMax));

	bool correct;
	bool signResult = numcopy1->data[0] ^ numcopy2->data[0];
	if (numcopy1->data[0]) negateNumber(numcopy1);
	if (numcopy2->data[0]) negateNumber(numcopy2);

	NumberPtr lastSum = NULL;
	int _countBits = countBits(numcopy1->bitness);
	for (int i = --_countBits; i > 0; i--)
	{//i > 0, потому что знаковый разряд [0] не умножается
		if (numcopy1->data[i])
		{
			lastSum = result;
			result = addNumber(lastSum, numcopy2);
			deleteNumber(lastSum);
		}
		if (result == NULL) break;
		lshNumber(numcopy2, &correct);
		if (!correct)
			break;
	}
	deleteNumber(numcopy1);
	deleteNumber(numcopy2);
	if (result && signResult)
		negateNumber(result);
	return result;
}

char* NumberToStr(NumberPtr number, TypeNumber type)
{
	if (!correctNumber(number))
		return NULL;
	int shift = (type == Binary) ? 0 : 2;
	int _countBits = countBits(number->bitness);//count=32
	int length = _countBits >> shift;//l=32
	length++; length++;//чтобы учесть нуль-терминатор и знак//l=34
	char *resStr = (char*)malloc((unsigned int)length*sizeof(char));
	resStr[--length]='\0';//l=33

	bool sign = number->data[0];
	NumberPtr numberCopy = copyNumber(number);
	if (numberCopy == NULL) return resStr;
	numberCopy->data[0] = false; // установка знакового символа в 0
	if (sign)
		negateNumber(numberCopy);

	if (type == Binary)
	{
		for (int i = --_countBits, l = --length; i > 0; i--, l--)
		{
			//i > 0, потому что знаковый разряд [0] не учитывается
			resStr[l] = _intToBinChar(numberCopy->data[i]);
			if (resStr[l] == '\0')
				break;
		}
		resStr[1] = '0';
	}
	else if (type == Hexadecimal)
	{
		bool *p = NULL;
		int l = --length;
		p = &numberCopy->data[_countBits];
		while (l > 0)
		{
			p--; p--; p--; p--;
			resStr[l] = _dataToHexChar(p);
			l--;
		}
		//for (int i = _countBits >> shift, l = --length; i >= 0; i = i >> shift, l--)
		//	resStr[l] = _dataToHexChar(&numberCopy->data[i]);
	}
	resStr[0] = (sign ? '-' : '+');
	deleteNumber(numberCopy);
	return resStr;
}

NumberPtr StrToNumber(char* str, TypeNumber type)
{
	int number = 0;
	int length = (int)strlen(str);
	int shift = (type == Binary) ? 0 : 2;
	bool sign = false;
	if (str[0] == '-')
	{
		sign = true;
	}
	for (int i = --length; i >= 0; i--)//length = 7, i = 7
	{
		if (sign == true && i == 0)
			break;
		int temp = _charToInt(str[i], type);
		if (temp == -1)
			return NULL;
		temp = temp << ((length - i) << shift);
		number = number | temp;
	}
	if (sign)
		number = -number;
	return IntToNumber(number);
}

int NumberToInt(NumberPtr number)
{
	if (!correctNumber(number))
		return 0;
	int _countBits = countBits(number->bitness);
	int result = 0;
	for (int i = --_countBits; i > 0; i--)
	{//i > 0, потому что знаковый разряд [0] не суммируется
		result = result | (number->data[i] << (_countBits - i));
	}
	if (number->data[0])//если меньше нуля
		result = -result;
	return result;
}

NumberPtr IntToNumber(int num)
{
	NumberPtr result = createNumber(dword);
	if (result == NULL) return NULL;
	int _countBits = countBits(result->bitness);
	bool sign = num < 0;
	if (sign) num = -num;
	for (int i = --_countBits; i >= 0; i--)
	{//1 1 0
		result->data[i] = (num & 1);
		num = num >> 1;
	}
	if (sign)
		negateNumber(result);
	return result;
}

NumberPtr inputNumber(TypeNumber type)
{
	char buffer[256];
	scanf("%s",buffer);
	return StrToNumber(buffer, type);
}

void outputNumber(NumberPtr number, TypeNumber type)
{
	char *str = NumberToStr(number, type);
	if (str == NULL)
		printf_s("%s", "wrong number");
	printf("%s\n", str);
	if (str != NULL)
		free(str);
}

void _outputNumberBits(NumberPtr number)
{
	if (!correctNumber(number))
		return;
	int _countBits = countBits(number->bitness);//count=32
	for (int i = 0; i < _countBits; i++)
		putchar(_intToBinChar(number->data[i]));
	putchar('\n');
}

void _inc2bits(bool b1, bool b2, bool *result, bool *overflowOut)
{
	*result = b1 ^ b2;
	*overflowOut = b1 & b2;
}

void _inc3bits(bool b1, bool b2, bool overflowIn, bool *result, bool *overflowOut)
{
	bool result12, overflow12;
	_inc2bits(b1,b2, &result12, &overflow12);
	*result = result12 ^ overflowIn;
	bool or12 = b1 | b2;
	*overflowOut = (or12 & overflowIn) | overflow12;
}

int _charToInt(char _char, TypeNumber type)
{
	if (type == Binary)
	{
		if (_char == '0')
			return 0;
		else if (_char == '1')
			return 1;
	}
	else if (type == Hexadecimal)
	{
		if (_char == '0')
			return 0;
		else if (_char == '1')
			return 1;
		else if (_char == '2')
			return 2;
		else if (_char == '3')
			return 3;
		else if (_char == '4')
			return 4;
		else if (_char == '5')
			return 5;
		else if (_char == '6')
			return 6;
		else if (_char == '7')
			return 7;
		else if (_char == '8')
			return 8;
		else if (_char == '9')
			return 9;
		else if (_char == 'A' || _char == 'a')
			return 10;
		else if (_char == 'B' || _char == 'b')
			return 11;
		else if (_char == 'C' || _char == 'c')
			return 12;
		else if (_char == 'D' || _char == 'd')
			return 13;
		else if (_char == 'E' || _char == 'e')
			return 14;
		else if (_char == 'F' || _char == 'f')
			return 15;
	}
	return -1;
}

char _intToBinChar(int _int)
{
	if (_int == 0)
		return '0';
	else if (_int == 1)
		return '1';
	else
		return '\0';
}

char _dataToHexChar(bool* data)
{//в data находится адрес текущего и трех последовательных бит
 //для преобразования в символ
	int tempRez = 0;
	for(int i = 3, j = 0; i >= 0; i--, j++)
		tempRez = tempRez | (data[i] << j);
	if (tempRez == 0)
		return '0';
	else if (tempRez == 1)
		return '1';
	else if (tempRez == 2)
		return '2';
	else if (tempRez == 3)
		return '3';
	else if (tempRez == 4)
		return '4';
	else if (tempRez == 5)
		return '5';
	else if (tempRez == 6)
		return '6';
	else if (tempRez == 7)
		return '7';
	else if (tempRez == 8)
		return '8';
	else if (tempRez == 9)
		return '9';
	else if (tempRez == 10)
		return 'A';
	else if (tempRez == 11)
		return 'B';
	else if (tempRez == 12)
		return 'C';
	else if (tempRez == 13)
		return 'D';
	else if (tempRez == 14)
		return 'E';
	else if (tempRez == 15)
		return 'F';
	else
		return '\0';
}
