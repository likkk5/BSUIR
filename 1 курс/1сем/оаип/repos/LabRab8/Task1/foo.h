#pragma once
#include <iostream>                   
#include <windows.h>
#include <stdio.h>		// ��� �����, ������ (scanf, printf)
#include <conio.h>		// ��� �������� ��������� (getch)
#include <string>

// ���� � �������� �� ������������ �����: ����������� ����� - �� 0, �� �������������, �� ������������, �� �������� �����, �� ��������� 2147483647
int InputNumber(int ii, int max)
{
    int number;
    std::string temp_input, check_string;

    while (true)
    {
        if (ii == 1)
        {
            printf("������� ���������� ������� �� ������� [1 .. %d]: ", max);
        }
        if (ii == 2)
        {
            printf("������� ����� ������ �� ������� [1 .. %d]: ", max);
        }
        if (ii == 3)
        {
            printf("������� ���������� ��������� ���� �� ������� [1 .. %d]: ", max);
        }
        if (ii == 4)
        {
            printf("������� ����� ������, ����� �������� ���� ���������� ����������: ");
        }
        if (ii == 6)
        {
            printf("������� ����� �������� ������: ");
        }
        if (ii == 7)
        {
            printf("������� ����� ���������� ������: ");
        }
        if (ii == 8)
        {
            printf("������� ����� �������������� ������: ");
        }
        getline(std::cin, temp_input);

        if ((temp_input[0] >= 48) && (temp_input[0] <= 57))
        {
            // <=2147483647
            if ((temp_input.length() < 10) || ((temp_input.length() == 10) && ((temp_input[0] < 50) || ((temp_input[0] == 50) && (temp_input[1] <= 49) && (temp_input[2] <= 52) && (temp_input[3] <= 55) && (temp_input[4] <= 52) && (temp_input[5] <= 56) && (temp_input[6] <= 51) && (temp_input[7] <= 54) && (temp_input[8] <= 52) && (temp_input[9] <= 55)))))
            {
                number = std::stoi(temp_input);
                check_string = std::to_string(number);

                if ((check_string.length() != temp_input.length()) || (number < 1) || (number > max))
                {
                    printf("��������� ����. ������������ ��������.\n");
                    //while (getchar() != '\n');
                }
                else
                {
                    return number;
                    break;
                }
            }

            else
            {
                printf("��������� ����. ������������ ��������.\n");
                //while (getchar() != '\n');
            }
        }
        else
        {
            printf("��������� ����. ������������ ��������.\n");
            //while (getchar() != '\n');
        }
    }
    printf("\n");
}

// ���� ������ �������� � �������� (����� �����������/����������)
char* InputString(int ii, int max)
{
    int jj, kk = 0;
    std::string temp_input;
    char ch[MAX_LENGHT_STRING]{ '\0' };

    while (true)
    {
        if (ii == 1)
        {
            printf("������� ����� �����������: ");
        }
        if (ii == 2)
        {
            printf("������� ����� �����������: ");
        }

        getline(std::cin, temp_input);
        if ((temp_input.length() == 0) || (temp_input.length() > max))
        {
            printf("��������� ����. ������������ ��������.\n");
            //while (getchar() != '\n');
        }
        else
        {
            kk = 0;
            for (jj = 0;jj < temp_input.length();jj++)
            {
                if ((temp_input[jj] < -64) || ((temp_input[jj] > -1) && (temp_input[jj] < 65)) || ((temp_input[jj] > 90) && (temp_input[jj] < 97)) || (temp_input[jj] > 122))
                {
                    kk++;
                }
            }
            if (kk != 0)
            {
                printf("��������� ����. ������������ ��������.\n");
                //while (getchar() != '\n');
            }
            else
            {
                for (jj = 0;jj < temp_input.length();jj++)
                {
                    ch[jj] = temp_input[jj];
                }
                return ch;
                break;
            }
        }
    }
}

