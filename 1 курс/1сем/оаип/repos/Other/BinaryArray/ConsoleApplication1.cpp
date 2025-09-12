
#include <iostream>
// конвертация числа из 10СС в 2СС 
std::string ConvertDecimalBinary(int k, int m)
{
    int ii = 0;
    std::string temp_str;

    while (k != 0)
    {
        temp_str += k % 2 + 48;
        k = k / 2;
        ii = ii + 1;
    }
    std::reverse(temp_str.begin(), temp_str.end());
    
    while (temp_str.length() < m)
    {
        temp_str = '0' + temp_str;
    }
    return temp_str;
}

int* GenerationBinaryArray(int* array_slave, int n, int m) 
{
    std::string str;
    int ii = 0;

    for (int kk = 0;kk < n;kk++)
    {
        str = ConvertDecimalBinary(kk,m);
        std::cout << kk << "\n";
        for (int jj = 0;jj < m;jj++)
        {
            *(array_slave + ii * m + jj) = str[jj]-48;
            std::cout << *(array_slave + ii * m + jj) << " ";
        }
        std::cout << "\n";
        ii++;

    }

    return array_slave;
}

int main()
{
    int n = 16;
    int m = 4;

    int* array_slave = nullptr;
    array_slave = new int[n * m];
    
    array_slave = GenerationBinaryArray(array_slave, n, m);

    delete [] array_slave;
    array_slave = nullptr;
}

