#pragma once

#define MAX_LENGHT_STRING 31 // максимальна€ длина строки дл€ ‘»ќ
#define MAX_LENGHT_PERSONAL_NUMBER 5 // максимальный табельный номер (четырехзначный код - ’’’’)
#define MAX_HOURS_MOUNTH 200 // максимальное количество отработанных часов в мес€ц
#define MAX_HOURLY_RATE 100.00 // максимальный почасовой тариф

union ZP {
    float smallSalary;
    double bigSalary;
} ;

typedef struct Employee //объ€вл€ем шаблон структуры
{
    char last_name[MAX_LENGHT_STRING]{ '\0' };  // фамили€ сотрудника
    char first_name[MAX_LENGHT_STRING]{ '\0' }; // отчество сотрудника
    char midle_name[MAX_LENGHT_STRING]{ '\0' }; // им€ сотрудника
    char personal_number[MAX_LENGHT_PERSONAL_NUMBER]{ '\0' }; // табельный номер (четырехзначный код - ’’’’)
    int hours;                                  // количество отработанных часов в мес€ц
    double hourly_rate;                         // почасовой тариф
    ZP salary;
};