#include <iostream>

int main()
{
    long long i, j, l, x, y, N, x_min, y_min, j_min, num;
    std::cin >> N;

    x_min = N;
    y_min = N;
    j_min = -1;

    long long c[31];
    c[0] = 1;
    c[1] = 1;

    for (i = 2; i < 31; i++)
    {
        c[i] = c[i - 1] + c[i - 2];
    }

    
    for (j = 0; j < 30;j++)
    {
        for (i = 0;i <= 2000;i++)
        {
            for (l = 0; l <= 2000;l++)
            {
                num = c[j] * i + c[j + 1] * l;
                if (num == N)
                {
                    if ((x_min + y_min) > (i + l))
                    {
                        x_min = i;
                        y_min = l;
                        j_min = j;
                     }
                }
                else if (num > N)
                {
                    break;
                }
            }
        }
    }

    std::cout << x_min << " " << y_min;
    return 0;
}