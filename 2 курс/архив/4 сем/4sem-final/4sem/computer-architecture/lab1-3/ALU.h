#ifndef LAB1_3_ALU_H
#define LAB1_3_ALU_H


#include "AluRegister.h"

class ALU {
public:
    static void print(const std::string &s, AluRegister x);

    static Number stringToNumber(std::string str);

    static AluRegister negateSilent(AluRegister x);

    static AluRegister negate(AluRegister x);

    static AluRegister addSilent(AluRegister a, AluRegister b);

    static AluRegister add(AluRegister a, AluRegister b);

    static AluRegister subSilent(AluRegister a, AluRegister b);

    static AluRegister sub(AluRegister a, AluRegister b);

    static std::pair<AluRegister, AluRegister> multiply(AluRegister a, AluRegister b);

    static std::pair<AluRegister, AluRegister> divide(AluRegister a, AluRegister b);
};

#endif //LAB1_3_ALU_H
