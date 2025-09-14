//
// Created by Vladislav Kremenevskiy on 4/18/21.
//

#include "Float.h"





Float::Float() {
    number = std::vector<int>(N, 0);
    mantissa = std::vector<int>(m_size, 0);
    exp = std::vector<int>(e_size, 0);
}


Float::Float(float num) : Float() {

    float_num = num;
    int entire = abs((int)num);
    float fraction = abs(num) - (float)entire;
    std::vector<int> entireBin = entireToBin(entire);
    std::vector<int> fractionBin = fractionToBin(fraction, 23);

    int offset = 0;
    if (entire > 0)
        offset = (int)entireBin.size() - 1;
    else if (entire == 0 && fraction != 0){
        for(int i = 0; fractionBin[i] != 1; ++i){
            offset--;
        }
        offset--;
    }


    int i = 0;
    if(num >= 0){
        sign = 0;
        number[i] = 0;
        ++i;
    }
    else{
        sign = 1;
        number[i] = 1;
        ++i;
    }

    zero_exp = maxInt(e_size);
    expInt = offset;
    int exponent = maxInt(e_size) + offset;
    exp = buildExp(exponent, e_size);
    while(i < e_size+1){
        number[i] = exp[i-1];
        ++i;
    }

//    Don't keep track first one in mantissa and skip it

    // combine two vectors and to mantisa

    std::vector<int> trimmed = trimV(entireBin, fractionBin, m_size);
    int k = 0;
    while(trimmed[k] != 1 && k < trimmed.size()){
        ++k;
    }
    ++k;
    for(int m = 0; i < N; ++k){

        number[i] = trimmed[k];
        mantissa[m] = trimmed[k];
        ++i;
        ++m;

    }

//    for(int k = 1; i < N && k < entireBin.size(); ++k){
//
//        number[i] = entireBin[k];
//        mantissa[m] = entireBin[k];
//        ++i;
//        ++m;
//    }
//
//    for(int k = 0; i < N && k < fractionBin.size(); ++k){
//        if (entire == 0 && fraction == 0){
//            break;
//        }
//        if (entire == 0 && k == 0){
//            while(fractionBin[k] != 1 && k < fractionBin.size()){
//                ++k;
//            }
//            continue;
//        }
//        number[i] = fractionBin[k];
//        mantissa[m] = fractionBin[k];
//        ++i;
//        ++m;
//    }
}


Float::Float(const Float& num) {
    this->expInt = num.expInt;
    this->number = num.number;
    this->exp = num.exp;
    this->mantissa = num.mantissa;
    this->sign = num.sign;
    this->float_num = num.float_num;
}



Float& Float::operator=(const Float &floating_2) {
    this->expInt = floating_2.expInt;
    this->number = floating_2.number;
    this->exp = floating_2.exp;
    this->mantissa = floating_2.mantissa;
    this->sign = floating_2.sign;
    this->float_num = floating_2.float_num;
    return *this;
}


std::vector<int> Float::buildBinary(int num, int size){
    std::vector<int> bin(size, 0);
    for(int i = 0; num > 0; ++i){
        bin[size-1-i] = num % 2;
        num /= 2;
    }
    return bin;
}


int Float::maxInt(int exp_size){
    return (int)pow(2, e_size - 1) - 1;
}


std::vector<int> Float::buildExp(int exponent, int exp_size){
    if (exponent == 127){
        return std::vector<int> (exp_size, 0);
    }
    std::vector<int> binExp(exp_size, 0);
    for(int i = 0; i <= exp_size; ++i){
        binExp[exp_size-i-1] = exponent % 2;
        exponent /= 2;
    }
//    std::reverse(binExp.begin(), binExp.end());
    return binExp;
}


std::vector<int> Float::entireToBin(int entire){
    std::vector<int> binArr(0,0);
    while(entire > 0){
        binArr.push_back(entire % 2);
        entire /= 2;
    }
    std::reverse(binArr.begin(), binArr.end());
    return binArr;
}


std::vector<int> Float::fractionToBin(float fraction, int size){
    std::vector<int> binArr(0, 0);
    for(int i = 0; i < size; ++i){
        fraction *= 2;
        if (fraction >= 1){
            binArr.push_back(1);
            fraction -= 1;
        }
        else
            binArr.push_back(0);
    }
    return binArr;
}


