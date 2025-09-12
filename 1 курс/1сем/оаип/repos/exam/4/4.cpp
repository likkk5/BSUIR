#include <iostream>
#include <fstream>   

void CreateBinaryFile()
{
    std::ofstream fileIn;
    if (!fileIn.is_open()) {
        fileIn.open("input.data", std::ofstream::binary | std::ofstream::app | std::ofstream::ate);
    }
    fileIn.clear();

    int value;
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::cin >> value;
        fileIn.write((char*)&value, sizeof(int));
    }
   
    fileIn.clear();
    fileIn.close();
}
void ReadBinaryFile()
{
    std::ifstream fileIn("input.data", std::ifstream::binary);

    int  value;
   
    if (!fileIn)
    {
        CreateBinaryFile();
    }
   
    fileIn.open("input.data", std::ifstream::binary);
    while (!fileIn.eof())
    {
        fileIn.read((char*)&value, sizeof(int));
        std::cout << value << " ";
    }
    std::cout << "\n";

    fileIn.close();
}

int main()
{
    //FILE* fopen(const* fileIn, const char* rb+);
   // std::ifstream fileIn("input.data", std::ifstream::binary);
    ReadBinaryFile();
}