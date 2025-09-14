//
// Created by Vladislav Kremenevskiy on 4/18/21.
//

#ifndef LAB456_FLOAT_H
#define LAB456_FLOAT_H
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>





#define show_add true
#define show_sub true
#define show_mul true
#define show_div false


class Float {
    float float_num;
    const static int m_size = 23;
    const static int e_size = 8;
    int zero_exp = 127;
    const static int N = m_size + e_size + 1;
    std::vector<int> number;
    std::vector<int> mantissa;
    std::vector<int> exp;

    int expInt;
    int sign;

    static std::vector<int> truncMantissa(std::vector<int> m);
    std::vector<int> addBinaryMul(const std::vector<int>& v1,std::vector<int>& v2);
    static std::vector<int> addBinary(const std::vector<int>& v1, const std::vector<int>& v2);
    static std::vector<int> subBinary(const std::vector<int>& v1, const std::vector<int>& v2);

    static std::pair<std::vector<int>, int> addBinary_s(const std::vector<int>& v1, const std::vector<int>& v2);

    static std::vector<int> rMove(const std::vector<int>& v);
    static std::vector<int> lMove(const std::vector<int>& v);

    static std::vector<int> buildBinary(int num, int size);
    static std::vector<int> entireToBin(int entire);
    static std::vector<int> buildExp(int exponent, int exp_size);
    static std::vector<int> fractionToBin(float fraction, int size=16);
    static int maxInt(int exp_size);

    static int binEntireToInt(const std::vector<int>& v);
    static int entireFromMantissa(const std::vector<int>& mantissa, int exp);
    static float fractionFromMantissa(const std::vector<int>& mantissa, int exp);
    static std::vector<int> trimV(const std::vector<int>& v_1, const std::vector<int>& v_2, int size);

    static std::vector<int> binFromMantissa(std::vector<int>& m);
    static std::vector<int> mantissaFromBin(std::vector<int>& bin);
    static std::vector<int> mantissaFromRandBin(std::vector<int>& bin);


    friend std::ostream& operator<<(std::ostream& out, const std::vector<int>& v);
    friend std::ostream& operator<<(std::ostream& out, const Float& floating);


//    Float operator>>(int num) const;

    static std::vector<int> make2c(std::vector<int>& bin);





public:
    Float();
    explicit Float(float num);
    Float(const Float& num);
    Float operator+(Float& floating_2);
    Float operator-(Float& floating_2);
    Float operator*(Float& floating_2);
    Float operator/(Float& floating_2);
    Float& operator=(const Float& floating_2);

    explicit operator float() const;

};



class Register{

    static const int N = 48;
    int number;
    std::vector<int> binary;

    struct Flags{
        int OF = 0;
    } flags;


    void printBits() const;

    static std::vector<int> makeBinary(int num);
    static void reverseArrBits(std::vector<int> &arr);
    static void twos_complement(std::vector<int>& bin);
    static int toInt(const Register& reg);


public:

    Register();
    explicit Register(int num);
    explicit Register(const std::vector<int> &bitsArr);
    Register(const Register& reg);

    void setBinary(const std::vector<int> & binArr);
    void setNumber(const int num);
    void setRegister(const Register& reg);

    static Register reverseBits(const Register &reg);
    void reverseBits();
    static int getBigNum(const Register& reg_1, const Register& reg_2);

    Register& operator=(const Register& reg);

private:
    int& operator[](const int index);
    const int& operator[](const int index) const;

public:
    void setIndexedVal(int index, int value);
    Register& operator++();
    Register operator++(int);

    Register operator+(const Register &reg_2);
    Register operator+(int& num);
    friend Register operator+(int& num, Register& reg_2);

    Register operator-(const Register& reg_2);
    Register operator-(int& num);
    friend Register operator-(int& num, Register& reg_2);

    std::vector<int> operator*(Register& reg_2);
    Register operator/(Register& reg_2);

    friend bool operator==(const Register& reg_1, const Register& reg_2);
    friend bool operator==(const Register& reg_1, const int& num);

    Register operator<<(const Register& reg2) const;
    Register operator<<(int num) const;
    Register operator>>(const Register& reg_2) const;
    Register operator>>(int num) const;

    friend std::ostream& operator<< (std::ostream &out, const Register& reg);
    friend std::istream& operator>> (std::istream &in, Register& reg);

    explicit operator int() const;
};




#endif //LAB456_FLOAT_H