// ���� ������� � �������� (������ ��:��)
char* InputTime(int ii, int max)
{
    int jj, kk = 0;
    std::string temp_input;
    char ch[MAX_COUNT_TIME]{ '\0' };

    while (true)
    {
        if (ii == 1)
        {
            printf("������� ����� �������� ������ (������ ��:��): ");
        }
        getline(std::cin, temp_input);
        if ((temp_input.length() != max - 1))
        {
            printf("��������� ����. ������������ ��������.\n");
        }
        else
        {
            kk = 0;
            if (temp_input[2] == ':')
            {
                kk++;
            }

            for (jj = 0;jj < temp_input.length();jj++)
            {
                if ((temp_input[jj] >= 48) && (temp_input[jj] <= 57) && (jj != 2))
                {
                    kk++;
                }
            }

            if (kk != temp_input.length())
            {
                printf("��������� ����. ������������ ��������.\n");
                //while (getchar() != '\n');
            }
            else
            {
                int hour = 0, min = 0;
                hour = (temp_input[0] - 48) * 10 + (temp_input[1] - 48);
                min = (temp_input[3] - 48) * 10 + (temp_input[4] - 48);
                if ((hour >= 0) && (hour <= 23) && (min >= 0) && (min <= 59))
                {
                    for (jj = 0;jj < temp_input.length();jj++)
                    {
                        ch[jj] = temp_input[jj];
                    }
                    return ch;
                    break;
                }
                else
                {
                    printf("��������� ����. ������������ ��������.\n");
                    //while (getchar() != '\n');
                }
            }
        }
    }
}

// ���� ���������� ������� � ������������ ������� ��������
int NumberOfTrains(void)
{
    return InputNumber(1, MAX_COUNT_TRAIN);
}

// ���� ��������� ��������� ������������� ������� � ��������� ����������� �������
void FillTrains1(depo* ftrains, int famountoftr)
{
    int i;
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};

    printf_s("\n��� ��������� ������ � ���������� ���������� � %d �������.\n", famountoftr);

    for (i = 1; i <= famountoftr; i++, ftrains++)
    {
        printf("\n���� ���������� �� %d-�� ������.\n", i);

        ftrains->amount = InputNumber(2, MAX_NUMBER_TRAIN);

        ch1 = InputString(1, MAX_LENGHT_STRING);
        strcpy_s(ftrains->departure, ch1);

        ch1 = InputString(2, MAX_LENGHT_STRING);
        strcpy_s(ftrains->destination, ch1);

        ch1 = InputTime(1, MAX_COUNT_TIME);
        strcpy_s(ftrains->departure_time, strlen(ch1) + 1, ch1);

        ftrains->number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);
    }
    //delete[] ch1;
}

// ���� ��������� ��������� ������������� ������� ���� ������������ �� ������ ����� ����� lastTrain
void FillTrains2(depo* ftrains, int* famountoftr)
{
    int i = 0, repeat3 = 0, lastTrain;
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};

    //����� ������, ����� �������� ���� ���������� ����������
    lastTrain = InputNumber(4, MAX_NUMBER_TRAIN);
    printf_s("\n��� ��������� ������ � ���������� ���������� � ������� ���� �� ������� ����� ����� %d", lastTrain);
    do
    {
        i++;
        *famountoftr = *famountoftr + 1;
        printf("\n���� ���������� �� %d-�� ������.\n", i);

        ftrains[i - 1].amount = InputNumber(2, MAX_NUMBER_TRAIN);

        ch1 = InputString(1, MAX_LENGHT_STRING);
        strcpy_s(ftrains[i - 1].departure, ch1);

        ch1 = InputString(2, MAX_LENGHT_STRING);
        strcpy_s(ftrains[i - 1].destination, ch1);

        ch1 = InputTime(1, MAX_COUNT_TIME);
        strcpy_s(ftrains[i - 1].departure_time, strlen(ch1) + 1, ch1);

        ftrains[i - 1].number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);


        if (ftrains[i - 1].amount == lastTrain)
        {
            printf("���� ������������� ����������� ������� �������� ��������\n");
            repeat3 = 0;
            break;
        }
        else
        {
            repeat3 = 1;
        }
    } while (repeat3 == 1);

    *famountoftr = *famountoftr - 1;
    //delete ch1;
}

