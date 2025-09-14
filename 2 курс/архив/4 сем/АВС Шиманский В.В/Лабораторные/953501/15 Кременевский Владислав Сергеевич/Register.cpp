//
// Created by Vladislav Kremenevskiy on 4/12/21.
//

#include "Register.h"



void Register::setBinary(const std::vector<int> &binArr) {
    binary = binArr;
    number = (int)(*this);
}


void Register::setNumber(const int num){
    number = num;
    binary = makeBinary(abs(num));
    if (num < 0) {
        twos_complement(binary);
    }
}


void Register::setRegister(const Register& reg) {
    number = reg.number;
    binary = reg.binary;
}



void Register::reverseBits(){
    reverseArrBits(binary);
    ++(*this);
}


Register Register::reverseBits(const Register& reg){
    Register reversed(reg.binary);
    reversed.reverseBits();
    return reversed;
}


void Register::twos_complement(std::vector<int>& bin){
    reverseArrBits(bin);
    int i = N-1;
    while(i >= 0){
        if (bin[i] == 1) {
            bin[i] = 0;
        }
        else {
            bin[i] = 1;
            break;
        }
        --i;
    }
}


void Register::printBits() const{
    for(int i = 0; i < N; ++i) {
        std::cout << binary[i];
    }
}


std::vector<int> Register::makeBinary(int num) {

    std::vector<int> binArr(N, 0);
    int i = 0;
    while(num > 0) {
        binArr[N-1-i] = num % 2;
        num /= 2;
        ++i;
    }
    return binArr;
}


void Register::reverseArrBits(std::vector<int> &arr) {
    for(int i = 0; i < N; ++i) {
        arr[i] == 1 ? arr[i] = 0 : arr[i] = 1;
    }
}


int Register::toInt(const Register& reg){
    int intNum = 0;
    intNum -= reg.binary[0] * pow(2, N - 1);
    for(int i = N - 1; i > 0; --i){
        if (reg.binary[i] == 0){
            continue;
        }
        intNum += pow(2, N-i-1);
    }
    return intNum;
}


Register::Register() {
    binary = std::vector<int>(N, 0);
    number = 0;
}


Register::Register(int num) : Register() {
    setNumber(num);
}


Register::Register(const std::vector<int> &bitsArr) : Register() {
    setBinary(bitsArr);
}


Register::Register(const Register& reg){
    setNumber(reg.number);
}


Register& Register::operator=(const Register& reg){
    setRegister(reg);
    return *this;
}


int& Register::operator[](const int index){

    return this->binary[index];
}


const int& Register::operator[](const int index) const {
    return this->binary[index];
}


void Register::setIndexedVal(int index, int value){
    (*this)[index] = value;
    this->setBinary(this->binary);
}


Register& Register::operator++(){
    int i = N-1;
    while(i >= 0){
        if (binary[i] == 0){
            binary[i] = 1;
            break;
        }
        binary[i] = 0;
        --i;
    }
    return *this;
}


Register Register::operator++(int){
    Register temp(binary);
    ++(*this);
    return temp;
}


Register Register::operator+(const Register &reg_2){
    int r{};
    int r_prev{};
    Register result;
    if (show_add){
        std::cout << "---Сложение---\n";
        std::cout << "Первое число: " << int(*this) << " (" << this->binary << ")"<< '\n';
        std::cout << "Второе число: " << int(reg_2) << " (" << reg_2.binary << ")"<< '\n';


        std::cout << std::setw(5);
        std::cout << "|num_1|" << " |num_2|" << " |CF|" << " |res|\n";
    }
    for(int i = N-1; i >= 0; --i) {
        r_prev = r;
        if ((this->binary[i] + reg_2[i] + r) == 1) {
            r = 0;
            result[i] = 1;
        }
        else if ((this->binary[i] + reg_2[i] + r) == 2) {
            r = 1;
            result[i] = 0;
        }
        else if(this->binary[i] + reg_2[i] + r == 3) {
            r = 1;
            result[i] = 1;
        }
        else{
            r = 0;
            result[i] = this->binary[i] + reg_2[i];
        }
        if (show_add){
            std::cout << std::setw(4) << binary[i];
            std::cout << std::setw(8) << reg_2[i];
            std::cout << std::setw(6) << r_prev;
            std::cout << std::setw(6) << result[i] << '\n';
        }

    }
    if ((this->binary[0] == reg_2[0]) && (this->binary[0] != result[0])){
        result.flags.OF = 1;
        std::cout << "Переполнение\n";
    }

    if(show_add){
        std::cout << (int)*this << " + " << (int)reg_2 << " = " << (int)result << '\n';
        std::cout << "Результат: " << (int)result << " (" << result.binary << ")\n";
    }
    result.setBinary(result.binary);
    return result;
}


Register Register::operator+(int& num){
    Register reg_2(num);
    Register result = *this + reg_2;
    return result;
}


Register operator+(int& num, Register& reg_2){
    Register result = reg_2 + num;
    return result;
}


