#include "ALU.h"

float ALU::Float(const string& f) {
    unsigned int x = bitset<32>(f).to_ulong();
    return *((float *) &x);
}

string ALU::String(float f) {
    int repl = *((int *) &f);
    return bitset<32>(repl).to_string();
}

void ALU::print(float f) {
    cout << String(f).insert(9, " ").insert(1, " ") << " = " << f << endl;
}

void ALU::print(string f) {
    string a = f;
    cout << f.insert(9, " ").insert(1, " ") << " = " << Float(a) << endl;
}

void ALU::print(const string& s, float f) {
    cout << s << " = ";
    print(f);
}

void ALU::print(const string& s, string f) {
    cout << s << " = ";
    print(f);
}

bool ALU::getSignBit(string f) {
    return (f[0] == '1');
}

int ALU::getSign(string f) {
    return (getSignBit(f) ? -1 : 1);
}

void ALU::setSign(string &f, bool s) {
    f[0] = (s ? '1' : '0');
}

void ALU::setSign(string &f, int s) {
    setSign(f, (s < 0));
}

int ALU::getExponent(string f) {
    return (bitset<32>(f.substr(1, 8)).to_ulong() - 127);
}

void ALU::setExponent(string &f, int e) {
    if ((e <= -127) || (128 <= e)) {
        throw string("Порядок превышен");
    }
    f.replace(1, 8, bitset<8>(e + 127).to_string());
}

int ALU::getMantissa(const string& f) {
    return bitset<32>("1" + f.substr(9, 23)).to_ulong();
}

void ALU::setMantissa(string &f, int e) {
    if ((e < 0) || ((1 << 24) <= e)) {
        throw string("Мантисса превышена");
    }
    if ((e & (1 << 23)) == 0) {
        throw string("Мантисса не начинается с 1");
    }
    f.replace(9, 23, bitset<23>(e ^ (1 << 23)).to_string());
}

bool ALU::isZero(string f) {
    return count(f.begin() + 1, f.end(), '0') == 31;
}

string ALU::negate(string f) {
    cout << "---Отрицание---" << endl;
    string ans = f;
    print(" x", ans);
    ans[0] = '0' + '1' - ans[0];
    print("-x", ans);
    return ans;
}

void ALU::addition(string a, string b) {
    cout << "---Суммирование---" << endl;
    print("a", a);
    print("b", b);
    cout << "a + b =" << endl;
    if (isZero(a)) {
        cout << "a = 0.0 -> a + b = b" << endl;
        print(" ", b);
        return;
    }
    if (isZero(b)) {
        cout << "b = 0.0 -> a + b = a" << endl;
        print(" ", a);
        return;
    }
    if (getExponent(a) > getExponent(b)) {
        swap(a, b);
        print("a", a);
        print("b", b);
        cout << "a + b =" << endl;
    }
    bool SignBitA = getSignBit(a), SignBitB = getSignBit(b);
    int SignA = getSign(a), SignB = getSign(b);
    int ExpA = getExponent(a), ExpB = getExponent(b);
    int MantA = getMantissa(a), MantB = getMantissa(b);
    cout << "Порядки чисел " << ((ExpA < ExpB) ? "не " : "") << "равны." << endl;
    while (ExpA < ExpB) {
        ExpA++;
        MantA >>= 1;
    }
    if (ExpB < ExpA) {
        throw string("Что-то пошло не так");
    }
    cout << "a = " << (SignBitA ? "-" : "+") << " " << bitset<8>(ExpA + 127).to_string() << " 0."
         << bitset<24>(MantA).to_string() << endl;
    cout << "b = " << (SignBitB ? "-" : "+") << " " << bitset<8>(ExpB + 127).to_string() << " 0."
         << bitset<24>(MantB).to_string() << endl;
    if (MantA == 0) {
        cout << "a ~ 0.0 -> a + b = b" << endl;
        print(" ", b);
        return;
    }
    int sm = MantA * SignA + MantB * SignB;
    int se = ExpA;
    int ss = 1;
    cout << "Мантисса a = " << SignA * MantA << endl;
    cout << "Мантисса b = " << SignB * MantB << endl;
    cout << "Мантисса a+b = " << sm << endl;
    if (sm == 0) {
        print(" ", 0);
        return;
    }
    if (sm < 0) {
        ss = -1;
        sm = -sm;
    }
    cout << "Знак a+b = " << (ss < 0 ? "-1" : "+1") << endl;
    cout << "Порядок a+b = " << se << endl;
    cout << "Мантисса a+b = " << bitset<32>(sm).to_string().insert(9, " ").insert(8, " ") << endl;
    cout << "Нормализация ответа:";
    while (sm >= (1 << 24)) {
        cout << " ->";
        sm >>= 1;
        se++;
        if (se >= 128) {
            cout << endl;
            throw string("Переполнение порядка");
        }
    }
    while ((sm & (1 << 23)) == 0) {
        cout << " <-";
        sm <<= 1;
        se--;
        if (se <= -127) {
            cout << endl;
            throw string("Потеря значимости порядка");
        }
    }
    cout << endl;
    cout << "Знак a+b = " << (ss < 0 ? "-1" : "+1") << endl;
    cout << "Порядок a+b = " << se << endl;
    cout << "Мантисса a+b = " << bitset<32>(sm).to_string().insert(9, " ").insert(8, " ") << endl;
    string ans(32, '_');
    setSign(ans, ss);
    setExponent(ans, se);
    setMantissa(ans, sm);
    print(" ", ans);
    return;
}

