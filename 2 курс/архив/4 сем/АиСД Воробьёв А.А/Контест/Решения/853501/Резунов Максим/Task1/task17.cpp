#include <iostream>
#include <string.h>
#include <string>
using namespace std;

bool contain(char** strs, int n, const char *str)
{
	for (int i = 0; i < n; i++)
		if (strcmp(str, strs[i]) == 0)
			return true;
	return false;
}

int main17()
{
	int n;
	cin >> n;
	char** strs = new char*[n];
	for (int i = 0; i < n; i++)
	{
		strs[i] = new char[11]{ '\0' };
		cin >> strs[i];
	}

	if ((contain(strs, n, "1021") && contain(strs, n, "1031") && contain(strs, n, "1033")) ||
		(contain(strs, n, "1065023") && contain(strs, n, "1021")) ||
		(contain(strs, n, "1054693") && contain(strs, n, "1031")) ||
		(contain(strs, n, "1052651") && contain(strs, n, "1033")) ||
		(contain(strs, n, "1087388483")))
		cout << "YES";
	else
		cout << "NO";
	return 0;
}