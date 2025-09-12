#pragma once

#define MAX_COUNT_TRAIN 100 // ������������ ���������� ������� � ������������ ������� ��������
#define MAX_NUMBER_TRAIN 999999 // ������������ ����� ������
#define MAX_LENGHT_STRING 31 // ������������ ����� ������ ��� ����� �����������/����������
#define MAX_COUNT_TIME 6 // ������������ ���������� ������� ��� ������� ����������� (XX::XX)
#define MAX_NUMBER_FREE_SEAT 999 // ������������ ����� ��������� ���� � ������

typedef struct depo //��������� ������ ���������
{
    int amount; //����� ������
    char departure[MAX_LENGHT_STRING]{ '\0' };  //����� �����������
    char destination[MAX_LENGHT_STRING]{ '\0' };  //����� ���������� 
    char departure_time[MAX_COUNT_TIME]{ '\0' }; //����� �����������
    int	number_of_seats_available; //����� ��������� ����

};

