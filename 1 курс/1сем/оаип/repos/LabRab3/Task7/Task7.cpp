#include <iostream>
#include <iomanip>


int main()
{
	const long double pi = 3.14159265358979323;
	const int k = 30; // количество знаков после запятой для печати
	long long i, j, fact, degree = 0;
	long double a, b, c, x, d, t, t1, min, ln_10;

	setlocale(LC_ALL, "rus");
	std::cout << std::setprecision(k);
	std::cout << "Введите x= ";
	std::cin >> x;

	// sin(x)
	int sign = (x < 0) ? -1 : 1; //сохраняем знак х;
	// sin(t-2pi) = sin(t)

	t = fabsl(x);

	
	t1 = 2*pi*pow(10,10);
	
	// исключаем периодичность
	if (t > t1)
	{ 
		t = t/ pow(10, 10) - long long (t / t1) * 2*pi;
		t = t * pow(10, 10);
	}
	
	if (t > 2 * pi)
	{
		t = t - long long(t / (2 * pi)) * (2 * pi);
	}
	
	t1 = t; // сохраняем для косинуса, чтобы еще раз не убирать периоды

	if (t > pi)
	{
		t = t - pi;
		sign = sign * (-1);
	}

	if (t > pi / 2)
	{
		t = pi - t;
	}

	i = 0;
	a = 0;
	d = t;
	fact = 1;
	do
	{
		a = a + d;
		i++;
		fact = fact * 2 * i * (2 * i + 1);
		d = d * (-1) * t * t / fact;
	} while (fabsl(d) > 1.0e-43);
	a = a * sign;
	std::cout << "a = " << a << "\n";


	// cos(x)
	sign = 1; // cos(-x) = cos(x)

	// cos(t-2pi) = cos(t)

	t = t1;
	
	if (t > (3 * pi / 2))
	{
		t = 2 * pi - t;
	}

	if (t > pi / 2)
	{
		t = t - pi;
		sign = sign * (-1);
	}

	i = 0;
	b = 0;
	d = 1;
	fact = 1;
	do
	{
		b = b + d;
		i++;
		fact = fact * (2 * i - 1) * 2 * i;
		d = d * (-1) * t * t / fact;
	} while (fabsl(d) > 1.0e-43);
	b = b * sign;
	std::cout << "b = " << b << "\n";


	if (a > b)
	{
		min = b;
	}
	else
	{
		min = a;
	}


	// ln(|x|) = ln (|t|*10^q) = ln (|t|) + q * ln (10), 1 <= |t| <10  
	if (x != 0)
	{
		// преобразование |x| (0..10) 
		t = fabsl(x);
		degree = 0;

		if (fabsl(x) > 10)
		{
			degree = 0;
			while (t > 10)
			{
				t = t / 10;
				degree = degree + 1;
			}
		}
		if (fabsl(x) < 1)
		{
			degree = 0;
			while (t < 1)
			{
				t = t * 10;
				degree = degree - 1;
			}
		}

		//логарифм для вещественных чисел от 0 до 10 (по модулю)
		i = 0;
		t = (fabs(t) - 1) / (fabs(t) + 1);
		c = 0;
		d = 0;
		do
		{
			c = c + d;
			i++;
			d = 2 * pow(t, 2 * i - 1) / (2 * i - 1);
		} while (d > 1.0e-43);

		//логарифм 
		if (degree != 0)
		{
			i = 0;
			t = (fabs(10) - 1) / (fabs(10) + 1);
			ln_10 = 0;
			d = 0;
			do
			{
				ln_10 = ln_10 + d;
				i++;
				d = 2 * pow(t, 2 * i - 1) / (2 * i - 1);
			} while (d > 1.0e-43);

			c = c + ln_10 * degree;
		}

		if (min > c)
		{
			min = c;
		}
		std::cout << "c = " << c << "\n";
		std::cout << "min= " << min << "\n";
	}
	else
	{
		std::cout << "ln(0) - не определен" << "\n";
		std::cout << "min = " << min << "\n";
	}
	return 0;
}
