#include <iostream>
#include <string.h>
using namespace std;

int main12()
{
	char input[20];
	cin >> input;
	int length = strlen(input);
	if (input[length - 1] == '0')
		cout << "NO";
	else
		cout << input[length - 1];
	return 0;
}