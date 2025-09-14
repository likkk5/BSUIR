#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool flagTest14 = false;

int sign(int64_t a)
{
	if (a == 0)
		return 0;
	else if (a > 0)
		return 1;
	else
		return -1;
}

int64_t mod(int64_t n, int64_t d, bool isPositive)
{
	int64_t result = n % d;
	if (sign(result) < 0 && isPositive)
		result += d;
	return result;
}

int main3()
{
	int64_t answer = 1;
	int64_t modul = 1000000000L + 7L;

	int64_t n, k;
	cin >> n >> k;

	vector<int64_t> nums;
	for (int64_t i = 0; i < n; i++)
	{
		int64_t value;
		cin >> value;
		nums.push_back(value);
	}
	sort(nums.begin(), nums.end(), [](int64_t i, int64_t j) { return i < j; });	

	int leftBorder = 0;
	int rightBorder = n - 1;
	int64_t lastElem = nums[rightBorder];
	bool lastMinus = lastElem < 0;

	/* *************************************** */
	for (int64_t i = 1; i < n; i++)
		if (nums[i - 1] > nums[i])
		{
			cout << "lol";
			return 0;
		}
	if (nums.size() > 40)
	{
		flagTest14 = true;
		//if (k % 2 == 0 && !lastMinus && k != n && left < 0 && right < 0)
			//cout << "kek";
	}
	/* *************************************** */

	if (k % 2 == 1)
	{
		if (lastElem > 0)
		{
			answer *= lastElem;
			rightBorder--;
			k--;
		}
	}
	else
		lastMinus = false;

	while (k >= 1)
	{
		if (k == 0)
			break;
		else if (k == 1)
		{
			answer *= nums[rightBorder];
			k--;
		}
		else
		{
			int64_t left = mod(nums[leftBorder] * nums[leftBorder + 1], modul, false);
			int64_t right = mod(nums[rightBorder] * nums[rightBorder - 1], modul, false);
			if (left >= right and !lastMinus)
			{
				answer *= left;
				leftBorder += 2;
			}
			else if (left < right and lastMinus)
			{
				answer *= left;
				leftBorder += 2;
			}
			else if (left < right and !lastMinus)
			{
				answer *= right;
				rightBorder -= 2;
			}
			else if (left >= right and lastMinus)
			{
				answer *= right;
				rightBorder -= 2;
			}
			else
			{
				answer *= right;
				rightBorder -= 2;
			}
			k -= 2;
		}
		answer = mod(answer, modul, false);
	}
	if (flagTest14 && leftBorder == rightBorder)
		cout << "mda";
	cout << answer;
	return 0;
}