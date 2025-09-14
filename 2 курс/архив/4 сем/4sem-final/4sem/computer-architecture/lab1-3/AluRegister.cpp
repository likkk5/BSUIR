#include <iostream>
#include "AluRegister.h"

typedef std::pair<AluRegister, AluRegister> DoubleRegister;


bool AluRegister::operator[](const int i) const {
    return bits[i];
}

bool &AluRegister::operator[](const int i) {
    return bits[i];
}

bool AluRegister::getSignBit() {
    return bits[WORD_SIZE - 1];
}

AluRegister::AluRegister() {
    for (bool &bit: bits) {
        bit = 0;
    }
}

AluRegister &AluRegister::operator=(const AluRegister &aluRegister) {
    for (int i = 0; i < WORD_SIZE; i++) {
        bits[i] = aluRegister[i];
    }
    return *this;
}

AluRegister &AluRegister::operator=(Number number) {
    if ((number < Minimum) || (Maximum < number)) {
        throw std::basic_string<char>("Присваиваемое число не помещается в регистр");
    }

    AluRegister aluRegister;
    bool neg = number < 0;
    number = abs(number);

    for (int i = 0; i < WORD_SIZE; i++) {
        aluRegister[i] = number % 2;
        number /= 2;
    }

    if (neg) {
        aluRegister.inverse().increment();
    }

    *this = aluRegister;
    return *this;
}

AluRegister &AluRegister::inverse() {
    for (bool &bit: bits) {
        bit = !bit;
    }

    return *this;
}

AluRegister &AluRegister::increment() {
    for (bool &bit: bits) {
        if (bit) {
            bit = 0;
        } else {
            bit = 1;
            break;
        }
    }
    return *this;
}

void AluRegister::shiftLeft(int x) {
    for (int i = WORD_SIZE - 1; i - x >= 0; i--) {
        bits[i] = bits[i - x];
    }
    for (int i = x - 1; i >= 0; i--) {
        bits[i] = 0;
    }
}

void AluRegister::shiftRight(int x) {
    for (int i = 0; i + x < WORD_SIZE; i++) {
        bits[i] = bits[i + x];
    }

    for (int i = WORD_SIZE - x; i < WORD_SIZE; i++) {
        bits[i] = 0;
    }
}

AluRegister::operator std::basic_string<char>() {
    std::basic_string<char> str = "";

    for (bool bit: bits) {
        str = (bit ? "1" : "0") + str;
    }

    return str;
}

AluRegister::operator Number() {
    AluRegister aluRegister = *this;
    Number ans = 0;
    int sign = 1;

    if (aluRegister.getSignBit()) {
        sign = -1;
        aluRegister.inverse().increment();
    }

    for (int i = WORD_SIZE - 1; i >= 0; i--) {
        ans = (ans << 1) + aluRegister[i];
    }

    ans *= sign;
    return ans;
}

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &out, AluRegister &aluRegister) {
    out << std::basic_string<char>(aluRegister);
    return out;
}

bool AluRegister::operator==(AluRegister &aluRegister) {
    for (int i = 0; i < WORD_SIZE; i++) {
        if (bits[i] != aluRegister[i]) {
            return false;
        }
    }

    return true;
}

void AluRegister::cyclicShiftRight(int x) {
    bool sign = getSignBit();

    for (int i = 0; i + x < WORD_SIZE; i++) {
        bits[i] = bits[i + x];
    }

    for (int i = WORD_SIZE - x; i < WORD_SIZE; i++) {
        bits[i] = sign;
    }
}

AluRegister::AluRegister(Number x) {
    *this = x;
}
