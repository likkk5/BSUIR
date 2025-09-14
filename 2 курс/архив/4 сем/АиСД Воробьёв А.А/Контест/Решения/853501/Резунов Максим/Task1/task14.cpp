#include <iostream>
#include <vector>
using namespace std;

void GoThrough(int index, bool* isVisited, vector<int>* graph)
{
	// ��������������� ���� ���������
	isVisited[index] = true;
	// �������� �� ���� �������
	for (auto item : graph[index])
		// ���� �����-�� ����� �� �������
		if (!isVisited[item])
			// ��������� �� �� �������� � ��� ����
			GoThrough(item, isVisited, graph);
}

int Task1(int count, bool* isVisited, vector<int>* graph)
{
	int result = 0;
	// �������� �� ���� ��������
	for (int i = 0; i < count; i++)
		// ���� ������� �� ����������
		if (!isVisited[i])
		{
			// ������������� ��������� � ��������� ��� �����
			GoThrough(i, isVisited, graph);
			result++;
		}
	return result;
}

int Task13(int result, int n, int m)
{
	if (m - n + 1 >= 0 && result == 1)
		return m - n + 1;
	else
		return -1;
}

int main14()
{
	// [n][m]
	int n, m;
	cin >> n >> m;
	// ������ ��� �������� ��������� ������
	bool* isVisited = new bool[n] {false};
	// ����
	vector<int>* graph = new vector<int>[n];

	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		// ����������� � �������
		a--;
		b--;
		// ��������� ���������� � ��������
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	// �����
	cout << Task13((Task1(n, isVisited, graph)), n, m);	
	return 0;
}