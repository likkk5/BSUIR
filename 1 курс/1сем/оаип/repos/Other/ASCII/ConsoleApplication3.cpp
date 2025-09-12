#include <iostream>
#include <windows.h>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    
    for(int i=-128; i<=127;i++)
    std::cout << "i=" << i <<"   " << char(i) << "\n";
}
