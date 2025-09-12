//100. Дан сивольный файл f. Записать в файл g компоненты файла f в обратном порядке.
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    
    std::ifstream fileIn("f.txt", std::ios::ate);
    std::ofstream fileOut("g.txt");
   
    if (!fileIn.is_open())
    {
        std::cout << "File error" << "\n";
    }
    else
    {
        int max = fileIn.tellg();
        fileIn.seekg(-1, std::ios::end);
        char symbol;
       // std::cout << max;

        for (int i = max; i > 0; i--)
        {
            fileIn >> std::noskipws >> symbol;
            std::cout << symbol;
            fileOut << symbol;
            fileIn.seekg(-2 + i, std::ios::beg);
        }
    }
    
    /*
    int posg;
    char s;
    
    if (!fileIn.is_open())
    {
        std::cout << "File error" << "\n";
    }
    else
    {
        //fileIn.seekg(SEEK_END);
        posg = fileIn.tellg();

        while (posg >= 0)
        {
            fileIn.seekg(posg);

            fileIn >> s;
            std::cout << s << "\n";

            fileOut << s;
            posg--;
        }
    }*/

    fileIn.close();
    fileOut.close();
    system("pause");
    return 0;
}


