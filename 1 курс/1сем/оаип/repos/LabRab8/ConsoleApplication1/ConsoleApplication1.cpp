#include <stdio.h>		// для ввода, вывода (scanf, printf)
#include <conio.h>		// для задержки программы (getch)
#include <string.h>		// для работы со строковыми функциями

#define MAX_LENGHT_STRING 100	// максимальная длина строковых данных
#define MAX_COUNT_SCHOOL 20		// максимальное кол-во школ для обработки

//-------------------------------------------------------------------------
// структура, описывающая школу
//-------------------------------------------------------------------------
typedef struct
{
    int number; // номер школы
    char surnameDirector[MAX_LENGHT_STRING]; // фамилия директора
    char regionCity[MAX_LENGHT_STRING]; // район города
    int countClasses; // количество классов
    int countPupils; // количество учеников
} TSchool;
//-------------------------------------------------------------------------
// ввод количества школ для обработки
//-------------------------------------------------------------------------
int InputCountSchools(void)
{
    int count;
    do
    {
        printf("Введите количество школ для обработки из отрезка [1 .. %d]: ", MAX_COUNT_SCHOOL);
        scanf("%d", &count);
    } while ((count < 1) || (count > MAX_COUNT_SCHOOL));
    return count;
}
//-------------------------------------------------------------------------
// добавление новой школы перед школой с заданным номером
//-------------------------------------------------------------------------
void AddSchool(TSchool* pschools, int* pcount)
{
    int targetNumberSchool; // хранит школу с заданным номером (перед этой школой будет попытка добавление новой школы)
    int insert;
    int i;

    printf("\nВведите № школы, перед которой планируется добавить новую школу: ");
    scanf("%d", &targetNumberSchool);

    // прежде, чем пытаться добавить новую школу, нужно убедиться, что школа с заданным номером существует и вставка физически возможна
    for (insert = 0; insert < *pcount; insert++)
        if ((pschools + insert)->number == targetNumberSchool)
            break;

    if (insert >= *pcount)
    {
        printf("Школы с введенным номером не существует! Добавление новой школы невозможно!\n");
        return;
    }
    else
    {
        // происходит смещение всех школ, чтобы освободить место для новой школы
        for (i = (*pcount - 1); i >= insert; i--)
        {
            pschools[i + 1].number = pschools[i].number;
            strcpy(pschools[i + 1].surnameDirector, pschools[i].surnameDirector);
            strcpy(pschools[i + 1].regionCity, pschools[i].regionCity);
            pschools[i + 1].countClasses = pschools[i].countClasses;
            pschools[i + 1].countPupils = pschools[i].countPupils;
        }
        printf("\nВведите номер добавляемой школы: ");
        scanf("%d", &pschools[insert].number);
        printf("Введите фамилию директора добавляемой школы: ");
        scanf("%s", pschools[insert].surnameDirector);
        printf("Введите район города добавляемой школы: ");
        scanf("%s", pschools[insert].regionCity);
        printf("Введите количество классов добавляемой школы: ");
        scanf("%d", &pschools[insert].countClasses);
        printf("Введите количество учеников добавляемой школы: ");
        scanf("%d", &pschools[insert].countPupils);
        printf("\nИнформация о новой школе успешно добавлена!\n");
        (*pcount)++;
        getch();
    }
}
//-------------------------------------------------------------------------
// заполнение информации о школах вводом с клавиатуры
//-------------------------------------------------------------------------
void FillSchools(TSchool* pschools, const int pcount)
{
    int i;
    printf("\nВам предстоит ввести с клавиатуры информации о %d школах.\n", pcount);
    for (i = 1; i <= pcount; i++, pschools++)
    {
        printf("\n\nВвод информации по %d-й школе.\n", i);
        printf("\tВведите номер школы: ");
        scanf("%d", &pschools->number);
        printf("\tВведите фамилию директора школы: ");
        scanf("%s", pschools->surnameDirector);
        printf("\tВведите района города, где располагается школа: ");
        scanf("%s", pschools->regionCity);
        printf("\tВведите количество классов школы: ");
        scanf("%d", &pschools->countClasses);
        printf("\tВведите количество учеников, обучающихся в школе: ");
        scanf("%d", &pschools->countPupils);
    }
}
//-------------------------------------------------------------------------
// вывод информации о школах на экран в табличном виде
//-------------------------------------------------------------------------
void PrintSchools(TSchool* pschools, const int pcount)
{
    int i;
    if (pcount == 0)
    {
        printf("\nНет ни одной школы! Печать информации о школах невозможна.\n");
        return;
    }
    //  ╚╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝	символы псевдографики для построения красивого каркаса таблицы при выводе
    printf("\nИнформация о %d школах имеет вид:\n", pcount);
    printf("╔═════════╦═══════════════════╦══════════════╦════════════════════╦═════════════════════╗\n");
    printf("║ № школы ║ Фамилия директора ║ Район города ║ Количество классов ║ Количество учеников ║\n");
    printf("╠═════════╬═══════════════════╬══════════════╬════════════════════╬═════════════════════╣\n");
    for (i = 1; i <= pcount; i++, pschools++)
        printf("║ %-7d ║ %17s ║ %12s ║ %-18d ║ %-19d ║\n",
            pschools->number, pschools->surnameDirector, pschools->regionCity,
            pschools->countClasses, pschools->countPupils);
    printf("╚═════════╩═══════════════════╩══════════════╩════════════════════╩═════════════════════╝\n\n");
}
//-------------------------------------------------------------------------
// удаление всех школ заданного региона
//-------------------------------------------------------------------------
void DeleteSchoolByRegion(TSchool* pschools, int* pcount)
{
    int i, j;
    int countDeletedSchool = 0;
    char deleteRegion[MAX_LENGHT_STRING];
    printf("\nВведите район города для удаления всех школ, принадлежащих этому району: ");
    scanf("%s", deleteRegion);
    for (i = (*pcount - 1); i >= 0; i--)
    {
        if (strcmp(pschools[i].regionCity, deleteRegion) == 0)
        {
            countDeletedSchool++;
            for (j = i + 1; j < *pcount; j++)
            {
                pschools[j - 1].number = pschools[j].number;
                strcpy(pschools[j - 1].surnameDirector, pschools[j].surnameDirector);
                strcpy(pschools[j - 1].regionCity, pschools[j].regionCity);
                pschools[j - 1].countClasses = pschools[j].countClasses;
                pschools[j - 1].countPupils = pschools[j].countPupils;
            }
        }
    }
    *pcount = *pcount - countDeletedSchool;
    printf("Все школы заданного района успешно удалены!\n");
}
//-------------------------------------------------------------------------
// главная функция программы (точка входа)
//-------------------------------------------------------------------------
int main(void)
{
    TSchool* schools; // указатель на массив школ
    int countSchool; // активное количество школ

    // вводим кол-во школ и выделяем под школы необходимое количество памяти
    countSchool = InputCountSchools();
    schools = new TSchool[countSchool + 1];

    // заполняем информацию о школах вводом с клавиатуры и выводим на экран
    FillSchools(schools, countSchool);
    PrintSchools(schools, countSchool);

    // добавляем новую школу перед заданной и выводим на экран результат
    AddSchool(schools, &countSchool);
    PrintSchools(schools, countSchool);

    // удаляем все школы заданного региона и выводим на экран результат
    DeleteSchoolByRegion(schools, &countSchool);
    PrintSchools(schools, countSchool);

    // очищаем память из-под массива школ
    delete[] schools;

    printf("\nДля завершения работы программы нажмите клавишу ENTER...");
    getch(); // задержка работы программы, чтобы просмотреть результат
    return 0; // завершение работы программы и передача управления в ОС
}