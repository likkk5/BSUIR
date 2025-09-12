//Есть два текстовых файла.В первом числа отсортированы по возрастанию, во 
//втором по убыванию.Без выполнения сортировки записать числа из этих файлов в третий файл по возрастанию. sort
#include <iostream>
#include <fstream>

/*
void bubble(int a[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[i]) swap(a[j], a[i]);
        }
    }
}*/

using namespace std;

int main()
{
    ifstream fileIn_1("input1.txt");
    ifstream fileIn_2("input2.txt");
    ofstream fileOut("output.txt");

    int value1, value2;
    int count1 = 0, count2 = 0;

    if (!fileIn_1.is_open() || !fileIn_2.is_open())
    {
        cout << "File error" << endl;
        exit(1);
    }
    while (!fileIn_1.eof())
    {
        fileIn_1 >> value1;
        count1++;
    }
    while (!fileIn_2.eof())
    {
        fileIn_2 >> value2;
        count2++;
    }

    fileIn_1.close();

    fileIn_1.open("input1.txt");
    int pos1 = 0;
    int pos2 = fileIn_2.tellg();
    std::cout << "pos2 = " << pos2 << "\n";
    //fileIn_2.seekg(-1, std::ios::end);

    //while(!fileIn_2.eof())
    for (int i = count2; i > 0; i--)
    {
        fileIn_2 >> value2;
        std::cout << "value2 = " << value2 << "\n";
        //while (!fileIn_1.eof())
        for (int j = pos1; j < count1 - 1; j++)
        {
            fileIn_1 >> value1;
            std::cout << "value1 = " << value1 << "\n";
            if (value1 < value2)
            {
                fileOut << value1 << " ";
            }
            else
            {
                fileOut << value2 << " ";
                pos1 = j;
                std::cout << "pos1 = " << pos1 << "\n";
                fileIn_1.seekg(pos1, std::ios::beg);
                
                //pos2 = fileIn_2.tellg();
                //std::cout << "pos2 = " << pos2 << "\n";
                fileIn_2.seekg(-2 + i, std::ios::beg);
                //break;
            }
        }
        if (fileIn_1.eof())
        {
            break;
        }
    }

    while (pos2 >= 0)
    {
        fileIn_2 >> value2;
        fileOut << value2 << " ";
        pos2--;
        fileIn_2.seekg(pos2, std::ios::beg);

       // fileIn_2.seekg(pos2);
    }

    while (!fileIn_1.eof())
    {
        fileIn_1 >> value1;
        fileOut << value1 << " ";
    }




    fileIn_1.close();
    fileIn_2.close();
    fileOut.close();
    system("pause");
    return 0;

     
    
    
    
    
    
    
    /*
    ofstream file("Task.bin", ios::app | ios::ate); //дозапись+сортировка
    if (!file) cout << "NOT FOUND";
    else {
        int n;
        cin >> n;
        int* a = new int[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            file << a[i] << " ";
        }
    }
    file.close();
    ifstream fin("Task.bin");
    if (!fin) cout << "NOT FOUND";
    int count = 0, x, i = 0;
    int a[20];
    while (fin >> x) {
        a[i++] = x;
    }
    fin.close();
    for (int k = 0; k < i; k++) {
        std::cout << a[k] << " ";
    }
    cout << "\n";
    bubble(a, i);
    for (int k = 0; k < i; k++) {
        std::cout << a[k] << " ";
    }
    ofstream outf("Task.bin");
    for (int k = 0; k < i; k++) {
        outf << a[k] << " ";
    }
    */
}

