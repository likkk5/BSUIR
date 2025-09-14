#include <iostream>
#include <string.h>
#include <string>
using namespace std;

char max(char *s, int n)
{
	char res = s[0];
	for (int i = 0; i < n; i++)
		if (res < s[i])
			res = s[i];
	return res;
}

void sortUp(char *s, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (s[j] > s[j + 1])
			{
				char temp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = temp;
			}
}

bool isUpSorted(char *s, int n)
{
	for (int i = 1; i < n; i++)
		if (s[i - 1] > s[i])
			return false;
	return true;
}

bool isDownSorted(char *s, int n)
{
	for (int i = 1; i < n; i++)
		if (s[i - 1] < s[i])
			return false;
	return true;
}

int findMinMaxNum(int num, char *s, int n)
{
	if (!isDownSorted(s, n))
	{
		int k = n - 2;
		for (; k > 0; k--)
			if (s[k] < s[k + 1])
				break;

		char min = s[k + 1];
		int l = k + 1;
		for (int i = l; i < n; i++)
			if (min > s[i] && s[i] > s[k])
			{
				min = s[i];
				l = i;
			}

		s[l] = s[k];
		s[k] = min;

		sortUp(s + k + 1, n - k - 1);
		return stoi(s);
	}
	else
		return -1;
}

int main16()
{
	int snum;
	cin >> snum;
	string s = to_string(snum);

	int n = s.length();
	char* res = new char[n + 1]{ '\0' };
	for (int i = 0; i < n; i++)
		res[i] = s[i];
	char maxChar = max(res, n);

	if (n == 1)
		cout << -1;
	else
	{
		int num = stoi(string(s));	
		cout << findMinMaxNum(num, res, n);
	}
	return 0;
}