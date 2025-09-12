#pragma once
#include "Employee.h"

class EmployeeRW
{
public:
	Employee* readAll(int &amount);
	void save(Employee* employee);
	void add(Employee employee);
	void edit(Employee employee, int position);  //заменяем одну строку
	Employee* remove(Employee* employees, int& count, int position); //нам нужен весь массив, потому что не можем удалить лишь одну строку нормально
};

