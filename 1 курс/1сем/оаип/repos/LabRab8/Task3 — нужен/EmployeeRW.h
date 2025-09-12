#pragma once
#include "Employee.h"

class EmployeeRW
{
public:
	Employee* readAll(int &amount);
	void save(Employee* employee);
	void add(Employee employee);
	void edit(Employee employee, int position);  //�������� ���� ������
	Employee* remove(Employee* employees, int& count, int position); //��� ����� ���� ������, ������ ��� �� ����� ������� ���� ���� ������ ���������
};

