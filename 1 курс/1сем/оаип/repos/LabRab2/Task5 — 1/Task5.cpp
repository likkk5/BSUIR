#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    long double k, x, y, d = 0;
    std::cin >> k >> x >> y;

    if (k < 0)
    {
        k = -k;
        x = -x;
        y = -y;
    }

    if ((x >= 0) && (x <= k))
    {
        if (y > k)
        {
            d = y - k;
        }
        else
        {

            if ((y >= 0) && (y <= k))
            {
                /*if (x >= k / 2) // находим min(y,k-x,k-y)
                {
                    if (y >= k / 2) // находим min(k-x,k-y)
                    {
                        if (x >= y)
                        {
                            d = k - x;
                        }
                        else
                        {
                            d = k - y;
                        }
                    }
                    else // находим min(k-x,y)
                    {
                        if (k - x >= y)
                        {
                            d = y;
                        }
                        else
                        {
                            d = k - x;
                        }
                    }
                }
                else // находим min(x,y,k-y)
                {
                    if (y >= k / 2) // находим min(x,k-y)
                    {
                        if (x >= k - y)
                        {
                            d = k - y;
                        }
                        else
                        {
                            d = x;
                        }
                    }
                    else // находим min(y,x)
                    {
                        if (x >= y)
                        {
                            d = y;
                        }
                        else
                        {
                            d = x;
                        }
                    }
                }*/

                d = fmin(x, y);
                d = fmin(d, k - y);
                d = fmin(d, k - x);
            }
            else // y<0
            {
                d = -y;
            }
        }

    }
    else
    {
        if (x > k)
        {
            if (y < 0)
            {
                d = sqrt((x - k) * (x - k) + y * y);
            }
            if ((y >= 0) && (y <= k))
            {
                d = x - k;
            }
            if (y > k)
            {
                d = sqrt((x - k) * (x - k) + (y - k) * (y - k));
            }
        }
        else // x<0
        {
            if (y < 0)
            {
                d = sqrt(x * x + y * y);
            }
            if ((y >= 0) && (y <= k))
            {
                d = -x;
            }
            if (y > k)
            {
                d = sqrt(x * x + (y - k) * (y - k));
            }
        }
    }

    std::cout << std::setprecision(22) << d ;
    return 0;
}