#ifndef LAB4_6_ALU_H
#define LAB4_6_ALU_H

#include <iostream>
#include <bitset>
#include <algorithm>
#include <limits>

using namespace std;

class ALU {
private:
    static float Float(const string& f);
    static string String(float f);

    static void print(float f);
    static void print(string f);
    static void print(const string& s, float f);
    static void print(const string& s, string f);

    static bool getSignBit(string f);
    static int getSign(string f);
    static void setSign(string &f, bool s);
    static void setSign(string &f, int s);
    static int getExponent(string f);
    static void setExponent(string &f, int e);
    static int getMantissa(const string& f);
    static void setMantissa(string &f, int e);
    static bool isZero(string f);
    static string negate(string f);

public:
    static void addition(string a, string b);
    static void addition(float a, float b);
    static void subtraction(string a, string b);
    static void subtraction(float a, float b);
    static void multiplication(string a, string b);
    static void multiplication(float a, float b);
    static void division(string a, string b);
    static void division(float a, float b);
};


#endif //LAB4_6_ALU_H
