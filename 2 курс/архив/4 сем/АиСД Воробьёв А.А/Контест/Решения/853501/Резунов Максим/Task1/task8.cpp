#include <iostream>
using namespace std;
int main8()
{
	int year;
	cin >> year;
	if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
		cout << "YES";
	else
		cout << "NO";
	return 0;
}