// ���� ��������� ��������� ������������� ������� ���� ������������ ����� ������� ����������
void FillTrains3(depo* ftrains, int* famountoftr)
{
    int i = 0, repeat3 = 0;
    std::string temp_str3;
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};

    printf_s("\n��� ��������� ������ � ���������� ���������� � �������.\n");
    do
    {
        i++;
        *famountoftr = *famountoftr + 1;
        printf("\n���� ���������� �� %d-�� ������.\n", i);

        ftrains[i - 1].amount = InputNumber(2, MAX_NUMBER_TRAIN);

        ch1 = InputString(1, MAX_LENGHT_STRING);
        strcpy_s(ftrains[i - 1].departure, ch1);

        ch1 = InputString(2, MAX_LENGHT_STRING);
        strcpy_s(ftrains[i - 1].destination, ch1);

        ch1 = InputTime(1, MAX_COUNT_TIME);
        strcpy_s(ftrains[i - 1].departure_time, strlen(ch1) + 1, ch1);

        ftrains[i - 1].number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);

        printf("��� ����������� ����� ���������� � ��������� ������ ������� ��, ��� ���������� ����� ���������� - ����� ������:  ");
        getline(std::cin, temp_str3);
        if (temp_str3 == "��")
        {
            repeat3 = 1;
        }
        else
        {
            printf("���� ������������� ����������� ������� �������� ��������\n");
            repeat3 = 0;
            break;
        }
    } while (repeat3 == 1);

    *famountoftr = *famountoftr - 1;
    //delete ch1;
}

// ������ ������������� ������� ��������
void PrintTrains(depo* ftrains, const int famountoftr)
{
    int i;
    if (famountoftr == 0)
    {
        printf("\n��� �� ������ ������. ������ ���������� ����������.\n");
        return;
    }
    printf_s("\n���������� � %d ������� ����� ���:\n", famountoftr);
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| � ������ |          ����� �����������          |          ����� ����������           | ����� �������� | ���������� ��������� ���� |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------- \n");
    for (i = 1; i <= famountoftr; i++, ftrains++)
    {
        printf("| %-8d | %35s | %35s | %14s | %-25d |\n",
            ftrains->amount, ftrains->departure, ftrains->destination, ftrains->departure_time, ftrains->number_of_seats_available);
    }
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

// �������� ������� � ������������ ������ ��������
void AddNewTrain(depo* ftrains, int* famountoftr)
{

    int add = (*famountoftr)++;
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};

    printf("\n�������� ����� �����\n");

    ftrains[add].amount = InputNumber(2, MAX_NUMBER_TRAIN);

    ch1 = InputString(1, MAX_LENGHT_STRING);
    strcpy_s(ftrains[add].departure, ch1);

    ch1 = InputString(2, MAX_LENGHT_STRING);
    strcpy_s(ftrains[add].destination, ch1);

    ch1 = InputTime(1, MAX_COUNT_TIME);
    strcpy_s(ftrains[add].departure_time, strlen(ch1) + 1, ch1);

    ftrains[add].number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);

    printf("\n���������� � ����� ������ ������� ���������\n");
}

// ����� �������� �� ������ ������ � ������������ ������� ��������
int SearchTrainByNumber(depo* ftrains, int* famountoftr, int searchNumber)
{
    int i;
    int countsearch = 0;
    int foundIndex = -1;
    for (i = (*famountoftr - 1); i >= 0; i--)
    {
        if (ftrains[i].amount == searchNumber)
        {
            foundIndex = i;
            countsearch++;
            break;
        }
    }
    return foundIndex;
}

