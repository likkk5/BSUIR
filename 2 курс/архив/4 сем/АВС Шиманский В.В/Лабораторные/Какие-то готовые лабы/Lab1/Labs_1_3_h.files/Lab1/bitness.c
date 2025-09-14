#include "bitness.h"

int countBits(Bitness bitness)
{
	if (bitness == wrong)
		return 0;
	return 8 << bitness;
}

Bitness bitnessOfBits(int countBits)
{
	if (countBits < 0)
		return wrong;
	int bitness = 0;
	countBits--;
	countBits = countBits >> 3;
	while (countBits > 0)
	{
		countBits = countBits >> 1;
		bitness++;
	}
	if (bitness > qword)
		return wrong;
	return (Bitness)(bitness);
}

int countBytes(Bitness bitness)
{
	if (bitness == wrong)
		return 0;
	return (int)bitness+1;
}

Bitness bitnessOfBytes(int countBytes)
{
	if (countBytes < 0 ||  countBytes > 4)
		return wrong;
	return (Bitness)(countBytes-1);
}
