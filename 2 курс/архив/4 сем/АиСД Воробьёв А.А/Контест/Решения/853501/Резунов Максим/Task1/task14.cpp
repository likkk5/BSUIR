#include <iostream>
#include <vector>
using namespace std;

void GoThrough(int index, bool* isVisited, vector<int>* graph)
{
	// Устанавливается флаг посещения
	isVisited[index] = true;
	// Проходим по всем соседям
	for (auto item : graph[index])
		// Если какой-то сосед не посещен
		if (!isVisited[item])
			// Выполняем те же действия и для него
			GoThrough(item, isVisited, graph);
}

int Task1(int count, bool* isVisited, vector<int>* graph)
{
	int result = 0;
	// Проходим по всем вершинам
	for (int i = 0; i < count; i++)
		// Если вершина не посещалась
		if (!isVisited[i])
		{
			// Устанавливаем посещение и проверяем все связи
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
	// Массив для проверки посещения вершин
	bool* isVisited = new bool[n] {false};
	// Граф
	vector<int>* graph = new vector<int>[n];

	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		// редактируем в индексы
		a--;
		b--;
		// Заполняем информацию о вершинах
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	// Ответ
	cout << Task13((Task1(n, isVisited, graph)), n, m);	
	return 0;
}