// ������ �������� �� ������ ������ � ������������ ������� ��������
void PrintSearchTrain(depo* ftrains, const int famountoftr, int foundIndex)
{

    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| � ������ |          ����� �����������          |          ����� ����������           | ����� �������� | ���������� ��������� ���� |\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------- \n");
    printf("| %-8d | %35s | %35s | %14s | %-25d |\n",
        ftrains[foundIndex].amount, ftrains[foundIndex].departure, ftrains[foundIndex].destination, ftrains[foundIndex].departure_time, ftrains[foundIndex].number_of_seats_available);
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n\n");
}

// �������� �������� �� ������ ������ � ������������ ������� ��������
void DeleteTrainByNumber(depo* ftrains, int* famountoftr)
{
    int i, j;
    int countdel = 0;
    int deleteNumber;

    //����� ���������� ������
    deleteNumber = InputNumber(7, MAX_NUMBER_TRAIN);

    for (i = 0; i < *famountoftr; i++)
    {
        if (ftrains[i].amount == deleteNumber)
        {
            countdel++;
            if (*famountoftr != 1)
            {
                for (j = i + 1; j < *famountoftr; j++)
                {
                    ftrains[j - 1].amount = ftrains[j].amount;
                    strcpy_s(ftrains[j - 1].departure, ftrains[j].departure);
                    strcpy_s(ftrains[j - 1].destination, ftrains[j].destination);
                    strcpy_s(ftrains[j - 1].departure_time, ftrains[j].departure_time);
                    ftrains[j - 1].number_of_seats_available = ftrains[j].number_of_seats_available;
                }
            }
        }
    }
    if (countdel == 0)
    {
        printf("����� � �������� ������� �� ������.\n");
    }
    else
    {
        printf("����� � �������� ������� ������� ������.\n");
    }
    *famountoftr = *famountoftr - countdel;
}

// ��������� �������� �� ������ ������ � ������������ ������� ��������
void EditTrain(depo* ftrains, const int famountoftr, int editIndex)
{
    char* ch1 = new char [MAX_LENGHT_STRING] {'\0'};

    printf("�������� ������ ��� ������ ����� %d : \n", ftrains[editIndex].amount);

    //ftrains[editIndex].amount = InputNumber(2, MAX_NUMBER_TRAIN);

    ch1 = InputString(1, MAX_LENGHT_STRING);
    strcpy_s(ftrains[editIndex].departure, ch1);

    ch1 = InputString(2, MAX_LENGHT_STRING);
    strcpy_s(ftrains[editIndex].destination, ch1);

    ch1 = InputTime(1, MAX_COUNT_TIME);
    strcpy_s(ftrains[editIndex].departure_time, strlen(ch1) + 1, ch1);

    ftrains[editIndex].number_of_seats_available = InputNumber(3, MAX_NUMBER_FREE_SEAT);

    printf("\n���������� � ������ ������� ��������\n");
}

// ���������� ������� �������� �� ����� ��������� ���� � �������(���������� �������� �� �����������)
void SortAscendingTrain(depo* ftrains, int* famountoftr)
{
    int j, k;
    depo tempTrain;

    for (j = 1; j < *famountoftr; j++)
    {
        tempTrain.amount = ftrains[j].amount;
        strcpy_s(tempTrain.departure, ftrains[j].departure);
        strcpy_s(tempTrain.destination, ftrains[j].destination);
        strcpy_s(tempTrain.departure_time, ftrains[j].departure_time);
        tempTrain.number_of_seats_available = ftrains[j].number_of_seats_available;

        k = j - 1;
        while (tempTrain.number_of_seats_available < ftrains[k].number_of_seats_available)
        {
            ftrains[k + 1].amount = ftrains[k].amount;
            strcpy_s(ftrains[k + 1].departure, ftrains[k].departure);
            strcpy_s(ftrains[k + 1].destination, ftrains[k].destination);
            strcpy_s(ftrains[k + 1].departure_time, ftrains[k].departure_time);
            ftrains[k + 1].number_of_seats_available = ftrains[k].number_of_seats_available;
            k--;
            if (k < 0)
            {
                break;
            }
        }

        ftrains[k + 1].amount = tempTrain.amount;
        strcpy_s(ftrains[k + 1].departure, tempTrain.departure);
        strcpy_s(ftrains[k + 1].destination, tempTrain.destination);
        strcpy_s(ftrains[k + 1].departure_time, tempTrain.departure_time);
        ftrains[k + 1].number_of_seats_available = tempTrain.number_of_seats_available;
    }
}

