#include <iostream>
#include <bitset>
#include <algorithm>
#include <limits>

using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::swap;
using std::bitset;
using std::count;
using std::numeric_limits;

class ALU
{
public:
    static float Float(string f) {
        unsigned int x = bitset<32>(f).to_ulong();
        return *((float*)&x);
    }
    static string String(float f) {
        return bitset<32>(*((int*)&f)).to_string();
    }
    static void Print(float f) {
        cout << String(f).insert(9, " ").insert(1, " ") << " = " << f << endl;
    }
    static void Print(string f) {
        cout << f.insert(9, " ").insert(1, " ") << " = " << Float(f) << endl;
    }
    static void Print(string s, float f) {
        cout << s << " = ";
        Print(f);
    }
    static void Print(string s, string f) {
        cout << s << " = ";
        Print(f);
    }
    static bool SignBit(string f) {
        return (f[0] == '1');
    }
    static int Sign(string f) {
        return (SignBit(f) ? -1 : 1);
    }
    static void SetSign(string& f, bool s) {
        f[0] = (s ? '1' : '0');
    }
    static void SetSign(string& f, int s) {
        SetSign(f, ((s < 0) ? true : false));
    }
    static int Exp(string f) {
        return (bitset<32>(f.substr(1, 8)).to_ulong() - 127);
    }
    static void SetExp(string& f, int e) {
        if ((e <= -127) || (128 <= e)) {
            throw string("Порядок превышен");
        }
        f.replace(1, 8, bitset<8>(e + 127).to_string());
    }
    static int Mant(string f) {
        return bitset<32>("1" + f.substr(9, 23)).to_ulong();
    }
    static void SetMant(string& f, int e) {
        if ((e < 0) || ((1 << 24) <= e)) {
            throw string("Мантисса превышена");
        }
        if ((e & (1 << 23)) == 0) {
            throw string("Мантисса не начинается с 1");
        }
        f.replace(9, 23, bitset<23>(e ^ (1 << 23)).to_string());
    }
    static bool IsZero(string f) {
        return count(f.begin() + 1, f.end(), '0') == 31;
    }

