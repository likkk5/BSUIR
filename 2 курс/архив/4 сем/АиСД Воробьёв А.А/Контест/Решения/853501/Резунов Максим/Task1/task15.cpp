#include <iostream>
using namespace std;

int64_t max(int64_t * nums, int n)
{
	int64_t res = nums[0];
	for (int i = 0; i < n; i++)
		if (res < nums[i])
			res = nums[i];
	return res;
}

int64_t min(int64_t * nums, int n)
{
	int64_t res = nums[0];
	for (int i = 0; i < n; i++)
		if (res > nums[i])
			res = nums[i];
	return res;
}

int64_t sumUps(int64_t *nums, int n)
{
	int64_t maximum = max(nums, n);
	int64_t sum = 0;
	for (int64_t *last = nums, *now = nums + 1, i = 1; i < n; i++, now++, last++)
		if (*last < *now)
			sum += *now - *last;
	sum += maximum - nums[n - 1];
	return sum;
}

int main15()
{
	int n;
	cin >> n;
	int64_t *nums = new int64_t[n];
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	cout << sumUps(nums, n);
	return 0;
}