// ���������� ������� �������� �� ����� ��������� ���� � �������(���������� �������� �� ��������)
void SortDescendingTrain(depo* ftrains, int* famountoftr)
{
    int j, k;
    depo tempTrain;

    for (j = (*famountoftr - 2); j >= 0; j--)
    {
        tempTrain.amount = ftrains[j].amount;
        strcpy_s(tempTrain.departure, ftrains[j].departure);
        strcpy_s(tempTrain.destination, ftrains[j].destination);
        strcpy_s(tempTrain.departure_time, ftrains[j].departure_time);
        tempTrain.number_of_seats_available = ftrains[j].number_of_seats_available;

        k = j + 1;
        while (tempTrain.number_of_seats_available < ftrains[k].number_of_seats_available)
        {
            ftrains[k - 1].amount = ftrains[k].amount;
            strcpy_s(ftrains[k - 1].departure, ftrains[k].departure);
            strcpy_s(ftrains[k - 1].destination, ftrains[k].destination);
            strcpy_s(ftrains[k - 1].departure_time, ftrains[k].departure_time);
            ftrains[k - 1].number_of_seats_available = ftrains[k].number_of_seats_available;
            k++;
            if (k > *famountoftr - 1)
            {
                break;
            }
        }

        ftrains[k - 1].amount = tempTrain.amount;
        strcpy_s(ftrains[k - 1].departure, tempTrain.departure);
        strcpy_s(ftrains[k - 1].destination, tempTrain.destination);
        strcpy_s(ftrains[k - 1].departure_time, tempTrain.departure_time);
        ftrains[k - 1].number_of_seats_available = tempTrain.number_of_seats_available;
    }
}

