#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void solve(long double a, long double b, long double h, long double eps)
{
    cout << setprecision(3) << scientific << showpos <<
        "                                    eps = " << eps << "        " << endl;
    cout << " ---------------------------------------------------------- " << endl;
    cout << " |     x      |    S(x)    |    Y(x)    | abs(S - Y) | n  | " << endl;
    cout << " |------------|------------|------------|------------|----| " << endl;
    for (long double x = a; x < b + h / 2; x += h)
    {
        int k = 0;
        long double S = 0;
        long double Y = pow(M_E, x*cos(M_PI/4)) * cos(x*sin(M_PI/4));
        long double val = 1;
        while (abs(S - Y) > eps) {
            S += val * cos(k * M_PI / 4);
            k++;
            val *= x / k;
        }
        cout << setprecision(3) << scientific << showpos <<
            " | " << x << " | " << S << " | " << Y << " | " << abs(S - Y) << " | " <<
            noshowpos << right << setw(2) << k << " | " << endl;
    }
    cout << " ---------------------------------------------------------- " << endl;
}

int main()
{
    long double a, b, h, eps;
    cout << endl << "Enter a, b, h, eps:" << endl;
    cin >> a >> b >> h >> eps;
    solve(a, b, h, eps);
    return 0;
}