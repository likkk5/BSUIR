#include <iostream>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>


int main() {
    double x1, y1, x2, y2, x3, y3, a, b, c, p, s, ha, hb, hc, ma, mb, mc, la, lb, lc, alfa, betta, gamma, Ralfa, Rbetta, Rgamma, r1, r2, l1, l2, s1, s2;
    std::cin >> x1 >> y1;
    std::cin >> x2 >> y2;
    std::cin >> x3 >> y3;
    std::cout << std::setprecision(5); 
    // длина стороны треугольника
    a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    c = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
    std::cout << a << "\n";
    std::cout << b << "\n";
    std::cout << c << "\n";
    // длина высоты треугольника
    p = (a + b + c) / 2; // полупериметр
    s = 2 * sqrt(p * (p - a) * (p - b) * (p - c)); // удвоенная площадь треугольника
    ha = s/a;
    hb = s/b;
    hc = s/c;
    std::cout << ha << "\n";
    std::cout << hb << "\n";
    std::cout << hc << "\n";
    // длина медианы треугольника
    ma = 0.5 * sqrt(2 * b * b + 2 * c * c - a * a);
    mb = 0.5 * sqrt(2 * a * a + 2 * c * c - b * b);
    mc = 0.5 * sqrt(2 * a * a + 2 * b * b - c * c);
    std::cout << ma << "\n";
    std::cout << mb << "\n";
    std::cout << mc << "\n";
    // длина биссектрисы треугольника
    la = sqrt(b * c * (b + c - a) * 2*p)/(b + c);
    lb = sqrt(a * c * (a + c - b) * 2 * p) / (a + c);
    lc = sqrt(a * b * (a + b - c) * 2 * p) / (a + b);
    std::cout << la << "\n";
    std::cout << lb << "\n";
    std::cout << lc << "\n";
    // радианная и градусная мера угла треугольника
    Ralfa = acos((b * b + c * c - a * a)/(2 * b * c)); // в радианах
    Rbetta = acos((a * a + c * c - b * b)/(2 * a * c));
    Rgamma = acos((a * a + b * b - c * c)/(2 * a * b));
    alfa = Ralfa * 180 / M_PI; // в градусах
    betta = Rbetta * 180 / M_PI;
    gamma = Rgamma * 180 / M_PI;
    std::cout << Rbetta << " " << betta << "\n";
    std::cout << Rgamma << " " << gamma << "\n";
    std::cout << Ralfa << " " << alfa << "\n";
    // радиусы описанной и вписанной окружности
    s = s / 2; // площадь
    r1 = a * b * c / (4 * s);
    r2 = s / p;
    std::cout << r1 << "\n";
    std::cout << r2 << "\n";
    // длина и площадь вписанной и описанной окружности треугольника
    l1 = 2 * M_PI * r1;
    l2 = 2 * M_PI * r2;
    s1 = M_PI * r1 * r1;
    s2 = M_PI * r2 * r2;
    std::cout << l2 << "\n";
    std::cout << s2 << "\n";
    std::cout << l1 << "\n";
    std::cout << s1 << "\n";
    // периметр и площадь треугольника
    p = 2 * p;
    std::cout << s << "\n";
    std::cout << p ;
    return 0;
}