Register Register::operator-(const Register& reg_2){
    if (show_sub){
        std::cout << "---Вычитание---\n";
        std::cout << (int)*this << " - " << (int)reg_2 << '\n';
        std::cout << "Первое число: " << int(*this) << " (" << this->binary << ")"<< '\n';
        std::cout << "Второе число: " << int(reg_2) << " (" << reg_2.binary << ")"<< '\n';
    }

    Register reg_2_temp(reg_2);
    if (reg_2 == -32678){
        std::cout << "Невозможно выполнить отрицание для " << int(reg_2) << '\n';
        return Register(0);
    }

    reg_2_temp.reverseBits();
    if (show_sub){
        std::cout << "Инвертирование 2 числа:\n";
        std::cout << "~ " << reg_2.binary << " = " << reg_2_temp.binary << " (" << (int)reg_2_temp << ")\n";
    }
    Register result = *this + reg_2_temp;
    return result;
}


Register Register::operator-(int& num){
    Register reg_2(num);
    Register result = *this - reg_2;
    return result;
}


Register operator-(int& num, Register& reg_2){
    Register reg_1(num);
    Register result = reg_1 - reg_2;
    return result;
}


int Register::getBigNum(const Register& reg_1, const Register& reg_2){
    int num = 0;
    int j = 0;
    for(int i = 0; i < N; ++i){
        num += reg_2[N-i-1] * (int)pow(2, j);
        ++j;
    }
    for(int i = 0; i < N; ++i){
        num += reg_1[N-i-1] * (int)pow(2, j);
        ++j;
    }
    return num;
}


Register Register::operator*(Register& reg_2){
    if (show_mul){
        std::cout << "---Умножение---\n";
        std::cout << this->number << " * " << reg_2.number << " (Результат компьютера: " << (int)(*this) * (int)reg_2 << ") "<<'\n';
        std::cout << "Первое число: " << int(*this) << " (" << this->binary << ") - reg_1\n";
        std::cout << "Второе число: " << int(reg_2) << " (" << reg_2.binary << ") - reg_2\n\n";
    }

    Register A;
    int Q1 = 0;
    int A1 = 0;

    if (show_mul) {
        std::cout << std::setw(10) << " A " << std::setw(9) << "|";
        std::cout << std::setw(14) << " reg_2 " << std::setw(6) <<  "|" << " Q1  |\n";

        std::cout << A.binary << " |";
        std::cout << std::setw(2) << reg_2.binary << " | ";
        std::cout << std::setw(2) << Q1 << "  |\n";
    }

    for(int i = N-1; i >= 0; --i) {

        if (Q1 == 0 && reg_2[N-1] == 1){
            A = A - *this;
        }
        else if (Q1 == 1 && reg_2[N-1] == 0){
            A = A + *this;
        }

        if (show_mul && Q1 != reg_2[N-1]) {
            std::cout << A.binary << " |";
            std::cout << std::setw(2) << reg_2.binary << " | ";
            std::cout << std::setw(2) << Q1 << "  |  ";
            std::cout << reg_2.binary[N-1] << "-" << Q1 << " ->";
            if (Q1 == 0)
                std::cout << " A = A-reg_1\n";
            else
                std::cout << " A = A+reg_1\n";

        }
//        shifting
        A1 = A.binary[N-1];
        A = A >> 1;
        Q1 = reg_2.binary[N-1];
        reg_2 = reg_2 >> 1;
        reg_2.setIndexedVal(0, A1);
//        reg_2[0] = A1;

        if (show_mul) {
            std::cout << A.binary << " |";
            std::cout << std::setw(2) << reg_2.binary << " | ";
            std::cout << std::setw(2) << Q1 << "  | >> shift\n";
        }
    }

    if (show_mul){
        std::cout << '\n' << std::setw(20) <<  "Регистр A";
        std::cout << std::setw(7) << " | ";
        std::cout << std::setw(24) << "Регситр reg_2\n";
        std::cout << A.binary << " | " << reg_2.binary << '\n';
        std::cout << "Результат умножения: " << getBigNum(A, reg_2);
    }
    return A;
}


