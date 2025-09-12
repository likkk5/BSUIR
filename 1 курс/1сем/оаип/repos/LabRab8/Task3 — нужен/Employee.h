#pragma once
#define MAX_LENGHT_STRING 31 // ������������ ����� ������ ��� ���
#define MAX_LENGHT_PERSONAL_NUMBER 5 // ������������ ��������� ����� (�������������� ��� - ����)
#define MAX_HOURS_MOUNTH 200 // ������������ ���������� ������������ ����� � �����
#define MAX_HOURLY_RATE 100.00 // ������������ ��������� �����

class Employee
{
public:
    char last_name[MAX_LENGHT_STRING];  // ������� ����������
    char first_name[MAX_LENGHT_STRING]; // �������� ����������
    char midle_name[MAX_LENGHT_STRING]; // ��� ����������
    char personal_number[MAX_LENGHT_PERSONAL_NUMBER]; // ��������� ����� (�������������� ��� - ����)
    int hours;                                  // ���������� ������������ ����� � �����
    double hourly_rate;                         // ��������� �����
    union {
        float salary;
    };
};

