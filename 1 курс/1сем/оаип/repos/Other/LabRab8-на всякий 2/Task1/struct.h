#pragma once

#define MAX_COUNT_TRAIN 100 // максимальное количество поездов в динамическом массиве структур
#define MAX_NUMBER_TRAIN 999999 // максимальный номер поезда
#define MAX_LENGHT_STRING 31 // максимальная длина строки для пункт отправления/назначения
#define MAX_COUNT_TIME 6 // максимальная количество сиволов для времени отправления (XX::XX)
#define MAX_NUMBER_FREE_SEAT 999 // максимальное число свободных мест в поезде

typedef struct depo //объявляем шаблон структуры
{
    int amount; //номер поезда
    char departure[MAX_LENGHT_STRING]{ '\0' };  //пункт отправления
    char destination[MAX_LENGHT_STRING]{ '\0' };  //пункт назначения 
    char departure_time[MAX_COUNT_TIME]{ '\0' }; //время отправления
    int	number_of_seats_available; //число свободных мест

};

