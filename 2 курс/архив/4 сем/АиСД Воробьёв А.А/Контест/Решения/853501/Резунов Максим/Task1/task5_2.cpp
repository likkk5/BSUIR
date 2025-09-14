#include <iostream>
#include <vector>
using namespace std;

void SetDistance(vector<pair<int, int>>* graph, int n, int minNode, int64_t* nodeValue);

int main5_2()
{
	// ���-�� ������
	int n;
	// ���-�� �����
	int m;
	// ������ ������� / ������ �������/ ��� �����
	int data[3];
	// ������ � ����
	int begin, end;

	cin >> n >> m;

	// ����
	vector<pair<int, int>>* graph = new vector<pair<int, int>>[n];

	for (int i = 0; i < m; i++)
	{
		cin >> data[0] >> data[1] >> data[2];
		data[0]--;
		data[1]--;

		// ��������� ����
		graph[data[0]].push_back({ data[1], data[2] });
		graph[data[1]].push_back({ data[0], data[2] });
	}

	cin >> begin >> end;
	begin--;
	end--;

	// ������ � ������ ������
	int64_t* nodeValue = new int64_t[n];
	// ������ ��������� ������
	bool* visited = new bool[n] {false};
	// ���������� �� ���� �������� �������������
	for (int i = 0; i < n; i++)
		nodeValue[i] = INT64_MAX;
	nodeValue[begin] = 0;

	for (int i = 0; i < n; i++)
	{
		int minNode = INT32_MIN;
		// ����� ������������ �������
		for (int j = 0; j < n; j++)
		{
			if (visited[j] == false)
			{
				if (minNode == INT32_MIN)
					minNode = j;
				else if (nodeValue[minNode] > nodeValue[j])
					minNode = j;
			}
		}
		if (nodeValue[minNode] == INT32_MAX)
			break;
		else
		{
			visited[minNode] = true;
			SetDistance(graph, n, minNode, nodeValue);
		}
	}

	cout << nodeValue[end];
	return 0;
}

// �������� �� ���� ��������� ����� �� ������� � ���������� ����
void SetDistance(vector<pair<int, int>>* graph, int n, int minNode, int64_t* nodeValue)
{
	for (int j = 0; j < graph[minNode].size(); j++)
	{
		int64_t neighbour = graph[minNode][j].first;
		int64_t weight = graph[minNode][j].second;
		if (nodeValue[minNode] + weight < nodeValue[neighbour])
			nodeValue[neighbour] = nodeValue[minNode] + weight;
	}
}