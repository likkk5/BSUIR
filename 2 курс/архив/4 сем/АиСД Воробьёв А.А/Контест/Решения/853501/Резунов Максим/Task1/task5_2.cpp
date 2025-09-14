#include <iostream>
#include <vector>
using namespace std;

void SetDistance(vector<pair<int, int>>* graph, int n, int minNode, int64_t* nodeValue);

int main5_2()
{
	// кол-во вершин
	int n;
	// кол-во ребер
	int m;
	// Индекс первого / индекс второго/ вес ребра
	int data[3];
	// Откуда и куда
	int begin, end;

	cin >> n >> m;

	// Граф
	vector<pair<int, int>>* graph = new vector<pair<int, int>>[n];

	for (int i = 0; i < m; i++)
	{
		cin >> data[0] >> data[1] >> data[2];
		data[0]--;
		data[1]--;

		// Заполняем граф
		graph[data[0]].push_back({ data[1], data[2] });
		graph[data[1]].push_back({ data[0], data[2] });
	}

	cin >> begin >> end;
	begin--;
	end--;

	// Массив с весами вершин
	int64_t* nodeValue = new int64_t[n];
	// Массив посещений вершин
	bool* visited = new bool[n] {false};
	// Изначально на всех вершинах бесконечность
	for (int i = 0; i < n; i++)
		nodeValue[i] = INT64_MAX;
	nodeValue[begin] = 0;

	for (int i = 0; i < n; i++)
	{
		int minNode = INT32_MIN;
		// Поиск непосещенной вершины
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

// Проходим по всем возможным путям из вершины и сравниваем пути
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