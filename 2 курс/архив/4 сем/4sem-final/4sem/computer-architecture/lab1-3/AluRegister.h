#ifndef LAB1_3_ALUREGISTER_H
#define LAB1_3_ALUREGISTER_H

#include <valarray>

typedef long long Number;
const int WORD_SIZE = 16;

class AluRegister {


    bool bits[WORD_SIZE];

public:
    static const Number Minimum = -(1 << (WORD_SIZE - 1));
    static const Number Maximum = (1 << (WORD_SIZE - 1)) - 1;

    bool operator[](int i) const;

    bool &operator[](int i);

    bool getSignBit();

    AluRegister();

    AluRegister(Number x);

    AluRegister &operator=(const AluRegister &aluRegister);

    AluRegister &operator=(Number number);

    AluRegister &inverse();

    AluRegister &increment();

    void shiftLeft(int x);

    void shiftRight(int x);

    void cyclicShiftRight(int x);

    operator std::basic_string<char>();

    operator Number();

    friend std::basic_ostream<char> &operator<<(std::basic_ostream<char> &out, AluRegister &aluRegister);

    bool operator==(AluRegister &aluRegister);
};

#endif //LAB1_3_ALUREGISTER_H