std::ostream& operator<<(std::ostream& out, const std::vector<int>& v){
    for(auto &i : v){
        out << i;
    }
    return out;
}


std::ostream& operator<<(std::ostream& out, const Float& floating){
    out << floating.sign << ' ';
    out << floating.exp << ' ';
    out << floating.mantissa << '\n';
    return out;
}


int Float::binEntireToInt(const std::vector<int> &v) {
    int number = 0;
    for(int i = 0; i < v.size(); ++i){
       number += v[v.size()-1-i] * (int)pow(2, i);
    }
    return number;
}


int Float::entireFromMantissa(const std::vector<int>& mantissa, int exp){
    int entire = 0;

    entire += pow(2, exp);
    for(int i = 0; i < exp; ++i){
        entire += mantissa[i] * (int)pow(2, exp-i-1);
    }
    return entire;
}


float Float::fractionFromMantissa(const std::vector<int>& mantissa, int exp){

    float fraction = 0;
    if (exp >= 0) {
        for (int i = exp, k = -1; i < m_size; ++i, --k) {
            fraction += mantissa[i] * (float) pow(2, k);
        }
    }
    else{
        fraction += pow(2, exp);
        for (int i = 0, k = exp-1; i < m_size; ++i, --k) {
            fraction += mantissa[i] * (float) pow(2, k);
        }
    }
    return fraction;
}


Float::operator float() const {
    float num = 0;
    num += (float)entireFromMantissa(mantissa, expInt);
    num += fractionFromMantissa(mantissa, expInt);
    if (sign == 1)
        num *= -1;
    return num;
}


std::vector<int> Float::addBinary(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<int> result(v1.size(), 0);
    int r = 0;
    for(int i = v1.size() - 1; i >= 0; --i){
        if (v1[i] + v2[i] + r == 0){
            result[i] = 0;
            r = 0;
        }
        if (v1[i] + v2[i] + r == 1){
            result[i] = 1;
            r = 0;
        }
        if (v1[i] + v2[i] + r == 2){
            result[i] = 0;
            r = 1;
        }
        if (v1[i] + v2[i] + r == 3){
            result[i] = 1;
            r = 1;
        }
    }

    return result;
}


std::vector<int> Float::addBinaryMul(const std::vector<int>& v1, std::vector<int>& v2) {
    int v2_size = v2.size();
    std::vector<int> newv2(v1.size(), 0);
    int k = 0;
    for(int i = newv2.size()-1; i >= 0; --i){
        if (k < v2_size){
            newv2[i] = v2[v2.size()-k-1];
            k++;
        }
    }
    v2 = newv2;
    std::vector<int> result(v1.size(), 0);
    int r = 0;
    for(int i = v1.size() - 1; i >= 0; --i){
        if (v1[i] + v2[i] + r == 0){
            result[i] = 0;
            r = 0;
        }
        if (v1[i] + v2[i] + r == 1){
            result[i] = 1;
            r = 0;
        }
        if (v1[i] + v2[i] + r == 2){
            result[i] = 0;
            r = 1;
        }
        if (v1[i] + v2[i] + r == 3){
            result[i] = 1;
            r = 1;
        }
    }
    std::vector<int> extra(v1.size() + 1, 0);
    extra[0] = 1;
    if (r == 1){
        for(int i = 1; i < extra.size(); ++i){
            extra[i] = result[i-1];
        }
        return extra;
    }
    return result;
}


std::pair<std::vector<int>, int> Float::addBinary_s(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<int> result(v1.size(), 0);
    int r = 0;
    for(int i = v1.size() - 1; i >= 0; --i){
        if (v1[i] + v2[i] + r == 0){
            result[i] = 0;
            r = 0;
        }
        else if (v1[i] + v2[i] + r == 1){
            result[i] = 1;
            r = 0;
        }
        else if (v1[i] + v2[i] + r == 2){
            result[i] = 0;
            r = 1;
        }
        else if (v1[i] + v2[i] + r == 3){
            result[i] = 1;
            r = 1;
        }
    }

    return {result, r};
}

std::vector<int> Float::rMove(const std::vector<int>& v){
    std::vector<int> result(v.size(), 0);
    for(int i = (int)v.size()-1; i >= 1; --i){
        result[i] = v[i-1];
    }
    result[0] = 0;
    return result;
}