    static string Negate(string f) {
        cout << "---Отрицание---" << endl;
        string ans = f;
        Print(" x", ans);
        ans[0] = '0' + '1' - ans[0];
        Print("-x", ans);
        return ans;
    }
    static void Addition(string a, string b) {
        cout << "---Суммирование---" << endl;
        Print("a", a);
        Print("b", b);
        cout << "a + b =" << endl;
        if (IsZero(a)) {
            cout << "a = 0.0 -> a + b = b" << endl;
            Print(" ", b);
            return;
        }
        if (IsZero(b)) {
            cout << "b = 0.0 -> a + b = a" << endl;
            Print(" ", a);
            return;
        }
        if (Exp(a) > Exp(b)) {
            swap(a, b);
            Print("a", a);
            Print("b", b);
            cout << "a + b =" << endl;
        }
        bool SignBitA = SignBit(a), SignBitB = SignBit(b);
        int SignA = Sign(a), SignB = Sign(b);
        int ExpA = Exp(a), ExpB = Exp(b);
        int MantA = Mant(a), MantB = Mant(b);
        cout << "Порядки чисел " << ((ExpA < ExpB) ? "не " : "") << "равны." << endl;
        while (ExpA < ExpB) {
            ExpA++;
            MantA >>= 1;
        }
        if (ExpB < ExpA) {
            throw string("Что-то пошло не так");
        }
        cout << "a = " << (SignBitA ? "-" : "+") << " " << bitset<8>(ExpA + 127).to_string() << " 0." << bitset<24>(MantA).to_string() << endl;
        cout << "b = " << (SignBitB ? "-" : "+") << " " << bitset<8>(ExpB + 127).to_string() << " 0." << bitset<24>(MantB).to_string() << endl;
        if (MantA == 0) {
            cout << "a ~ 0.0 -> a + b = b" << endl;
            Print(" ", b);
            return;
        }
        int sm = MantA * SignA + MantB * SignB;
        int se = ExpA;
        int ss = 1;
        cout << "Мантисса a = " << SignA * MantA << endl;
        cout << "Мантисса b = " << SignB * MantB << endl;
        cout << "Мантисса a+b = " << sm << endl;
        if (sm == 0) {
            Print(" ", 0);
            return;
        }
        if (sm < 0) {
            ss = -1;
            sm = -sm;
        }
        cout << "Знак a+b = " << (ss < 0 ? "-1" : "+1") << endl;
        cout << "Порядок a+b = " << se << endl;
        cout << "Мантисса a+b = " << bitset<32>(sm).to_string().insert(9," ").insert(8, " ") << endl;
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
        cout << "Мантисса a+b = " << bitset<32>(sm).to_string().insert(9," ").insert(8, " ") << endl;
        string ans(32, '_');
        SetSign(ans, ss);
        SetExp(ans, se);
        SetMant(ans, sm);
        Print(" ", ans);
        return;
    }
    static void Addition(float a, float b) {
        Addition(String(a), String(b));
    }
    static void Subtraction(string a, string b) {
        cout << "---Вычитание---" << endl;
        Print("a", a);
        Print("b", b);
        cout << "a - b = a + -b" << endl;
        Addition(a, Negate(b));
    }
    static void Subtraction(float a, float b) {
        Subtraction(String(a), String(b));
    }
    static void Multiplication(string a, string b) {
        cout << "---Умножение---" << endl;
        Print("a", a);
        Print("b", b);
        cout << "a * b =" << endl;
        if (IsZero(a)) {
            cout << "a = 0.0 -> a * b = 0" << endl;
            Print(" ", 0);
            return;
        }
        if (IsZero(b)) {
            cout << "b = 0.0 -> a * b = 0" << endl;
            Print(" ", 0);
            return;
        }
        int SignA = Sign(a), SignB = Sign(b);
        int ExpA = Exp(a), ExpB = Exp(b);
        int MantA = Mant(a), MantB = Mant(b);
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
        cout << "Мантисса a*b = " << bitset<32>(mm).to_string().insert(9," ").insert(8, " ") << endl;
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
        cout << "Мантисса a*b = " << bitset<32>(mm).to_string().insert(9," ").insert(8, " ") << endl;
        string ans(32, '0');
        SetSign(ans, ms);
        SetExp(ans, me);
        SetMant(ans, mm);
        Print(" ", ans);
        return;
    }
    static void Multiplication(float a, float b) {
        Multiplication(String(a), String(b));
    }
    static void Division(string a, string b) {
        cout << "---Деление---" << endl;
        Print("a", a);
        Print("b", b);
        cout << "a / b =" << endl;
        if (IsZero(b)) {
            cout << "b = 0.0 ->" << endl;
            throw string("Деление на ноль");
        }
        if (IsZero(a)) {
            cout << "a = 0.0, b != 0.0 -> a / b = 0" << endl;
            Print(" ", 0);
            return;
        }
        bool SignBitA = SignBit(a), SignBitB = SignBit(b);
        int SignA = Sign(a), SignB = Sign(b);
        int ExpA = Exp(a), ExpB = Exp(b);
        int MantA = Mant(a), MantB = Mant(b);
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
        cout << "Мантисса a/b = " << bitset<32>(dm).to_string().insert(9," ").insert(8, " ") << endl;
        cout << "Нормализация ответа:";
        while (dm >= (1 << 24)) {
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
        cout << "Мантисса a/b = " << bitset<32>(dm).to_string().insert(9," ").insert(8, " ") << endl;
        string ans(32, '0');
        SetSign(ans, ds);
        SetExp(ans, de);
        SetMant(ans, dm);
        Print(" ", ans);
        return;
    }
    static void Division(float a, float b) {
        Division(String(a), String(b));
    }
};

#define Test(f) \
    try { f; cout << endl; } catch (string ex) { cout << "Ошибка: " << ex << endl << endl; }

int main()
{
    setlocale(LC_ALL, "Russian");
    /*
     //Тестирование сложения
    {
        Test(ALU::Addition(0, 0));
        Test(ALU::Addition(-13.42, 0));
        Test(ALU::Addition(1.0, -2.0));
        Test(ALU::Addition(1.0, -1.0));
        Test(ALU::Addition(1.25, 1.5));
        Test(ALU::Addition(1.0, numeric_limits<float>::min()));

        Test(ALU::Addition(numeric_limits<float>::max(), numeric_limits<float>::max()));
        Test(ALU::Addition(2 * numeric_limits<float>::min(), -1.5 * numeric_limits<float>::min()));

        cout << endl << endl << endl;
    }

     //Тестирование вычитания
    {
        Test(ALU::Subtraction(1.0, 1.0));
        Test(ALU::Subtraction(-13.42, 0));

        cout << endl << endl << endl;
    }

     //Тестирование умножения
    {
        Test(ALU::Multiplication(0, 0));
        Test(ALU::Multiplication(13, 0));
        Test(ALU::Multiplication(42, -0.01));
        Test(ALU::Multiplication(numeric_limits<float>::max(), numeric_limits<float>::min()));

        Test(ALU::Multiplication(numeric_limits<float>::max(), numeric_limits<float>::max()));
        Test(ALU::Multiplication(numeric_limits<float>::max(), 1.001));
        Test(ALU::Multiplication(numeric_limits<float>::min(), numeric_limits<float>::min()));
        Test(ALU::Multiplication(numeric_limits<float>::min(), 0.999));

        cout << endl << endl << endl;
    }

    //Тестирование деления
    {
        Test(ALU::Division(1, -3));
        Test(ALU::Division(42, 0));
        Test(ALU::Division(0, 13));

        Test(ALU::Division(numeric_limits<float>::max(), numeric_limits<float>::min()));
        Test(ALU::Division(numeric_limits<float>::max(), 0.999));
        Test(ALU::Division(numeric_limits<float>::min(), numeric_limits<float>::max()));
        Test(ALU::Division(numeric_limits<float>::min(), 1.001));

        cout << endl << endl << endl;
    }
    */
    float a, b;
    cin >> a >> b;
    cout << endl;
    Test(ALU::Addition(a, b));
    Test(ALU::Subtraction(a, b));
    Test(ALU::Multiplication(a, b));
    Test(ALU::Division(a, b));
    return 0;
}
