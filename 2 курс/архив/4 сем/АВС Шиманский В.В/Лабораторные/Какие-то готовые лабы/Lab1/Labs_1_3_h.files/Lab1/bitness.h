#ifndef BITNESS_H
#define BITNESS_H

typedef enum _Bitness
{
	byte,
	word,
	dword,
	qword,
	wrong = 100
} ///размерность числа
Bitness;

///возвращает количество бит по размерности
int countBits(Bitness bitness);
///определяет размерность по количеству бит
Bitness bitnessOfBits(int countBits);

///возвращает количество байт по размерности
int countBytes(Bitness bitness);
///определяет размерность по количеству байт
Bitness bitnessOfBytes(int countBytes);

#endif // BITNESS_H