std::vector<int> Float::lMove(const std::vector<int>& v){
    std::vector<int> result(v.size(), 0);
    for(int i = 0; i < v.size() - 1; ++i){
        result[i] = v[i+1];
    }
    result[v.size()-1] = 0;
    return result;
}



//Float Float::operator>>(int num) const{
//    Float result(0);
//    while(num > 0) {
//        result.mantissa = rMove(mantissa);
//        result.exp = addBinary(exp, buildBinary(1, e_size));
//        result.expInt += 1;
//        --num;
//    }
//    return result;
//}



//Float Float::operator<<(int num) const{
//    Float result(0);
//    while(num > 0) {
//        result.mantissa = lMove(mantissa);
//        result.exp = addBinary(exp, buildBinary(1, e_size));
//        result.expInt += 1;
//        --num;
//    }
//    return result;
//}


std::vector<int> Float::subBinary(const std::vector<int> &v1, const std::vector<int> &v2) {
    std::vector<int> res(v1.size(), 0);
    int r = 0;
    for(int i = (int)v1.size() - 1; i >= 0; --i) {
        if (v1[i] - v2[i] - r == 1) {
            res[i] = 1;
            r = 0;
        }
        else if (v1[i] - v2[i] - r == 0) {
            res[i] = 0;
            r = 0;
        }
        else if (v1[i] - v2[i] - r == -1) {
            res[i] = 1;
            r = 1;
        }
        else if (v1[i] - v2[i] - r == -2) {
            res[i] = 1;
            r = 1;
        }
    }
    return res;
}


Float Float::operator+(Float &floating_2) {

//    Float fl2_copy(floating_2);
    if (show_add){
        std::cout << "--Сложение--\n";
    }

    if(show_add){
        std::cout << "Первое число: " << (float)float_num << " (Порядок: " << this->expInt  << " )" << '\n';
        std::cout << *this;
        std::cout << "Второе число: " << (float)floating_2 << " (Порядок: " << this->expInt  << " )" << '\n';
        std::cout << floating_2;
    }

    if(this->float_num == 0){
        if (show_add){
            std::cout << "Так как одно из чисел равно 0, то результат равен другому числу!\n";
            std::cout << "Ответ: " << floating_2.float_num << '\n';
        }
        return floating_2;
    }
    else if(floating_2.float_num == 0){
        if (show_add){
            std::cout << "Так как одно из чисел равно 0, то результат равен другому числу!\n";
            std::cout << "Ответ: " << this->float_num << '\n';


        }
        return *this;
    }

    int diff = this->expInt - floating_2.expInt;
    std::vector<int> newMantissa;
    int exponent = this->expInt > floating_2.expInt ? this->expInt : floating_2.expInt;

    std::vector<int> mant;
    std::vector<int> constMant;
    if (diff > 0){
        mant = binFromMantissa(floating_2.mantissa);
        constMant = binFromMantissa(this->mantissa);
    }
    else{
        mant = binFromMantissa(this->mantissa);
        constMant = binFromMantissa(floating_2.mantissa);
    }

    while(diff != 0) {
        if (diff > 0) {
            floating_2.expInt += 1;
            --diff;
        }
        else if (diff < 0) {
            this->expInt += 1;
            ++diff;
        }
        mant = rMove(mant);
    }

    this->exp = buildExp(exponent + zero_exp, e_size);
    floating_2.exp = buildExp(exponent + zero_exp, e_size);


    if (show_add){
        std::cout << "\nПосле уравнивания порядков:\n";
        std::cout << *this;
        std::cout << floating_2;
    }

    Float result(0);

    if (this->sign == floating_2.sign) {
        auto resMantissa = addBinary_s(mant, constMant);


        if (show_add) {
            std::cout << "Результирующая мантисса: " << resMantissa.first;
        }

        if (resMantissa.second == 1) {
            exponent += 1;
//            resMantissa.first = lMove(resMantissa.first);
//            while (resMantissa.first[0] != 1) {
//                exponent += 1;
//                resMantissa.first = lMove(resMantissa.first);
//            }
//            resMantissa.first = lMove(resMantissa.first);
            result.mantissa = resMantissa.first;

        }
        else{
            result.mantissa = mantissaFromBin(resMantissa.first);
        }


        result.expInt = exponent;
        result.exp = buildExp(exponent + result.zero_exp, e_size);
        result.float_num = (float) result;
        result.sign = this->sign;
    }
    else {
        std::vector<int> subRes;
//        if (floating_2.float_num > this->float_num){
            bool bigger_mant = false;
            for(int i = 0; i < mant.size(); ++i){
                if (mant[i] > constMant[i]){
                    bigger_mant = true;
                    break;
                }
                else if (mant[i] < constMant[i]){
                    bigger_mant = false;
                    break;
                }
            }

            if (bigger_mant){
                subRes = subBinary(mant, constMant);
                if(show_add){
                    std::cout << "Вычитаем мантиссы: "  << '\n';
                    std::cout << mant << ' - \n';
                    std::cout << constMant << '\n';
                    std::cout << "---------------------------------\n";
                    std::cout << subRes << '\n';
                }
            }
            else {
                subRes = subBinary(constMant, mant);
                if (show_add) {
                    std::cout << "Вычитаем мантиссы: " << '\n';
                    std::cout << constMant << " - \n";
                    std::cout << mant << '\n';
                    std::cout << "---------------------------------\n";
                    std::cout << subRes << '\n';
                }
            }

//        }

        while (subRes[0] != 1) {
            exponent -= 1;
            subRes = lMove(subRes);
        }
//        subRes = lMove(subRes);


        result.mantissa = mantissaFromBin(subRes);
        result.expInt = exponent;
        result.exp = buildExp(exponent + result.zero_exp, e_size);
        result.float_num = (float) result;
        if (this->float_num - floating_2.float_num > 0){
            result.sign = 0;
        }
        else
            result.sign = 1;

    }

    if (show_add){
        std::cout << "\nРезультат: " << this->float_num << " - " << floating_2.float_num << " = "
            << (float)result << '\n';
        std::cout << result;
    }

    return result;
}


