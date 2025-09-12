#include <iostream>
#include <fstream>

using namespace std;


int main()
{
    ifstream fileIn;
    fstream fileOut;
    unsigned int count = 0, posg = 0, posp = 0;
    int str1, str2;
    fileIn.open("input.txt");
    fileOut.open("output.txt");
    if (!fileIn.is_open() || !fileOut.is_open())
    {
        cout << "File error" << endl;
        exit(1);
    }
    while (!fileIn.eof())
    {
        fileIn >> str1;
        fileOut << str1 << " ";
        count++;
    }
    fileIn.close();
    fileOut.clear();
    fileOut.seekg(0);
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            fileOut >> str1;
            posg = fileOut.tellg();
            posg++;
            fileOut >> str2;
            if (str1 > str2)
            {
                fileOut.seekg(posp);
                fileOut << str2 << " ";
                posg = fileOut.tellg();
                fileOut << str1 << " ";
                fileOut.seekg(posg);
                posp = posg;
                continue;
            }
            else
            {
                fileOut.seekg(posg);
                posp = posg;
                continue;
            }
        }
        fileOut.clear();
        posg = posp = 0;
        fileOut.seekg(posg);
    }
    fileOut.close();
    system("pause");
    return 0;
}
