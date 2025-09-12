
#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>


int main()
{
    double x, a, b, c, d, s, p, k, y, q, t, v, n, z, m, h;
    // B1
    std::cout << "Variant 1" << "\n";
    std::cout << "Input x=";
    std::cin >> x;
    std::cout << "Input d=";
    std::cin >> d;
    b = x + d;
    if (b != 0)
    {
        a = d * x / b;
        v = pow(d, 3) + (a + d - b);
        if (v != 0)
        {
            s = (pow(a, 2) + b * cos(x)) / v;
            std::cout << "s=" << s << "\n" << "\n";
        }
        else
        {
            std::cout << "Incorrect data" << "\n" << "\n";
        }
    }
    else 
    {
        std::cout << "Incorrect data" << "\n" << "\n";
    }
    // B2
    std::cout << "Variant 2" << "\n";
    std::cout << "Input x=";
    std::cin >> x;
    std::cout << "Input k=";
    std::cin >> k;
    std::cout << "Input p=";
    std::cin >> p;
    std::cout << "Input c=";
    std::cin >> c;
    a = x + sin(p);
    if (a != 0)
    {
        b = exp(k);
        y = 1 + pow(k, 2) / (2 * a * b) - b + d * c;
        std::cout << "y=" << y << "\n" << "\n";

    }
    else
    {
        std::cout << "Incorrect data" << "\n" << "\n";
    }
    // B3
    std::cout << "Variant 3" << "\n";
    std::cout << "Input x=";
    std::cin >> x;
    std::cout << "Input p=";
    std::cin >> p;
    std::cout << "Input n=";
    std::cin >> n;
    std::cout << "Input k=";
    std::cin >> k;
    std::cout << "Input d=";
    std::cin >> d;
    if ((k != 0) && (d != 0))
    {
        b = cos(x);
        c = p - n;
        q = pow(b, 2) / (k*d) + b * pow(c,3);
        std::cout << "q=" << q << "\n" << "\n";
    }
    else
    {
        std::cout << "Incorrect data" << "\n" << "\n";
    }
    // B4
    std::cout << "Variant 4" << "\n";
    std::cout << "Input x=";
    std::cin >> x;
    std::cout << "Input y=";
    std::cin >> y;
    std::cout << "Input z=";
    std::cin >> z;
    std::cout << "Input k=";
    std::cin >> k;
    std::cout << "Input d=";
    std::cin >> d;
    std::cout << "Input c=";
    std::cin >> c;
    v = k - c * d;
    if ((z >=0) && (v != 0))
    {
        a = x - y;
        b = sqrt(z);
        t = cos(x) + pow(a, 2) / v - b;
        std::cout << "t=" << t << "\n" << "\n";
    }
    else
    {
        std::cout << "Incorrect data" << "\n" << "\n";
    }
    // B5
    std::cout << "Variant 5" << "\n";
    std::cout << "Input x=";
    std::cin >> x;
    std::cout << "Input m=";
    std::cin >> m;
    std::cout << "Input n=";
    std::cin >> n;
    std::cout << "Input k=";
    std::cin >> k;
    a = fabs(n + m);
    if ((x != M_PI/2) && (x != -M_PI / 2) && (a != 0))
    {
        d = tan(x);
        y = 1.29 + k / a + pow(d, 2);
        std::cout << "y=" << y << "\n" << "\n";
    }
    else
    {
        std::cout << "Incorrect data" << "\n" << "\n";
    }
    // B6
    std::cout << "Variant 6" << "\n";
    std::cout << "Input x=";
    std::cin >> x;
    std::cout << "Input y=";
    std::cin >> y;
    std::cout << "Input c=";
    std::cin >> c;
    std::cout << "Input k=";
    std::cin >> k;
    if ((c != 0) && (k != 0))
    {
        a = x + y;
        d = fabs(c - a);
        s = 10.1 + a / c + d / pow(k, 2);
        std::cout << "s=" << s << "\n" << "\n";
    }
    else
    {
        std::cout << "Incorrect data" << "\n" << "\n";
    }
    // B7
    std::cout << "Variant 7" << "\n";
    std::cout << "Input x=";
    std::cin >> x;
    std::cout << "Input p=";
    std::cin >> p;
    std::cout << "Input h=";
    std::cin >> h;
    std::cout << "Input k=";
    std::cin >> k;
    std::cout << "Input c=";
    std::cin >> c;
    std::cout << "Input d=";
    std::cin >> d;
    if ((h>0) && (k!=0) && (c!=0) && (d!=0))
    {
        a = x - p;
        b=log(h);
        y = 0.78 * b + pow(a, 3) / (k * c * d);
        std::cout << "y=" << y << "\n" << "\n";
    }
    else
    {
        std::cout << "Incorrect data" << "\n" << "\n";
    }
    // B8
    std::cout << "Variant 8" << "\n";
    std::cout << "Input x=";
    std::cin >> x;
    std::cout << "Input k=";
    std::cin >> k;
    std::cout << "Input c=";
    std::cin >> c;
    std::cout << "Input d=";
    std::cin >> d;
    if ((x > 0) && (k != 0))
    {
        a = log(x);
        b = x + exp(d);
        y = (a + b) - pow(c, 2) / k;
        std::cout << "y=" << y << "\n" << "\n";
    }
    else
    {
        std::cout << "Incorrect data" << "\n" << "\n";
    }
    // B9
    std::cout << "Variant 9" << "\n";
    std::cout << "Input x=";
    std::cin >> x;
    std::cout << "Input p=";
    std::cin >> p;
    std::cout << "Input z=";
    std::cin >> z;
    std::cout << "Input k=";
    std::cin >> k;
    std::cout << "Input c=";
    std::cin >> c;
    std::cout << "Input d=";
    std::cin >> d;
    if ((c!= 0) && (d != 0))
    {
        a = sin(x) - z;
        b = fabs(p - x);
        y = pow(a + b, 2) - k / (c * d);
        std::cout << "y=" << y << "\n" << "\n";
    }
    else
    {
        std::cout << "Incorrect data" << "\n" << "\n";
    }
    // B10
    std::cout << "Variant 10" << "\n";
    std::cout << "Input x=";
    std::cin >> x;
    std::cout << "Input z=";
    std::cin >> z;
    std::cout << "Input k=";
    std::cin >> k;
    std::cout << "Input c=";
    std::cin >> c;
    std::cout << "Input d=";
    std::cin >> d;
    if (x > 0)
    {
        a = log(x) - k;
        if ((a != 0) && (z >= 0))
        {
            b = sqrt(z);
            y = pow(d, 2) + pow(c, 2) / (0.75 * a) + b;
            std::cout << "y=" << y << "\n" << "\n";
        }
        else
        {
            std::cout << "Incorrect data" << "\n" << "\n";
        }
    }
    else
    {
        std::cout << "Incorrect data" << "\n" << "\n";
    }
    
    return 0;
}
