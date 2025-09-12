// Дан файл f, компоненты которого являются целыми числами. Никакая из компонент файла не равна 0. 
// Файле f содержит столько же отрицательных чисел, сколько и положительных.
// Используя вспомогательный файл h, переписать компоненты файла f в файл g, чтобы в файле g не было двух соседних чисел с одним знаком

#include <iostream>
#include <fstream>
/*
int main()
{
	std::ifstream F;
	F.open("f.txt");
	std::fstream H; //и для чтения и для записи
	H.open("h.txt");
	std::ofstream G;
	G.open("g.txt");

	int s, s1;

	if (!F.is_open() || !H.is_open())
	{
		std::cout << "ERROR";
		exit(1);
	}
	while (!F.eof())
	{
		F >> s;
		if (s > 0)
		{
			H << s << " ";
		}
		else
		{
			G << s << " ";
		}
	}
	F.close();

	H.clear();
	H.seekg(0);
	// последовательно - вначале отрицательные, потом положительные
	while (!H.eof())
	{
		H >> s;
		G << s << " ";
	}
	
	H.close();
	G.close();
	return 0;
}*/
//?
#include <iostream>
#include <fstream>

int main()
{
    std::ifstream f("f.txt");
    std::ofstream g("g.txt");
    std::ofstream h("h.txt");

    int prev = 0;
    int curr = 0;

    while (f >> curr)
    {
        if (prev == 0)
        {
            prev = curr;
            if (curr > 0)
            {
                h << curr << " ";
            }
            else
            {
                g << curr << " ";
            }
        }
        else if ((prev > 0 && curr < 0) || (prev < 0 && curr > 0))
        {
            if (curr > 0)
            {
                h << curr << " ";
            }
            else
            {
                g << curr << " ";
            }
            prev = curr;
        }
        else
        {
            if (prev > 0)
            {
                g << curr << " ";
            }
            else
            {
                h << curr << " ";
            }
            prev = curr;
        }
    }

    f.close();
    g.close();
    h.close();

    std::ifstream g_in("g.txt");
    std::ofstream h_out("h.txt");

    prev = 0;
    curr = 0;

    while (g_in >> curr)
    {
        if (prev == 0)
        {
            prev = curr;
            h_out << curr << " ";
        }
        else if ((prev > 0 && curr < 0) || (prev < 0 && curr > 0))
        {
            h_out << curr << " ";
            prev = curr;
        }
        else
        {
            g << curr << " ";
            prev = curr;
        }
    }

    g_in.close();
    h_out.close();

    return 0;
}