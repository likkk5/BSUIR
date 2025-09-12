#include <iostream>
#include <fstream>
#include <string>

std::string SmallWord()
{
    std::ifstream fileIn("f.txt");

    std::string str1, str2, small;
    
    if (!fileIn.is_open())
    {
        std::cout << "File error" << "\n";
        exit(1);
    }

    fileIn >> str1;
    small = str1;

    while (!fileIn.eof())
    {
        fileIn >> str2;
        if (small.length() > str2.length())
        {
            small=str2;
        }
    }
    return small;
}


int main()
{
    std::cout << "The smaller word in file is    " << SmallWord();

   /* std::ifstream streamRead("f.txt");
    char symbol, prevSymbol = '0';
    int maxLength = 0, maxStartFrom = 0;
    int start = 0, end = 0;

    while (streamRead >> std::noskipws >> symbol) {
        if (symbol == ' ' && prevSymbol != ' ') {
            prevSymbol = symbol;
            end = streamRead.tellg();
            end--;
            if ((end - start) < maxLength || maxLength == 0) {
                maxLength = end - start;
                maxStartFrom = start;
            }
            start = end + 1;
        }
        prevSymbol = symbol;
    }
    streamRead.clear();

    for (int i = maxStartFrom; i < maxStartFrom + maxLength; i++)
    {
        streamRead.seekg(i, std::ios::beg);
        streamRead >> symbol;
        std::cout << symbol;

    }*/


}