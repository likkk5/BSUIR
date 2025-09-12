//#include <stdio.h>
#include <iostream>
#include <fstream>

int main()
{
    // два файла - работает ок
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
    fileOut.close();
    return 0;*/


    std::fstream fileIn("f.txt");
    char str1, str2='\0';
    int size = 0, pos1 = 0, pos2 = 0, count=0;

    if (!fileIn.is_open())
    {
        std::cout << "File error" << "\n";
        exit(1);
    }

    while (!fileIn.eof())
    {
        fileIn >> std::noskipws >> str1;
        pos1 = fileIn.tellg();
        pos1++;
        fileIn >> std::noskipws >> str2;

        if ((str1 == ' ') && (str2 == ' '))
        {
            fileIn >> std::noskipws >> str2;
            while (str2 != ' ');
            {
                pos2 = fileIn.tellg();
                count++;
                fileIn >> std::noskipws >> str2;
            }
            if (count != 0)
            {
                fileIn.seekg(pos1);
                fileIn << str2;
                count = 0;
            }
        }
        size++;
    }

    fileIn.clear();
    fileIn.seekg(0);
  
    
    
    
    
    
    return 0;


    
    /* FILE* in = fopen_s("input.txt", "r");
    FILE* out = fopen_s("output.txt", "w");
    char space = 0;
    short c;
    while ((c = getc(in)) != EOF)
        if (c == ' ') {
            if (!space) {
                space = 1;
                putc(' ', out);
            }
        }
        else {
            space = 0;
            putc(c, out);
        }
    fclose(in);
    fclose(out);*/
}