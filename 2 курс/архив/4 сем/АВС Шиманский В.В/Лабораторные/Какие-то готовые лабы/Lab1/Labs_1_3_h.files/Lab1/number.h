#ifndef FUNC_H
#define FUNC_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bitness.h"

typedef enum _TypeNumber
{
	Binary,
	Hexadecimal
} ///тип строкового представления числа
TypeNumber;

typedef struct _Number
{
	bool *data;
	Bitness bitness;
} ///структура, представляющая число
Number;

///указатель на число
typedef Number* NumberPtr;

///создает число размерностью bitness
NumberPtr createNumber(Bitness bitness);
///создает полную копию числа
NumberPtr copyNumber(NumberPtr number);
///удаляет число
void deleteNumber(NumberPtr number);
///проверяет число на корректность данных
bool correctNumber(NumberPtr number);

///присваивает числу нуль
void setZeroNumber(NumberPtr number);
///инкрементирует число
void incNumber(NumberPtr number);
///инверсирует число
void inverseNumber(NumberPtr number);
///меняет знак числа на противоположный
void negateNumber(NumberPtr number);

///сдвигает число влево на degree2 бит, проверяет сдвиг на корректность
void lshNumberDegree(NumberPtr number, int degree2, bool *correct);
///сдвигает число вправо на degree2 бит
void rshNumberDegree(NumberPtr number, int degree2);
///сдвигает число влево на 1 бит, проверяет сдвиг на корректность
void lshNumber(NumberPtr number, bool *correct);
///сдвигает число вправо на 1 бит
void rshNumber(NumberPtr number);

///расширяет память числа до размерности bitness, если она больше текущей
void expandBitnessNumber(NumberPtr number, Bitness bitness);

///суммирует два числа, возвращает новое число
NumberPtr addNumber(NumberPtr number1, NumberPtr number2);
///вычитает два числа, возвращает новое число
NumberPtr subNumber(NumberPtr number1, NumberPtr number2);
///умножает два числа, возвращает новое число размерностью в два раза больше
NumberPtr mulNumber(NumberPtr number1, NumberPtr number2);

///конвертирует число в строку
char* NumberToStr(NumberPtr number, TypeNumber type);
///конвертирует строку в число, возвращает новое число
NumberPtr StrToNumber(char* str, TypeNumber type);

///конвертирует число в int
int NumberToInt(NumberPtr number);
///конвертирует int в число
NumberPtr IntToNumber(int num);

///вводит число из консоли
NumberPtr inputNumber(TypeNumber type);
///выводит число в консоль
void outputNumber(NumberPtr number, TypeNumber type);
///выводит биты числа в консоль
void _outputNumberBits(NumberPtr number);

///суммирует два бита, возвращает результат и переполнение
void _inc2bits(bool b1, bool b2, bool *result, bool *overflowOut);
///суммирует три бита, возвращает разультат и переполнение
void _inc3bits(bool b1, bool b2, bool overflowIn, bool *result, bool *overflowOut);
///преобразует символ в int в зависимости от системы счисления
int _charToInt(char _char, TypeNumber type);
///преобразует значение бита в символ
char _intToBinChar(int _int);
///преобразует 4 бита (текущий и три следующих) в 16-ричный символ
char _dataToHexChar(bool* data);

#endif // FUNC_H