std::vector<int> Float::make2c(std::vector<int> &bin) {
    std::vector<int> twosBin(bin.size(), 0);
    for(int i = 0; i < bin.size(); ++i) {
        bin[i] == 1 ? twosBin[i] = 0 : twosBin[i] = 1;
    }

    int i = (int)bin.size()-1;
    while(i >= 0){
        if (twosBin[i] == 1) {
            twosBin[i] = 0;
        }
        else {
            twosBin[i] = 1;
            break;
        }
        --i;
    }
    return twosBin;
}


Float Float::operator-(Float &floating_2) {

    if (show_sub){
        std::cout << "---Вычитание---\n";
        std::cout << this->float_num << " - " << floating_2.float_num << '\n';

        std::cout << "Первое число: " << (float)float_num << " (Порядок: " << this->expInt  << " )" << '\n';
        std::cout << *this;
        std::cout << "Второе число: " << (float)floating_2 << " (Порядок: " << this->expInt  << " )" << '\n';
        std::cout << floating_2;

        std::cout << "Вычитание = сложение меняя знак у второго числа\n";
    }
    Float result(0);
    if (floating_2.sign == 1){
        floating_2.sign = 0;
    }
    else{
        floating_2.sign = 1;
    }

    if (show_sub) {
        std::cout << "Его новое представление: \n";
        std::cout << floating_2;
    }

    result = *this + floating_2;

//    if (show_sub){
//        std::cout << "--Вычитание--\n";
//    }
//
//    if(show_sub){
//        std::cout << "Первое число: " << this->float_num << " (Порядок: " << this->expInt  << " )" << '\n';
//        std::cout << *this;
//        std::cout << "Второе число: " << floating_2.float_num << " (Порядок: " << this->expInt  << " )" << '\n';
//        std::cout << floating_2;
//    }
//
//    if(this->float_num == 0){
//        return floating_2;
//    }
//    else if(floating_2.float_num == 0){
//        return *this;
//    }
//
//    int diff = this->expInt - floating_2.expInt;
//    std::vector<int> newMantissa;
//    int exponent = this->expInt > floating_2.expInt ? this->expInt : floating_2.expInt;
//
//    std::vector<int> mant;
//    std::vector<int> constMant;
//    if (diff > 0){
//        mant = binFromMantissa(floating_2.mantissa);
//        constMant = binFromMantissa(this->mantissa);
//    }
//    else{
//        mant = binFromMantissa(this->mantissa);
//        constMant = binFromMantissa(floating_2.mantissa);
//    }
//
//    while(diff != 0) {
//        if (diff > 0) {
//            floating_2.expInt += 1;
//            --diff;
//        }
//        else if (diff < 0) {
//            this->expInt += 1;
//            ++diff;
//        }
//        mant = rMove(mant);
//    }
//
//    this->exp = buildExp(exponent + zero_exp, e_size);
//    floating_2.exp = buildExp(exponent + zero_exp, e_size);
//
//
//    if (show_sub){
//        std::cout << "\nПосле уравнивания порядков:\n";
//        std::cout << *this;
//        std::cout << floating_2;
//    }
//
//    std::vector<int> inverse = make2c(mant);
//    auto resMantissa = addBinary_s(mant, constMant);
//
//
//    if (show_sub){
//        std::cout << "Результирующая мантисса: " << resMantissa.first;
//    }
//
////    if (resMantissa.second == 1){
////        exponent +=1;
////        resMantissa.first = lMove(resMantissa.first);
////        while(resMantissa.first[0] != 1){
////            exponent += 1;
////            resMantissa.first = lMove(resMantissa.first);
////        }
////        resMantissa.first = lMove(resMantissa.first);
////    }
//
//    Float result(0);
//    result.mantissa = mantissaFromBin(resMantissa.first);
//    result.expInt = exponent;
//    result.exp = buildExp(exponent + result.zero_exp, e_size);
//    result.float_num = (float)result;
//
//    if (show_sub){
//        std::cout << "\nРезультат: " << this->float_num << " + " << floating_2.float_num << " = "
//                  << result.float_num << '\n';
//        std::cout << result;
//    }
//
//    return result;

}


