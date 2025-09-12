#include <iostream>

int main()
{
    long long X, Y;
    long double A, B, C, K;
    std::cin >> X >> Y;
    std::cin >> A >> B >> C >> K;

    if (X < Y)
    {
        X = 0;
    }
    else
    {
        if (X > Y)
        {
            Y = 0;
        }
        else
        {
            X = 0;
            Y = 0;
        }
    }
    std::cout << X << " " << Y << "\n";

    if ((A > B) && (A > C))
    {
        A = A - K;
    }
    else
    {
        if ((B > A) && (B > C))
        {
            B = B - K;
        }
        else
        {
            if ((C > A) && (C > B))
            {
                C = C - K;
            }
        }
    }
    std::cout << A << " " << B << " " << C;
    return 0;
}
