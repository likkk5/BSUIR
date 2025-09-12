#include <iostream>

int main()
{
	long double W, H, x1, x2, y1, y2, w, h, a, b = 0;
	std::cin >> W >> H;
	std::cin >> x1 >> y1 >> x2 >> y2;
	std::cin >> w >> h;

	if (x1 > x2) // если введены координаты наоборот, то меняем местами 
	{
		a = x2;
		x2 = x1;
		x1 = a;
	}
	if (y1 > y2) // если введены координаты наоборот, то меняем местами 
	{
		a = y2;
		y2 = y1;
		y1 = a;
	}


	if ((W > 0) && (H > 0) && (w > 0) && (h > 0) && (W >= w) && (H >= h) && (x1 >= 0) && (y1 >= 0) && (x2 > 0) && (y2 > 0) && (x1 < W) && (x2 <= W) && (y1 < H) && (y2 <= H) && (x1 != x2) && (y1 != y2))
	{
		if (h != H)
		{
			if ((x1 >= w) || (y1 >= h))
			{
				b = 0;
			}
			else
			{
				if ((y2 + h - y1) <= H)
				{
					b = h - y1;
				}
				else
				{
					b = -1;
				}
			}
		}
		else
		{
			if ((x2 + w - x1) <= W)
			{
				b = w - x1;
			}
			else
			{
				b = -1;
			}
		}
	}
	else
	{
		std::cout << "Incorrect data" << "\n";
	}
	std::cout << b;
	return 0;

}