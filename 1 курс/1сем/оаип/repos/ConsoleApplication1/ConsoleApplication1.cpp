#include <iostream>
char GetBinKInd(int k, std::string str) {
    int cur = 0;
    int carry = 0;
    for (int j = 0; j < k + 1; j++) {
        carry = 0;
        cur = 0;
        for (int i = 0; i < str.length(); i++) {
            cur = (str[i] - 48) + carry * 10;
            str[i] = cur / 2 + 48;
            carry = cur % 2;
        }
    }
    return carry + 48;
}
int main()
{
    int n;
    std::cin >> n;
    std::string* a = new std::string[20000];
    std::string* b = new std::string[10000];
    a[0] = "0";
    std::string t = "0";
    int k = 0, qa = 0, qb = 0, q = 1, count = 0, c = 0, end = 0;
    bool flag1 = false;
    while (true) {
        for (int j = 0; j < q; j++) {
            if (k == 0) {
                b[j] = "1";
                std::cout << b[j] << " ";
                count++;
            }
            if (k > 0) {
                if (a[j].length() == k) {
                    b[j] = a[j];
                    b[j].insert(0, "1");
                    std::cout << b[j] << " ";
                }
                if (a[j].length() != k) {
                    b[j] = a[j];
                    b[j].insert(0, "1");
                    t.resize(k - a[j].length());
                    for (int z = 0; z < k - a[j].length(); z++) {
                        t[z] = '0';
                    }
                    b[j].resize(k);
                    b[j].insert(1, t);
                    std::cout << b[j] << " ";
                }

                count++;
            }
            if (count == n) {
                flag1 = true;
                std::cout << b[j];
                break;
            }
        }
        if (flag1 == true) { break; }
        k++;
        for (int i = 0; i < q; i++) {
            if (GetBinKInd(k, a[i]) == '0') {
                qa++;
                a[c] = a[i];
                c++;
                end = c;
            }
        }

        for (int i = 0; i < q; i++) {
            if (GetBinKInd(k, b[i]) == '0') {
                qb++;
                a[end] = b[i];
                end++;
            }
        }
        q = qa + qb;
        std::cout << "quantity" << q << "\n";
        for (int i = 0; i < q; i++) {
            std::cout << a[i] << " ";
        }
        std::cout << "\n";
        qa = 0;
        qb = 0;
        c = 0;

    }
}