void ALU::addition(float a, float b) {
    addition(String(a), String(b));
}

void ALU::subtraction(string a, string b) {
    cout << "---Вычитание---" << endl;
    print("a", a);
    print("b", b);
    cout << "a - b = a + -b" << endl;
    addition(a, negate(b));
}

void ALU::subtraction(float a, float b) {
    subtraction(String(a), String(b));
}

void ALU::multiplication(string a, string b) {
    cout << "---Умножение---" << endl;
    print("a", a);
    print("b", b);
    cout << "a * b =" << endl;
    if (isZero(a)) {
        cout << "a = 0.0 -> a * b = 0" << endl;
        print(" ", 0);
        return;
    }
    if (isZero(b)) {
        cout << "b = 0.0 -> a * b = 0" << endl;
        print(" ", 0);
        return;
    }
    int SignA = getSign(a), SignB = getSign(b);
    int ExpA = getExponent(a), ExpB = getExponent(b);
    int MantA = getMantissa(a), MantB = getMantissa(b);
    cout << "Порядок a = " << a.substr(1, 8) << endl;
    cout << "Порядок b = " << b.substr(1, 8) << endl;
    int ms = SignA * SignB;
    int me = ExpA + ExpB;
    long long mm = ((long long) MantA * MantB) >> 23;
    cout << "Порядок a*b = " << bitset<16>(me + 127).to_string().insert(8, " ") << endl;
    if (me >= 128) {
        throw string("Переполнение порядка");
    }
    if (me <= -127) {
        throw string("Потеря значимости порядка");
    }
    cout << "Мантисса a = " << MantA << endl;
    cout << "Мантисса b = " << MantB << endl;
    cout << "Мантисса a*b = " << mm << endl;
    if (mm == 0) {
        throw string("Что-то пошло не так");
    }
    cout << "Знак a*b = " << (ms < 0 ? "-1" : "+1") << endl;
    cout << "Порядок a*b = " << me << endl;
    cout << "Мантисса a*b = " << bitset<32>(mm).to_string().insert(9, " ").insert(8, " ") << endl;
    cout << "Нормализация ответа:";
    while (mm >= (1 << 24)) {
        cout << " ->";
        mm >>= 1;
        me++;
        if (me >= 128) {
            cout << endl;
            throw string("Переполнение порядка");
        }
    }
    if ((mm & (1 << 23)) == 0) {
        throw string("Что-то пошло не так");
    }
    cout << endl;
    cout << "Знак a*b = " << (ms < 0 ? "-1" : "+1") << endl;
    cout << "Порядок a*b = " << me << endl;
    cout << "Мантисса a*b = " << bitset<32>(mm).to_string().insert(9, " ").insert(8, " ") << endl;
    string ans(32, '0');
    setSign(ans, ms);
    setExponent(ans, me);
    setMantissa(ans, mm);
    print(" ", ans);
    return;
}

void ALU::multiplication(float a, float b) {
    multiplication(String(a), String(b));
}

void ALU::division(string a, string b) {
    cout << "---Деление---" << endl;
    print("a", a);
    print("b", b);
    cout << "a / b =" << endl;
    if (isZero(b)) {
        cout << "b = 0.0 ->" << endl;
        throw string("Деление на ноль");
    }
    if (isZero(a)) {
        cout << "a = 0.0, b != 0.0 -> a / b = 0" << endl;
        print(" ", 0);
        return;
    }
    int SignA = getSign(a), SignB = getSign(b);
    int ExpA = getExponent(a), ExpB = getExponent(b);
    int MantA = getMantissa(a), MantB = getMantissa(b);
    cout << "Порядок a = " << a.substr(1, 8) << endl;
    cout << "Порядок b = " << b.substr(1, 8) << endl;
    int ds = SignA * SignB;
    int de = ExpA - ExpB;
    long long dm = ((long long) MantA << 23) / MantB;
    cout << "Порядок a/b = " << bitset<16>(de + 127).to_string().insert(8, " ") << endl;
    if (de >= 128) {
        throw string("Переполнение порядка");
    }
    if (de <= -127) {
        throw string("Потеря значимости порядка");
    }
    cout << "Мантисса a = " << MantA << endl;
    cout << "Мантисса b = " << MantB << endl;
    cout << "Мантисса a/b = " << dm << endl;
    if (dm == 0) {
        throw string("Что-то пошло не так");
    }
    cout << "Знак a/b = " << (ds < 0 ? "-1" : "+1") << endl;
    cout << "Порядок a/b = " << de << endl;
    cout << "Мантисса a/b = " << bitset<32>(dm).to_string().insert(9, " ").insert(8, " ") << endl;
    cout << "Нормализация ответа:";
    if (dm >= (1 << 24)) {
        throw string("Что-то пошло именно так");
    }
    if ((dm & (1 << 23)) == 0) {
        cout << " <-";
        dm <<= 1;
        de--;
        if (de <= -127) {
            cout << endl;
            throw string("Потеря значимости порядка");
        }
    }
    cout << endl;
    cout << "Знак a/b = " << (ds < 0 ? "-1" : "+1") << endl;
    cout << "Порядок a/b = " << de << endl;
    cout << "Мантисса a/b = " << bitset<32>(dm).to_string().insert(9, " ").insert(8, " ") << endl;
    string ans(32, '0');
    setSign(ans, ds);
    setExponent(ans, de);
    setMantissa(ans, dm);
    print(" ", ans);
}

void ALU::division(float a, float b) {
    division(String(a), String(b));
}
