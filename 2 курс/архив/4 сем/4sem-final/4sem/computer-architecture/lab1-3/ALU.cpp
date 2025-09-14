#include "ALU.h"
#include "AluRegister.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::pair;
using std::setw;
using std::string;

AluRegister ALU::sub(AluRegister a, AluRegister b) {
    cout << "---Вычитание---" << endl;
    print("a", a);
    print("b", b);
    cout << "a - b = a + -b" << endl;

    return add(a, negate(b));
}

AluRegister ALU::subSilent(AluRegister a, AluRegister b) {
    return addSilent(a, negateSilent(b));
}

pair<AluRegister, AluRegister> ALU::divide(AluRegister a, AluRegister b) {
    cout << "---Деление---" << endl;

    print("a", a);
    print("b", b);

    if ((b == 0) | ((a == AluRegister::Minimum) & (b == -1))) {
        throw string("Переполнение при делении");
    }

    AluRegister aluRegister = b, A = -a.getSignBit(), Q = a;
    bool sign = a.getSignBit() ^ b.getSignBit();
    cout << "| A" << setw(WORD_SIZE + 1) << " | Q" << endl;

    for (int i = 0; i < WORD_SIZE; i++) {
        cout << " " << A << " " << Q << endl;
        A.shiftLeft(1);
        A[0] = Q.getSignBit();
        Q.shiftLeft(1);
        AluRegister oldA = A;

        if (A.getSignBit() ^ aluRegister.getSignBit()) {
            A = addSilent(A, aluRegister);
        } else {
            A = subSilent(A, aluRegister);
        }
        if ((!A.getSignBit() ^ oldA.getSignBit()) | ((A == 0) & (Q == 0))) {
            Q[0] = 1;
        } else {
            Q[0] = 0;
            A = oldA;
        }
    }

    if (sign) {
        Q = negateSilent(Q);
    }

    cout << " " << A << " " << Q << endl;
    cout << "-----" << endl;
    print("Q", Q);
    print("A", A);
    cout << endl;
    return {Q, A};
}

pair<AluRegister, AluRegister> ALU::multiply(AluRegister a, AluRegister b) {
    cout << "---Умножение---" << endl;
    print("a", a);
    print("b", b);
    cout << "a * b = " << endl;
    AluRegister ans;
    bool Q = 0;
    cout << "| A" << setw(WORD_SIZE + 1) << " | Q" << setw(WORD_SIZE + 3) << " | Q-1" << endl;
    for (int i = 0; i < WORD_SIZE; i++) {
        cout << " " << ans << " " << b << " " << Q << endl;
        if (Q ^ b[0]) {
            ans = addSilent(ans, (Q ? a : negateSilent(a)));
        }
        Q = b[0];
        b.shiftRight(1);
        b[WORD_SIZE - 1] = ans[0];
        ans.cyclicShiftRight(1);
    }
    cout << " " << ans << " " << b << " " << Q << endl;
    cout << "-----" << endl;
    cout << "= " << ans << b << "(2)" << endl;
    cout << "= " << stringToNumber(string(ans) + string(b)) << "(10)" << endl;
    cout << endl;
    return pair<AluRegister, AluRegister>(ans, b);
}

AluRegister ALU::add(AluRegister a, AluRegister b) {
    cout << "---Суммирование---" << endl;
    print("a", a);
    print("b", b);
    cout << a << endl;
    cout << "+" << endl;
    cout << b << endl;
    cout << "=" << endl;

    AluRegister ans;
    bool memory = false;

    cout << "A - бит первого числа, B - бит второго числа, m - флаг переноса" << endl;
    cout << " A + B + m -> S (m) " << endl;
    cout << "-------------------------" << endl;

    for (int i = 0; i < WORD_SIZE; i++) {
        cout << " " << a[i] << " + " << b[i] << " + " << memory;
        ans[i] = a[i] ^ b[i] ^ memory;
        memory = (a[i] & b[i]) | (memory & (a[i] | b[i]));
        cout << " -> " << ans[i] << " (" << memory << ")" << endl;
    }
    cout << ans << " (Перенос = " << memory << ")" << endl;
    if ((!(a.getSignBit() ^ b.getSignBit())) & (ans.getSignBit() ^ a.getSignBit())) {
        throw string("Переполнение при суммировании");
    }
    cout << "= " << int(ans) << "(10)" << endl;
    cout << endl;
    return ans;
}

void ALU::print(const string &s, AluRegister x) {
    cout << s << " = " << x << "(2) = " << int(x) << "(10)" << endl;
}

long long int ALU::stringToNumber(string str) {
    long long int ans = 0;
    int sign = 1;

    if (str[0] == '1') {
        sign = -1;

        for (char &c: str) {
            c = '0' + ('1' - c);
        }

        for (int i = str.size() - 1; i >= 0; i--) {
            str[i] = '0' + ('1' - str[i]);
            if (str[i] == '1') {
                break;
            }
        }
    }

    for (char c: str) {
        ans = (ans << 1) + (c - '0');
    }

    return sign * ans;
}

AluRegister ALU::addSilent(AluRegister a, AluRegister b) {
    AluRegister ans;
    bool memory = 0;

    for (int i = 0; i < WORD_SIZE; i++) {
        ans[i] = a[i] ^ b[i] ^ memory;
        memory = (a[i] & b[i]) | (memory & (a[i] | b[i]));
    }

    if ((!(a.getSignBit() ^ b.getSignBit())) & (ans.getSignBit() ^ a.getSignBit())) {
        throw string("Переполнение при суммировании");
    }

    return ans;
}

AluRegister ALU::negate(AluRegister x) {
    cout << "---Отрицание---" << endl;

    AluRegister ans = x;
    print(" x", ans);

    if (ans == AluRegister::Minimum) {
        throw string("Невозможно отрицать число");
    }

    ans.inverse();
    print("~x", ans);

    ans.increment();
    print("-x", ans);

    return ans;
}

AluRegister ALU::negateSilent(AluRegister x) {
    if (x == AluRegister::Minimum) {
        throw string("Невозможно отрицать число");
    }

    return x.inverse().increment();
}
