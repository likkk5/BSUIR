#pragma once

#define MAX_LENGHT_STRING 31 // ������������ ����� ������ ��� ���
#define MAX_LENGHT_PERSONAL_NUMBER 5 // ������������ ��������� ����� (�������������� ��� - ����)
#define MAX_HOURS_MOUNTH 200 // ������������ ���������� ������������ ����� � �����
#define MAX_HOURLY_RATE 100.00 // ������������ ��������� �����

union ZP {
    float smallSalary;
    double bigSalary;
} ;

typedef struct Employee //��������� ������ ���������
{
    char last_name[MAX_LENGHT_STRING]{ '\0' };  // ������� ����������
    char first_name[MAX_LENGHT_STRING]{ '\0' }; // �������� ����������
    char midle_name[MAX_LENGHT_STRING]{ '\0' }; // ��� ����������
    char personal_number[MAX_LENGHT_PERSONAL_NUMBER]{ '\0' }; // ��������� ����� (�������������� ��� - ����)
    int hours;                                  // ���������� ������������ ����� � �����
    double hourly_rate;                         // ��������� �����
    ZP salary;
};