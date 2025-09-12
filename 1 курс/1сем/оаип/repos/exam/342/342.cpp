// В текстовом файле удалить лишние пробелы
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    
    std::ifstream streamRead = std::ifstream("f.txt");
    std::ofstream streamWrite = std::ofstream("g.txt");

    char symbol, prevSymbol = '0';
    
    while (streamRead >> std::noskipws >> symbol) {
        //std::cout << symbol;

        if (symbol == ' ' && prevSymbol == ' ') {
            continue;
        }
        streamWrite << symbol;

        prevSymbol = symbol;
    }
    streamRead.close();
    streamWrite.close();


    // мой вариант: два файла - работает ок
    /*std::ifstream fileIn("f.txt");
    std::ofstream fileOut("g.txt");
    std::string str;

    if (!fileIn.is_open())
    {
        std::cout << "File error" << "\n";
        exit(1);
    }

    while (!fileIn.eof())
    {
        fileIn >> str;
        fileOut << str << " ";
    }

    fileIn.close();
    fileOut.close();*/

    return 0;
}