//menu
void Menu()
{
    std::string temp_str, temp_str1;
    depo* trains;// ��������� �� ������ �������
    int amountoftr; // �������� ���������� �������

    printf("�������� ������ ������������ ������������� ����������� ������� ��������:\n");
    printf("1. ���� ������� ��������� ���������� �������� \n");
    printf("2. ���� �� ��������� ��������� � �������� ���������\n");
    printf("3. ������ � ������������� � ������������� ���������� ����\n");

    while (true)
    {
        printf("\n ��� �����: ");
        getline(std::cin, temp_str);

        if (temp_str == "1")
        {
            // 1. ������������ ������������� ����������� ������� �������� - ���� ������� ��������� ���������� ��������
            // ������ ���-�� ������� � �������� ��� ������ ����������� ���������� ������
            amountoftr = NumberOfTrains();
            trains = new depo[amountoftr + 1];
            // ��������� ���������� � ������� ������ � ����������
            FillTrains1(trains, amountoftr);
            break;
        }

        if (temp_str == "2")
        {
            // 2. ������������ ������������� ����������� ������� �������� - ���� �� ��������� ��������� � �������� ���������
            // �������� ����� ������, ����� �������� ���� ���������� ����������
            amountoftr = 1;
            trains = new depo[amountoftr + 1];
            FillTrains2(trains, &amountoftr);
            break;
        }

        if (temp_str == "3")
        {
            // 3. ������������ ������������� ����������� ������� �������� - ������ � ������������� � ������������� ���������� ����
            // ������ ���������� � �������, ���� ������������ �� �������� ����
            amountoftr = 1;
            trains = new depo[amountoftr + 1];
            // ��������� ���������� � ������� ������ � ���������� � ������� �� �����
            FillTrains3(trains, &amountoftr);
            //PrintTrains(trains, amountoftr);
            break;
        }

        if ((temp_str != "1") || (temp_str != "2") || (temp_str != "3"))
        {
            printf("������������ ����. ��������� ����.\n");
            //while (getchar() != '\n');
        }
    }

    int searchNumber;
    int foundTrain;
    int editNumber;
    int repeat = 0;

    //while (getchar() != '\n');
    do
    {
        while (true)
        {
            printf("\n�������� ������� ������ � ������������ ���������� �������� ��������:\n");
            printf("4. �������� ����������� ������������� ������� ��������\n");
            printf("5. ���������� ��� ������������� ������� �������� ������ �����������\n");
            printf("6. ����� � ����� �� ����� �������� � �������� ��������� ��������\n");
            printf("7. �������� �������� ������� �������� � �������� ��������� ��������\n");
            printf("8. ��������� �������� ������� �������� � �������� ��������� ��������\n");
            printf("9. ������������ ������� �������� �� ����� ��������� ���� � ������� (���������� �������� �� ��������)\n");
            printf("0. ����� �� ���������\n");

            printf("\n ��� �����: ");
            getline(std::cin, temp_str);

            if (temp_str == "4")
            {
                // 4. �������� ����������� ������������� ������� ��������
                // ������� �� ����� ������
                PrintTrains(trains, amountoftr);
                break;
            }

            if (temp_str == "5")
            {
                // 5. ���������� ��� ������������� ������� �������� ������ �����������
                // ��������� ����� ����� ������� �� ����� ���������
                AddNewTrain(trains, &amountoftr);
                PrintTrains(trains, amountoftr);
                break;
            }

            if (temp_str == "6")
            {
                // 6. ����� � ����� �� ����� �������� � �������� ��������� ��������
                // ���� ����� ������ � ������� �� ����� ���������
                //printf("\n������� ����� �������� ������: ");
                //scanf_s("%d", &searchNumber);
                searchNumber = InputNumber(6, MAX_NUMBER_TRAIN);
                foundTrain = SearchTrainByNumber(trains, &amountoftr, searchNumber);
                if (foundTrain != -1)
                {
                    printf("����� � �������� ������� ������� ������.\n");
                    PrintSearchTrain(trains, amountoftr, foundTrain);
                }
                else
                {
                    printf("����� � �������� ������� �� ������.\n");
                }

                break;
            }

            if (temp_str == "7")
            {
                // 7. �������� �������� ������� �������� � �������� ��������� ��������
                // ������� ����� � �������� ������� � ������� �� ����� ���������
                DeleteTrainByNumber(trains, &amountoftr);
                PrintTrains(trains, amountoftr);
                break;
            }

            if (temp_str == "8")
            {
                // 8. ��������� �������� ������� �������� � �������� ��������� ��������
                // ����������� ����� � ������� �� ����� ���������
                //printf("\n������� ����� �������������� ������: ");
                //scanf_s("%d", &editNumber);
                editNumber = InputNumber(8, MAX_NUMBER_TRAIN);
                foundTrain = SearchTrainByNumber(trains, &amountoftr, editNumber);
                if (foundTrain != -1)
                {
                    EditTrain(trains, amountoftr, foundTrain);
                }
                else
                {
                    printf("����� � �������� ������� �� ������.\n");
                }
                PrintTrains(trains, amountoftr);
                break;
            }

            if (temp_str == "9")
            {
                // 9. ������������ ������� �������� �� ����� ��������� ���� � ������� (���������� �������� �� ��������)
                SortDescendingTrain(trains, &amountoftr);
                PrintTrains(trains, amountoftr);
                break;
            }

            if (temp_str == "0")
            {
                // 0. ����� �� ���������
                printf("��������� ��������� ���� ������\n");
                while (getchar() != '\n');
                repeat = 0;
                break;
            }
            if ((temp_str != "4") || (temp_str != "5") || (temp_str != "6") || (temp_str != "7") || (temp_str != "8") || (temp_str != "9") || (temp_str != "0"))
            {
                printf("������������ ����. ��������� ����.\n");
                //while (getchar() != '\n');
            }
        }

        if (temp_str != "0")
        {
            printf("\n������ ���������� ���� ������? ");
            repeat = 1;
        }

    } while (repeat == 1);

    // ������� ������ ��-��� ������� �������
    delete[] trains;
}

