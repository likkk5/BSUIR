#include <iostream>
#include <cmath>
#define bits 8
using namespace std;

string Negate(string& bin_num);
string Complement(int number);
string AddBinary(const string& lhs, const string& rhs);
int SignedMagnitude(string& number);
string reverse(string str);

int main(int argc, const char * argv[]) {
     int first, second;
     cout << "Enter the first number: ";
     cin >> first;
     cout << "Now enter the second number: ";
     cin >> second;
 
     string lhs, rhs, res;

     try {
         lhs = Complement(first);
         rhs = Complement(second);
         std::cout << "\nFirst:\t" << reverse(lhs) << "\nSecond:\t" << reverse(rhs) << '\n';
         res = AddBinary(lhs, rhs);
         std::cout << "The result is: " << SignedMagnitude(res) << '\n';
     }
     catch (overflow_error& e){
         string num = e.what();
         cout << "Overflow: " << SignedMagnitude(num) << '\n';
     }
     catch(exception& e){
         cout <<"Error! " << e.what() << '\n';
     }
     return 0;
}

string AddBinary(const string& lhs, const string& rhs) {
    string result;
    for(int i = 0; i < bits; ++i) {
        result.append(to_string(lhs[i] + rhs[i] - 2 * '0'));
        std::cout << lhs[i]  << " + " << rhs[i] << " = " << ((lhs[i] - '0') ^ (rhs[i] - '0')) << '\n';
    }
    for(int i = 0; i < bits; ++i){
        if (result[i] > '1') {
            result[i + 1] += (result[i] - '0') / 2;
            result[i] = (result[i] - '0') % 2 + '0';
        }
    }
    if((result[bits - 1] != lhs[bits - 1]) &&  lhs[bits - 1] == rhs[bits - 1]) {
        throw std::overflow_error(result);
    }
    return result;
}

string Complement(int number) {
    string in_binary;
    bool neg = false;
    if (number < 0) {
        neg = true;
        number = abs(number);
    }
    while (number) {
        in_binary.append(to_string(number % 2));
        number /= 2;
    }
    if(in_binary.length() < bits) {
        while (in_binary.length() < bits)
            in_binary.append("0");
    }
    if (neg) {
        Negate(in_binary);
    }
    return in_binary;
}

string Negate(string& bin_num) {
    for(int i = 0; i < bits; i++) {
        if(bin_num[i] == '0')
            bin_num[i] = '1';
        else
            bin_num[i] = '0';
    }
    bin_num[0]++;
    for(int i = 0; i < bits; ++i) {
        if (bin_num[i] > '1') {
            bin_num[i + 1] += (bin_num[i] - '0') / 2;
            bin_num[i] = (bin_num[i] - '0') % 2 + '0';
        }
    }
    return bin_num;
}

int SignedMagnitude(string& number) {
    int result = 0;
    bool neg = (number[bits - 1] == '1');
    if (neg) {
        for (int i = 0; i < bits - 1; i++) {
            if (number[i] != '0') break;
            if (i == bits - 2) return -1 * pow(2, bits - 1);
        }
        number = Negate(number);
    }
    for(int i = 0; i < bits - 1; ++i) {
        result += (number[i] - '0') * (int)pow(2, i);
    }
    if(neg) {
        result *= -1;
    }
    return result;
}

string reverse(string str)
{
    long n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
    return str;
}
                                                                
