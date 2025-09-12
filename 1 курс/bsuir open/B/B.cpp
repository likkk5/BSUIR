#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double n, m, k;
    cin >> n >> m >> k;
    double left = 0;
    double right = min(n, m);
    double epsilon = 0.000001;
    double ans = 0;

    while (right - left > epsilon) {
        double mid = (left + right) / 2;
        double squares = floor(n / mid) * floor(m / mid);

        if (squares >= k) {
            ans = mid;
            left = mid;
        }
        else {
            right = mid;
        }
    }

    cout << ans;

    return 0;
}