std::vector<int> Float::truncMantissa(std::vector<int> m) {
    std::vector<int> truncated(0, 0);
    int cnt_zer = 0;
    for(int i = m.size() - 1; i >= 0; --i){
        if (m[i] == 0) {
            ++cnt_zer;
        }else{
            break;
        }
    }

    for(int i = 0; i < m.size() - cnt_zer; ++i){
        truncated.push_back(m[i]);
    }
    return truncated;
}


Float Float::operator*(Float &floating_2) {

    if (show_mul) {
        std::cout << "---Умножение---\n";

        std::cout << this->float_num << " * " << floating_2.float_num << '\n';

        std::cout << "Первое число: " << (float) float_num << " (Порядок: " << this->expInt << " )" << '\n';
        std::cout << *this;
        std::cout << "Второе число: " << (float) floating_2 << " (Порядок: " << this->expInt << " )" << '\n';
        std::cout << floating_2;
    }

    auto mant_1 = binFromMantissa(this->mantissa);
    auto mant_2 = binFromMantissa(floating_2.mantissa);

    std::vector<int> mul(0, 0);


    mant_1 = truncMantissa(mant_1);
    auto truncated_2 = truncMantissa(mant_2);
    std::vector<int> sum(mant_1.size(), 0);

    for(int i = 0; i < truncated_2.size(); ++i){
         std::vector<int> num(mant_1.size() + i);
         for(int k = 0; k < num.size(); ++k){
             if (k < mant_1.size()) {
                 num[k] = mant_1[k];
             }
             else{
                 num[k] = 0;
             }
         }
         if (truncated_2[i] == 0){
             continue;
         }
         else{
             sum = addBinaryMul(num, sum);
         }
    }

    if(show_mul){
        std::cout << "Переменожение мантис:\n";
        std::cout << mant_1 << " * " <<'\n';
        std::cout << truncated_2 << '\n';
        std::cout << "------------------------\n";
        std::cout << sum << '\n';
    }


    std::vector<int> newMant(m_size, 0);
    for(int i = 1; i < sum.size(); i++){
        newMant[i-1] = sum[i];
    }

    Float result(0);
    result.mantissa = newMant;


    int exponent = floating_2.expInt + this->expInt;
    result.exp = buildExp(zero_exp + exponent, e_size);
    if (this->sign != floating_2.sign){
        result.sign = 1;
    }
    else{
        result.sign = 0;
    }
    result.expInt = exponent;

    int i = 1;
    for(int k = 0; k < result.exp.size(); ++k){
        result.number[i] = result.exp[k];
    }
    for(int k = 0; k < result.mantissa.size(); ++k){
        result.number[i] = result.mantissa[k];
    }


    if (show_mul){
        std::cout << "Порядок первого: " << this->expInt << " (" << this->exp <<  " )" << '\n';
        std::cout << "Порядок второго: " << floating_2.expInt << " (" << floating_2.exp <<  " )" << '\n';
        std::cout << "Результирующий порядок (после нормализации) : " << result.expInt
        << " (" << result.exp <<  " )" << '\n';

        std::cout << "Ответ: " << this->float_num << " * " << floating_2.float_num << " = " << (float)result << '\n';
        std::cout << result;
    }

    return result;
}


