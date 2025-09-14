#include <iostream>
#include <list>
using namespace std;

void getTwos(const list<int> &numbers, int &pos_max, int &pre_pos_max)
{
	if (numbers.size() > 1)
	{
		auto iter = --numbers.cend();
		pos_max = *iter;
		iter--;
		pre_pos_max = *iter;
	}
	else
	{
		pos_max = -1;
		pre_pos_max = -1;
	}
}

int main2()
{
	int n;
	cin >> n;
	list<int> poss;
	list<int> negs;
	for (int i = 0; i < n; i++)
	{
		int value;
		cin >> value;
		if (value >= 0)
			poss.push_back(value);
		else
			negs.push_back(-value);
	}
	poss.sort();
	negs.sort();

	int pos_max = -1, pre_pos_max = -1;
	getTwos(poss, pos_max, pre_pos_max);

	int neg_max = -1, pre_neg_max = -1;
	getTwos(negs, neg_max, pre_neg_max);

	if (pos_max != -1 && neg_max == -1)
		cout << int64_t(pos_max) * int64_t(pre_pos_max);
	else if (pos_max == -1 && neg_max != -1)
		cout << int64_t(neg_max) * int64_t(pre_neg_max);
	else if (pos_max != -1 && neg_max != -1)
	{
		int64_t pos = int64_t(pos_max) * int64_t(pre_pos_max);
		int64_t neg = int64_t(neg_max) * int64_t(pre_neg_max);
		cout << (pos > neg ? pos : neg);
	}
	else
	{
		if (poss.size() == 1 && negs.size() == 1)
		{
			cout << -int64_t(poss.front()) * int64_t(negs.front());
		}
	}
	return 0;
}