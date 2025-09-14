#include <iostream>
#include <string.h>
using namespace std;

int main9() {
	char s_chars[1000000];
	cin >> s_chars;
	int q_num;
	cin >> q_num;
	int left, right;
	bool* changeCharInStr = new bool[strlen(s_chars)]{ false };
	bool change = false;
	for (int i = 0; i < q_num; i++) {
		cin >> left;
		cin >> right;
		if (left == right) {
			if (islower(s_chars[left]))
				s_chars[left] = toupper(s_chars[left]);
			else
				s_chars[left] = tolower(s_chars[left]);
			continue;
		}
		if (left > right) swap(left, right);
		left--;
		changeCharInStr[left] = !changeCharInStr[left];
		changeCharInStr[right] = !changeCharInStr[right];

	}
	for (int l = 0; l < strlen(s_chars); l++) {
		if (changeCharInStr[l] == true) change = !change;
		if (change)
			if (islower(s_chars[l]))
				s_chars[l] = toupper(s_chars[l]);
			else
				s_chars[l] = tolower(s_chars[l]);
	}
	cout << s_chars;
	return 0;
}