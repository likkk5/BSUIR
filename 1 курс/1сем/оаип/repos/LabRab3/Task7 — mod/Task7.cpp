#include <iostream>
#include <iomanip>
#include <string>

//модуль
long double my_mod(long double a)
{
	return a < 0 ? -a : a;
}


int main()
{
	const double pi = 3.14159265358979323846;
	const int k = 30; // количество знаков после запятой для печати
	long long i, fact, degree = 0;
	long double a, b, c, x, d, t, min, ln_10;
	std::string s1 = "";
	std::string s2 = "";
	std::string s3 = "";

	setlocale(LC_ALL, "rus");
	std::cout << std::fixed << std::setprecision(k);
	std::cout << "Введите x= ";
	std::cin >> x;

	// sin(x)
	int sign = (x < 0) ? -1 : 1; //сохраняем знак х;
	t = my_mod(x);

	// sin(t-2pi) = sin(t)
	while (t > (2*pi))
	{
		t = t / (2*pi);
	}
	
	if (t > pi)
	{
		t = t - pi;
		sign = sign * (-1);
	}

	if (t > pi/2)
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
		d = d *(-1) * t * t / fact;
	}
	while (my_mod(d) > 1.0e-43);
	a = a * sign;
	std::cout << "a = " << a << "\n";

	
	// cos(x)
	sign = 1; // cos(-x) = cos(x)
	t = my_mod(x);
	
	if ((my_mod(x) < 0.1) && (x != 0))
	{
		degree = 0;
		while (t < 0.1)
		{
			t = t * 10;
			degree = degree + 1;
		}
	}

	// cos(t-2pi) = cos(t)
	if (my_mod(x) > (2 * pi))
	{
		while (t > (2 * pi))
		{
			t = t / (2 * pi);
		}
	}

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
	} while (my_mod(d) > 1.0e-43);
	b = b * sign;
	
	if ((my_mod(x) < 0.1) && (x != 0))
	{
		s1 = "0.";
		t = b;
		for (i = 1;i <= degree;i++)
		{
			s1 = s1 + "99";
		}
		for (i = 1;i <= k;i++)
		{
			t = t * 10;
			s3 = std::to_string(int(t));
			s2 = s2 + s3;
			t = t - int(t);
		}
		s1 = s1 + s2;
	}

	if ((my_mod(x) < 0.1) && (x != 0))
	{

		std::cout << "b = " << s1.erase(k+2,2*degree) << "\n";
		min = a;
	}
	else
	{
		std::cout << "b = " << b << "\n";
		if (a > b)
		{
			min = b;
		}
		else
		{
			min = a;
		}
	}

	// ln(|x|) = ln (|t|*10^q) = ln (|t|) + q * ln (10), 1 <= |t| <10  
	if (x != 0)
	{
		// приводим |x| к нормальной форме числа с плавающей точкой 
		t = my_mod(x);
		
		if (my_mod(x) > 10)
		{
			degree = 0;
			while (t > 10)
			{
				t = t / 10;
				degree = degree + 1;
			}
		}
		if (my_mod(x) < 1)
		{
			degree = 0;
			while (t < 1)
		    {
				t = t * 10;
				degree = degree - 1;
			}
		}
	
		//логарифм для вещественных чисел от 1 до 10 (по модулю)
		i = 0;
		t = (my_mod(t) - 1) / (my_mod(t) + 1);
		c = 0;
		d = 0;
		do
		{
			c = c + d;
			i++;
			d = 2 * pow(t, 2 * i - 1) / (2 * i - 1);
		}
		while (d > 1.0e-43);
		
		//логарифм 10
		if (degree != 0)
		{
			i = 0;
			t = (my_mod(10) - 1) / (my_mod(10) + 1);
			ln_10 = 0;
			d = 0;
			do
			{
				ln_10 = ln_10 + d;
				i++;
				d = 2 * pow(t, 2 * i - 1) / (2 * i - 1);
			}
			while (d > 1.0e-43);

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
