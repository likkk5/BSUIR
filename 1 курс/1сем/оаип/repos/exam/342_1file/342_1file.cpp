
#include <iostream>
#include <fstream>

int main()
{

    //почти работает
    std::fstream fileIn("f.txt");
    char str1, str2 = '0';
    int size = 0, pos1 = 0, pos2 = 0, count = 0, pos_p;

    if (!fileIn.is_open())
    {
        std::cout << "File error" << "\n";
        exit(1);
    }

    while (fileIn >> std::noskipws >> str1)
    {
        if (str1 == ' ' && str2 == ' ')
        {
            str1 = str2;
            count++;
            continue;
        }
        std::cout << count << "\n";
        if (count != 0)
        {
            for (int i = 0;i <= count;i++)
            {
                pos2 = fileIn.tellg();
                pos2--;
                pos_p = pos2;
                std::cout << "pos2 = " << pos2 << "   str1 = " << str1 << "\n";

                for (i = 0;i < count;i++)
                    while (!fileIn.eof())
                    {
                        pos2--;
                        fileIn.seekg(pos2);
                        fileIn << str1;
                        std::cout << pos2 << "  " << str1 << "\n";
                        pos2++;
                        pos2++;
                        fileIn.seekg(pos2);
                        fileIn >> str1;

                    }
                fileIn.clear();
                fileIn.seekg(pos_p);
            }
        }
        str2 = str1;
        count = 0;
    }
    /*
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
            std::cout << str2 << "\n";
            std::cout << pos2 <<"\n";
          
            fileIn.seekg(pos2);
            while (!fileIn.eof())
            {
                fileIn.seekg(pos2);
                fileIn << str2;
                pos1 = pos2 + 1;
                fileIn.seekg(pos1);
                fileIn >> str2;
                pos2++;
            }
        }
        size++;
    }
    */
    fileIn.clear();
    fileIn.seekg(0);

    return 0;
}


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
//}