Register Register::operator/(Register& reg_2) {

    if (reg_2 == 0){
        std::cout << "Ошибка при делении! Не предусмотрено деление на 0!";
        return Register(0);
    }

    if (*this == -32768 && reg_2 == -1) {
        std::cout << "Переполнение при делении!";
        return Register(0);
    }


    Register A;
    if (this->binary[0] == 1){
        A.setNumber(-1);
    }
    Register M(reg_2);
    Register reg_1(*this);

    if (show_div) {
        std::cout << "---Деление---\n";
        std::cout << this->number << " / " << reg_2.number
                  << " (Результат компьютера: " << (int) (*this) / (int) reg_2
                  << " | Остакток: " << (int) (*this) % (int) reg_2 << ") " << '\n';
        std::cout << "Первое число: " << int(*this) << " (" << this->binary << ") - reg_1\n";
        std::cout << "Второе число: " << int(reg_2) << " (" << reg_2.binary << ") - reg_2\n\n";

        std::cout << std::setw(10) << " A " << std::setw(9) << "|";
        std::cout << std::setw(14) << " reg_1"<< std::setw(7) << "|\n";
        std::cout << A.binary << " |";
        std::cout << std::setw(2) << reg_1.binary << " |\n";
    }


    int Qn{};
    for (int i = N - 1; i >= 0; --i) {
        Qn = reg_1[0];
        A = A << 1;
        reg_1 = reg_1 << 1;
        A[N - 1] = Qn;

        if (show_div) {
            std::cout << A.binary << " |";
            std::cout << std::setw(2) << reg_1.binary << " | ";
            std::cout << "<< shift | STEP " << N-i <<"\n";
        }

        int A_sign = A[0];

        if (M[0] == A[0]) {
            A = A - M;
            if (show_div) {
                std::cout << A.binary << " |";
                std::cout << std::setw(2) << reg_1.binary << " | ";
                std::cout << "Sub: A = A - reg_2\n";
            }
        } else {
            A = A + M;
            if (show_div) {
                std::cout << A.binary << " |";
                std::cout << std::setw(2) << reg_1.binary << " | ";
                std::cout << "Add: A = A + reg_2\n";
            }
        }

        if (A_sign == A[0] || (A == 0 && reg_1 == 0)) {
            reg_1.setIndexedVal(N - 1, 1);
            if (show_div) {
                std::cout << A.binary << " |";
                std::cout << std::setw(2) << reg_1.binary << " | ";
                std::cout << "reg_1[N] = 1\n";
            }
        } else {
            if (M[0] == A_sign) {
                A = A + M;
            }
            else{
                A = A - M;
            }
            reg_1.setIndexedVal(N - 1, 0);
            if (show_div) {
                std::cout << A.binary << " |";
                std::cout << std::setw(2) << reg_1.binary << " | ";
                std::cout << "Restore A\n";
            }
        }

        if (show_div){
            for(int i = 0; i < 60; i++)
                std::cout << '.';
            std::cout << '\n';
        }
    }

    if ((*this)[0] != M[0]) {
        Register saved_reg_1(reg_1);
        reg_1.reverseBits();

        if (show_div) {
            std::cout << "\nТак как знак Делимого(" << (int)*this << ") не равен знаку Делителя ("
            << (int)M << ")" << "\nИнвертируем значение полученного регистра reg_1\n";
            std::cout << "~ " << saved_reg_1.binary << " = " << reg_1.binary << '\n';

        }
    }

    if (show_div){
        std::cout << '\n' << std::setw(16) <<  "Осаток(Регистр A)";
        std::cout << std::setw(2) << " | ";
        std::cout << std::setw(24) << "Частное(Регситр reg_2)\n";
        std::cout << A.binary << " | " << reg_1.binary << '\n';
        std::cout << "\nРезультат деления: " << (int)reg_1 << " (" << reg_1.binary << ")";
        std::cout << "\nОстаток деления: " << (int)A << " (" << reg_1.binary << ")\n";
        std::cout << (int)(*this) << " = " << (int)reg_1 << " * " << (int)M << " + " << int(A) << "\n\n";
    }

    return reg_1;
}


bool operator==(const Register& reg_1, const Register& reg_2){
    return reg_1.binary == reg_2.binary;
}

bool operator==(const Register& reg_1, const int& num){
    return (int)reg_1 == num;
}

Register Register::operator<<(const Register& reg2) const{
    Register shifted;
    shifted.setNumber((int)(*this) << reg2.number);
    return shifted;
}


Register Register::operator<<(int num) const{
    Register shifted;
    shifted.setNumber((int)(*this) << num);
    return shifted;
}


Register Register::operator>>(const Register& reg_2) const{
    Register shifted;
    shifted.setNumber((int)(*this) >> reg_2.number);
    return shifted;
}


Register Register::operator>>(int num) const{
    Register shifted;
    shifted.setNumber(this->number >> num);
    return shifted;
}


Register::operator int() const {
    int intNum = 0;
    intNum -= this->binary[0] * (int)pow(2, N - 1);
    for(int i = N - 1; i > 0; --i){
        if (this->binary[i] == 0){
            continue;
        }
        intNum += pow(2, N-i-1);
    }
    return intNum;
}


std::ostream& operator<< (std::ostream &out, const Register& reg) {
    for(int i = 0; i < Register::N; ++i){
        out << reg[i] << ' ';
        if (i == 7){
            out  << ' ';
        }
    }
    out << '\n';
    return out;
}


std::ostream& operator<< (std::ostream &out, const std::vector<int>& bitsArr) {
    for(int i = 0; i < bitsArr.size(); ++i){
        out << bitsArr[i];
        if (i == 7){
            out  << ' ';
        }
    }
    return out;
}


std::istream& operator>> (std::istream &in, Register& reg){
    int num;
    in >> num;
    Register newRegister(num);
    reg = newRegister;
    return in;
}
