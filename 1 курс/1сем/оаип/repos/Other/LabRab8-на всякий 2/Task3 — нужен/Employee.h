#pragma once
#define MAX_LENGHT_STRING 31 // максимальная длина строки для ФИО
#define MAX_LENGHT_PERSONAL_NUMBER 5 // максимальный табельный номер (четырехзначный код - ХХХХ)
#define MAX_HOURS_MOUNTH 200 // максимальное количество отработанных часов в месяц
#define MAX_HOURLY_RATE 100.00 // максимальный почасовой тариф

class Employee
{
public:
    char last_name[MAX_LENGHT_STRING];  // фамилия сотрудника
    char first_name[MAX_LENGHT_STRING]; // отчество сотрудника
    char midle_name[MAX_LENGHT_STRING]; // имя сотрудника
    char personal_number[MAX_LENGHT_PERSONAL_NUMBER]; // табельный номер (четырехзначный код - ХХХХ)
    int hours;                                  // количество отработанных часов в месяц
    double hourly_rate;                         // почасовой тариф
    union {
        float salary;
    };
};