//Float Float::operator/(Float& floating_2){
//    int resSign = 0;
//    if (this->sign + floating_2.sign == 1){
//        resSign = 1;
//    }
//    int exp = this->expInt - floating_2.expInt;
//
//    std::vector<int> mant_1 = binFromMantissa(this->mantissa);
//    std::vector<int> mant_2 = binFromMantissa(floating_2.mantissa);
//    Register m_1(mant_1);
//    Register m_2(mant_2);




//}





std::vector<int> Float::trimV(const std::vector<int> &v_1, const std::vector<int> &v_2, int size) {
    std::vector<int> trimmed(size, 0);
    int i = 0;
    int k = 0;
    while(i < size) {
        if (i < v_1.size()) {
            trimmed[i] = v_1[i];
        } else {
            trimmed[i] = v_2[k];
            ++k;
        }
        ++i;
    }
    return trimmed;
}


std::vector<int> Float::binFromMantissa(std::vector<int> &m) {
    std::vector<int> bin(m.size()+1, 0);
    for(int i = 0; i < bin.size(); ++i){
        if (i == 0){
            bin[i] = 1;
            continue;
        }
        bin[i] = m[i-1];
    }
    return bin;
}


std::vector<int> Float::mantissaFromRandBin(std::vector<int>& bin){
    std::vector<int> m(m_size, 0);
    for(int i = 1; i < m.size(); ++i){
        m[i-1] = bin[i];
    }
    return m;
}


std::vector<int> Float::mantissaFromBin(std::vector<int> &bin) {
    std::vector<int> m(bin.size()-1, 0);
    for(int i = 1; i < bin.size(); ++i){
        m[i-1] = bin[i];
    }
    return m;
}



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


std::vector<int> Register::operator*(Register& reg_2){


    Register A;
    int Q1 = 0;
    int A1 = 0;



    for(int i = N-1; i >= 0; --i) {

        if (Q1 == 0 && reg_2[N-1] == 1){
            A = A - *this;
        }
        else if (Q1 == 1 && reg_2[N-1] == 0){
            A = A + *this;
        }


//        shifting
        A1 = A.binary[N-1];
        A = A >> 1;
        Q1 = reg_2.binary[N-1];
        reg_2 = reg_2 >> 1;
        reg_2.setIndexedVal(0, A1);
//        reg_2[0] = A1;


    }
    return reg_2.binary;
//    return getBigNum(A, reg_2);
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




    int Qn{};
    for (int i = N - 1; i >= 0; --i) {
        Qn = reg_1[0];
        A = A << 1;
        reg_1 = reg_1 << 1;
        A[N - 1] = Qn;



        int A_sign = A[0];

        if (M[0] == A[0]) {
            A = A - M;

        } else {
            A = A + M;

        }

        if (A_sign == A[0] || (A == 0 && reg_1 == 0)) {
            reg_1.setIndexedVal(N - 1, 1);

        } else {
            if (M[0] == A_sign) {
                A = A + M;
            }
            else{
                A = A - M;
            }
            reg_1.setIndexedVal(N - 1, 0);

        }


    }

    if ((*this)[0] != M[0]) {
        Register saved_reg_1(reg_1);
        reg_1.reverseBits();


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





std::istream& operator>> (std::istream &in, Register& reg){
    int num;
    in >> num;
    Register newRegister(num);
    reg = newRegister;
    return in;
}
