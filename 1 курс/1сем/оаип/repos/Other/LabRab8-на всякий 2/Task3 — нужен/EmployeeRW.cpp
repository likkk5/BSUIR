#include "EmployeeRW.h"
#include <iostream>     
#include <fstream>   
#include <windows.h>
#include <string>
#include <string.h>
#include "Employee.h"

Employee* EmployeeRW::readAll(int &amount)
{
    std::ifstream readStream("employee.data", std::ifstream::ate | std::ifstream::binary);
    int count = ((int)readStream.tellg() / ((int)sizeof(Employee))), i = 0;
    readStream.close();
    readStream.open("employee.data", std::ifstream::binary);

    Employee* employees = new Employee[count + 1];

    Employee employee;

    if (!readStream)
    {
        printf("Не удалось открыть файл для чтения. Файл не создан.");
    }

    while (readStream.read((char*)&employee, (int)sizeof(Employee))) {
        employees[i] = employee;
        i++; amount++;
    }

    readStream.close();

    return employees;
}

void EmployeeRW::save(Employee* employees)
{
    std::ofstream writeStream("employee.data", std::ofstream::binary);

    for (int i = 0; i < (sizeof(employees) / sizeof(Employee)); i++)
    {
        writeStream.write((char*)&employees[i], (int)sizeof(Employee));
    }

    writeStream.close();
}

void EmployeeRW::add(Employee employee)
{
    std::ofstream stream("employee.data", std::ofstream::binary | std::ofstream::app | std::ofstream::ate);
    stream.clear();
    stream.write((char*)&employee, sizeof(employee));
    stream.close();
}

void EmployeeRW::edit(Employee employee, int position)
{
    std::ofstream stream("employee.data", std::ofstream::binary | std::ofstream::in);
    stream.clear();
    stream.seekp(sizeof(employee) * position);
    stream.write((char*)&employee, sizeof(Employee));
    stream.close();
}

Employee* EmployeeRW::remove(Employee* employees, int &count, int position)
{
    position--;
    Employee employee;
    Employee* newEmployees = new Employee[count];
    int length = 0;

    for (int i = 0; i < count; i++) {
        if (i != position) {
            newEmployees[length] = employees[i];
            length++;
        }
    }
    count--;

    std::ofstream writeStream("employee.data", std::ofstream::binary | std::ofstream::trunc);

    if (!writeStream)
    {
        printf("Не удалось открыть файл для чтения. Файл не создан.");
    }

    for (int i = 0; i < count; i++)
    {
        writeStream.write((char*)&newEmployees[i], (int)sizeof(Employee));
    }

    writeStream.close();

    return newEmployees;
}
