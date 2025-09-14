/*#include <iostream>
using namespace std;

typedef struct _MapNode
{
	_MapNode(int xi, int yi, bool isWall) :
		xi(xi), yi(yi), isWall(isWall), next(nullptr) {}
	int xi, yi;
	bool isWall;
	_MapNode *next;
} MapNode;

typedef struct _Map
{
	_Map() : list(nullptr) {}
	MapNode* list;
} Map;

int tNum;
int *n, *m;
int ***a;
bool ***isWall;
Map **maps;
int *maxs;
int *mins;
//map<int, vector<tuple<int, int, bool>>> *maps;

inline void addNode(Map *map, int key, int xi, int yi, bool isWall)
{
	MapNode* node = new MapNode(xi, yi, isWall);
	if (!map[key].list)
		map[key].list = node;
	else
	{
		auto iter = map[key].list;
		while (iter->next != nullptr)
			iter = iter->next;
		iter->next = node;
	}
}

inline void deleteNode(Map *map, int key, MapNode *node)
{
	auto iter = map[key].list;
	while (iter->next != nullptr || iter->next != node)
		iter = iter->next;
	if (iter->next == node)
	{
		iter->next = node->next;
		delete node;
	}
	else if (node == map[key].list)
	{ //удаляем начало списка
		map[key].list = map[key].list->next;
		delete node;
	}
}

inline void initFirst()
{
	cin >> tNum;
	n = new int[tNum];
	m = new int[tNum];
	a = new int**[tNum];
	isWall = new bool**[tNum];
	maps = new Map*[tNum];
	for (int i = 0; i < tNum; i++)
		maps[i] = new Map[10000];
	maxs = new int[tNum] {INT32_MIN};
	mins = new int[tNum] {INT32_MAX};
	//maps = new map<int, vector<tuple<int, int, bool>>>[tNum];
}

inline bool isborder(int i, int j, int n, int m)
{
	return (i == 0 || j == 0 || i == (n - 1) || j == (m - 1));
}

int getVolume(MapNode *node, Map *map, int value, int **a, bool** isWall)
{
	if (node->isWall)
		return 0;
	bool isWallRight = isWall[node->xi + 1][node->yi];
	bool isWallLeft	= isWall[node->xi - 1][node->yi];
	bool isWallUp = isWall[node->xi][node->yi + 1];
	bool isWallDown = isWall[node->xi][node->yi - 1];
	bool isWallAround = isWallRight ||
		isWallLeft ||
		isWallUp ||
		isWallDown;
	node->isWall = true;
	if (isWallAround)
	{
		int minWallAround = INT32_MAX;
		if (isWallRight)
			if (minWallAround > a[node->xi + 1][node->yi])
				minWallAround = a[node->xi + 1][node->yi];
		if (isWallLeft)
			if (minWallAround > a[node->xi - 1][node->yi])
				minWallAround = a[node->xi - 1][node->yi];
		if (isWallUp)
			if (minWallAround > a[node->xi][node->yi + 1])
				minWallAround = a[node->xi][node->yi + 1];
		if (isWallDown)
			if (minWallAround > a[node->xi][node->yi - 1])
				minWallAround = a[node->xi][node->yi - 1];
		if (value < minWallAround)
		{
			a[node->xi][node->yi] = minWallAround;
			return minWallAround - value;
		}
		else
			return 0;
	}
	else
	{
		int minAround = a[node->xi + 1][node->yi];
		if (minAround > a[node->xi - 1][node->yi])
			minAround = a[node->xi - 1][node->yi];
		if (minAround > a[node->xi][node->yi + 1])
			minAround = a[node->xi][node->yi + 1];
		if (minAround > a[node->xi][node->yi - 1])
			minAround = a[node->xi][node->yi - 1];

		a[node->xi][node->yi] = minAround;
		if (minAround != value)
		{
			addNode(map, minAround, node->xi, node->yi, false);
			deleteNode(map, value, node);
		}
		return minAround - value;
	}
}

inline int volume(int** a, bool **isWall, int n, int m, int minValue, int maxValue, Map *map)
{
	/*int **va = new int*[n - 2];
	for (int i = 0; i < n; i++)
		va[i] = new int[m - 2]{ -1 };*/
/*	int volume = 0;
	for (int value = minValue; value < maxValue; value++)
	{
		auto iter = map[value].list;
		while (iter != nullptr)
		{
			volume += getVolume(iter, map, value, a, isWall);
			iter = iter->next;
		}
	}
	return volume;
}

int main_20_1()
{	
	initFirst();
	for (int t = 0; t < tNum; t++)
	{
		cin >> n[t] >> m[t];
		a[t] = new int*[n[t]];
		isWall[t] = new bool*[n[t]];
		for (int i = 0; i < n[t]; i++)
		{
			a[t][i] = new int[m[t]];
			isWall[t][i] = new bool[m[t]];
		}

		for (int i = 0; i < n[t]; i++)
			for (int j = 0; j < m[t]; j++)
			{
				cin >> a[t][i][j];
				bool isWall_t = isborder(i, j, n[t], m[t]);
				isWall[t][i][j] = isWall_t;
				addNode(maps[t], a[t][i][j], i, j, isWall_t);
				if (mins[t] > a[t][i][j])
					mins[t] = a[t][i][j];
				if (maxs[t] < a[t][i][j])
					maxs[t] = a[t][i][j];
			}
	}
	for (int t = 0; t < tNum; t++)
	{
		int volume_t = volume(a[t], isWall[t], n[t], m[t], mins[t], maxs[t], maps[t]);
		cout << volume_t << '\n';
	}
	return 0;
}*/