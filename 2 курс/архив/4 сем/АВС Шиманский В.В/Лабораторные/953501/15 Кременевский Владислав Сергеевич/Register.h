//
// Created by Vladislav Kremenevskiy on 4/12/21.
//

#ifndef LAB123_REGISTER_H
#define LAB123_REGISTER_H

#include <iostream>
#include <vector>
#include <iomanip>

#define show_add false
#define show_sub false
#define show_mul false
#define show_div true



class Register{

    static const int N = 16;
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

    Register operator*(Register& reg_2);
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


std::ostream& operator<< (std::ostream &out, const std::vector<int>& bitsArr);



#endif //LAB123_REGISTER_H
