#include <iostream>
#include <iomanip>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
	long double a, b, c, p, q, x1, x2, x3, x4, y1, y2, d, d1, d2;
	int i;
	//std::cout << std::fixed << std::setprecision(1);

	setlocale(LC_ALL, "russian");
	std::cout << "7.1: ax^4+bx^2+c=0" << "\n";
	std::cout << "7.2: ax^4+bx^3+cx^2+bx+a=0" << "\n";
	std::cout << "7.3: x^3+px+q=0" << "\n";
	std::cout << "Выберите уравнение:";
	std::cin >> i;

	switch (i)
	{
	case 1:
		std::cout << "Введите a=";
		std::cin >> a;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}

		std::cout << "Введите b=";
		std::cin >> b;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}

		std::cout << "Введите c=";
		std::cin >> c;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}

		std::cout << "Корни уравнения: " << "\n";
		if (a != 0)
		{
			d = pow(b, 2) - 4 * c * a;
			if (d > 0)
			{
				y1 = (-b + sqrt(d)) / (2 * a);
				y2 = (-b - sqrt(d)) / (2 * a);
				if ((y1 > 0) && (y2 > 0))
				{
					x1 = sqrt(y1);
					x2 = -sqrt(y1);
					x3 = sqrt(y2);
					x4 = -sqrt(y2);
					std::cout << "x=" << x1 << "\n";
					std::cout << "x=" << x2 << "\n";
					std::cout << "x=" << x3 << "\n";
					std::cout << "x=" << x4 << "\n";
				}
				else
				{
					if ((y1 > 0) && (y2 < 0))
					{
						x1 = sqrt(y1);
						x2 = -sqrt(y1);
						std::cout << "x=" << x1 << "\n";
						std::cout << "x=" << x2 << "\n";
					}
					else
					{
						if ((y1 < 0) && (y2 > 0))
						{
							x3 = sqrt(y2);
							x4 = -sqrt(y2);
							std::cout << "x=" << x3 << "\n";
							std::cout << "x=" << x4 << "\n";
						}
						else
						{
							std::cout << "действительных корней нет" << "\n";
						}
					}
				}
		    }
			else
			{
				if (d == 0)
				{
					y1 = -b / (2 * a);
					if (y1 > 0)
					{
						x1 = sqrt(y1);
						x2 = -sqrt(y1);
						std::cout << "x=" << x1 << "\n";
						std::cout << "x=" << x2 << "\n";
					}
					else
					{
						if (y1 == 0)
						{
							x1 = 0;
							std::cout << "x=" << x1 << "\n";
						}
						else
						{
							std::cout << "действительных корней нет" << "\n";

						}
					}
				}
				else 
				{
					std::cout << "действительных корней нет" << "\n";
				}
			}
		}
		else 
		{
			if (b != 0)
			{
				if (-c / b > 0)
				{
					x1 = sqrt(-c/b);
					x2 = -sqrt(-c/b);
					std::cout << "x = " << x1 << "\n";
					std::cout << "x = " << x2 << "\n";
				}
				else 
				{
					if (c==0)
					{
						x1 = 0;
						std::cout << "x = " << x1 << "\n";
					}
					else
					{
						std::cout << "действительных корней нет" << "\n";
					}
				}
			}
			else
			{
				if (c == 0)
				{
					std::cout << "x - любое (бесконечное количество корней)" << "\n";
				}
				else 
				{
					std::cout << "нет решения" << "\n";

				}
			}
		}
		break;
	
	case 2:
		std::cout << "Введите a=";
		std::cin >> a;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}

		std::cout << "Введите b=";
		std::cin >> b;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}

		std::cout << "Введите c=";
		std::cin >> c;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}

		std::cout << "Корни уравнения: " << "\n";
		if (a != 0)
		{
			d = pow(b, 2) - 4 *(c  - 2 * a) * a;
			if (d > 0)
			{
				y1 = (-b + sqrt(d)) / (2 * a);
				y2 = (-b - sqrt(d)) / (2 * a);
				d1 = pow(y1, 2) - 4;
				d2 = pow(y2, 2) - 4;
				if ((d1 > 0) && (d2 >0))
				{
					x1 = (y1 + sqrt(d1)) / 2;
					x2 = (y1 - sqrt(d1)) / 2;
					x3 = (y2 + sqrt(d2)) / 2;
					x4 = (y2 - sqrt(d2)) / 2;
					std::cout << "x=" << x1 << "\n";
					std::cout << "x=" << x2 << "\n";
					std::cout << "x=" << x3 << "\n";
					std::cout << "x=" << x4 << "\n";
				}
				if ((d1 > 0) && (d2 == 0))
				{
					x1 = (y1 + sqrt(d1)) / 2;
					x2 = (y1 - sqrt(d1)) / 2;
					x3 = 0.5 * y2;
					std::cout << "x=" << x1 << "\n";
					std::cout << "x=" << x2 << "\n";
					std::cout << "x=" << x3 << "\n";
				}
				if ((d1 > 0) && (d2 < 0))
				{
					x1 = (y1 + sqrt(d1)) / 2;
					x2 = (y1 - sqrt(d1)) / 2;
					std::cout << "x=" << x1 << "\n";
					std::cout << "x=" << x2 << "\n";
				}

				if ((d1 == 0) && (d2 > 0))
				{
					x1 = 0.5*y1;
					x3 = (y2 + sqrt(d2)) / 2;
					x4 = (y2 - sqrt(d2)) / 2;
					std::cout << "x=" << x1 << "\n";
					std::cout << "x=" << x3 << "\n";
					std::cout << "x=" << x4 << "\n";
				}
				if ((d1 == 0) && (d2 == 0))
				{
					x1 = 0.5 * y1;
					x3 = 0.5 * y2;
					std::cout << "x=" << x1 << "\n";
					std::cout << "x=" << x3 << "\n";
				}
				if ((d1 == 0) && (d2 < 0))
				{
					x1 = 0.5 * y1;
					std::cout << "x=" << x1 << "\n";
				}
				
				if ((d1 <0) && (d2 > 0))
				{
					x3 = (y2 + sqrt(d2)) / 2;
					x4 = (y2 - sqrt(d2)) / 2;
					std::cout << "x=" << x3 << "\n";
					std::cout << "x=" << x4 << "\n";
				}
				if ((d1 < 0) && (d2 == 0))
				{
					x3 = 0.5 * y2;
					std::cout << "x=" << x3 << "\n";
				}
				
				if ((d1 < 0) && (d2 < 0))
				{
					std::cout << "действительных корней нет" << "\n";
				}
			}
			else
			{
				if (d == 0)
				{
					y1 = -b / (2 * a);
					d1 = pow(y1, 2) - 4;
					if (d1 > 0)
					{
						x1 = (y1 + sqrt(d1)) / 2;
						x2 = (y1 - sqrt(d1)) / 2;
						std::cout << "x=" << x1 << "\n";
						std::cout << "x=" << x2 << "\n";
						}
					if (d1 == 0)
					{
						x1 = 0.5 * y1;
						std::cout << "x=" << x1 << "\n";
					}
					if (d1 < 0)
					{
						std::cout << "действительных корней нет" << "\n";
					}
				 }
				else
				{
					std::cout << "действительных корней нет" << "\n";
				}
			}
		}
		else
		{
		    if (b != 0)
			{
				x1 = 0;
				std::cout << "x = " << x1 << "\n";

				d = pow(c, 2) - 4 * pow(b, 2);
			    if (d > 0)
				{
					x2 = (-c + sqrt(d)) / (2 * b);
					x3 = (-c - sqrt(d)) / (2 * b);
					std::cout << "x = " << x2 << "\n";
					std::cout << "x = " << x3 << "\n";
				}
				else
				{
					if (d == 0)
					{
						x2 = -c / (2 * b);
						std::cout << "x = " << x2 << "\n";
					}
				}
			}
			else
			{
				if (c != 0)
				{
					x1 = 0;
					std::cout << "x = " << x1 << "\n";
				}
				else
				{
					std::cout << "x - любое (бесконечное количество корней)" << "\n";
				}
			}
		}
		break;
	
	case 3:
		//std::cout << std::fixed << std::setprecision(1);

		std::cout << "Введите p=";
		std::cin >> p;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}

		std::cout << "Введите q=";
		std::cin >> q;
		if (std::cin.fail() || std::cin.peek() != '\n')
		{
			std::cout << "некорректный ввод";
			return 0;
		}

		std::cout << "Корни уравнения: " << "\n";

		a = -p / 3;
		b = q / 2;
		if ((b * b) < (a * a * a))
		{
			x4 = acos(b / sqrt(a * a * a)) / 3;
			
			x1 = -2 * sqrt(a) * cos(x4);
			x2 = -2 * sqrt(a) * cos(x4 + (2 * M_PI / 3));
			x3 = -2 * sqrt(a) * cos(x4 - (2 * M_PI / 3));
			std::cout << "x = " << x1 << "\n";
			std::cout << "x = " << x2 << "\n";
			std::cout << "x = " << x3 << "\n";
		}
		else
		{
			x1 = cbrt(-q / 2 + sqrt((q * q) / 4 + (p * p * p) / 27)) + cbrt(-q / 2 - sqrt((q * q) / 4 + (p * p * p) / 27));
			std::cout << "x=" << x1 << "\n";
		}
		break;
	
	default:
	   	std::cout << "Уравнение не выбрано" << "\n";
		break;
       
    }
	return 0;
}