#include <iostream>
#include <cmath>

int main()
{
	//13
	double y[10000];
	double a=-1.0, b=1.0, h, x, min;
	int n,i=0,j=0;
	setlocale(LC_ALL, "rus");
	std::cout << "Введите количество частей, на которые надо разделить область поиска корня -  ";
	std::cin >> n;
	if (std::cin.fail() || std::cin.peek() != '\n')
	{
		std::cout << "Incorrect input";
		return 0;
	}
	
	h = (b - a) / n;
	if ((n > 0) && (n<10000))
	{
		for (x = a; x <= b; x = x + h)
		{
			y[i] = sin(x) + tan(x) - 1 / (1 + x * x);
			std::cout << "y[" << i << "]= " << y[i] << "   x = " << x << "\n";
			i++;
		}
		
		min = fabs(y[0]);
		
		for (i = 1; i < n; i++)
		{
			if (min > fabs(y[i]))
			{
				min = fabs(y[i]);
				j = i;
			}
		}
		
		std::cout << "\n" << "Минимальное по модулю значение функции: ";
		std::cout << "y = " << y[j] << "\n";
		x = a + j * h;
		std::cout << "Корень: x = "<< x << "\n";
	}
	else
	{
		std::cout << "Incorrect input";
	}

	return 0;
}