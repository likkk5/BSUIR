#include <iostream>
#include <list>
using namespace std;

typedef struct _MapNode
{
	void set(_MapNode *top, _MapNode *down, _MapNode *left, _MapNode *right)		
	{
		this->top = top;
		this->down = down;
		this->left = left;
		this->right = right;
	}
	int height;
	bool isWall;
	_MapNode *next;
	_MapNode *top;
	_MapNode *down;
	_MapNode *left;
	_MapNode *right;
} MapNode;

MapNode** mapStartHeightNodesWalls = new MapNode*[10000]; //словарь указателей соответствия узлов высотам для стен
MapNode** mapEndHeightNodesWalls = new MapNode*[10000]; //словарь указателей соответствия узлов высотам для стен

MapNode*** a;
int tNum;
int *n, *m;
int *maxs;
int *mins;
int *volumesResult;

/*int testGrid1[4][6] =
{
	{3,3,4,4,4,2},
	{3,1,6,2,1,4},
	{3,5,4,3,1,4},
	{7,3,1,6,3,1}
};

int testGrid2[3][6] =
{
	{3,3,4,4,4,2},
	{3,1,3,2,1,4},
	{7,3,1,6,4,1}
};*/

MapNode*** createMatrix(int n, int m)
{
	MapNode ***a = new MapNode**[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new MapNode*[m];
		for (int j = 0; j < m; j++)
			a[i][j] = new MapNode();
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			MapNode *top = (j > 0) ? a[i][j - 1] : nullptr;
			MapNode *down = (j < m - 1) ? a[i][j + 1] : nullptr;
			MapNode *left = (i > 0) ? a[i - 1][j] : nullptr;
			MapNode *right = (i < n - 1) ? a[i + 1][j] : nullptr;
			a[i][j]->set(top, down, left, right);
		}
	return a;
}

void deleteMatrix(MapNode*** a, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			delete a[i][j];
		delete[] a[i];
	}
	delete[] a;
}

inline bool isborder(int i, int j, int n, int m)
{
	return (i == 0 || j == 0 || i == (n - 1) || j == (m - 1));
}


inline void addNodeToWalls(MapNode *nodePtr)
{
	int height = nodePtr->height;

	nodePtr->next = mapStartHeightNodesWalls[height];
	mapStartHeightNodesWalls[height] = nodePtr;
	if (mapEndHeightNodesWalls[height] == nullptr)
		mapEndHeightNodesWalls[height] = nodePtr;
}

void insertToWallsNode(MapNode *wall, MapNode *notWall)
{
	if (notWall->height <= wall->height)
	{
		MapNode *nextOfWall = wall->next;
		wall->next = notWall;
		notWall->next = nextOfWall;
	}
	else
		addNodeToWalls(notWall);
}

int minWallAround(MapNode* nodePtr)
{
	int minWall = INT32_MAX;
	if (nodePtr->down->isWall)
		minWall = nodePtr->down->height;
	if (nodePtr->top->isWall && nodePtr->top->height < minWall)
		minWall = nodePtr->top->height;
	if (nodePtr->left->isWall && nodePtr->left->height < minWall)
		minWall = nodePtr->left->height;
	if (nodePtr->right->isWall && nodePtr->right->height < minWall)
		minWall = nodePtr->right->height;
	return minWall;
}

int doWall(MapNode* nodePtr)
{
	nodePtr->isWall = true;
	int minWall = minWallAround(nodePtr);
	if (nodePtr->height < minWall)
	{
		int res = minWall - nodePtr->height;
		nodePtr->height = minWall;
		return res;
	}
	else
		return 0;
}

int calculateVolume(int t)
{
	int sum = 0;
	for (int i = mins[t]; i <= maxs[t]; i++)
		if (mapStartHeightNodesWalls[i] != nullptr)
		{
			MapNode *wallIncr = mapStartHeightNodesWalls[i];
			while (wallIncr != nullptr)
			{
				if (wallIncr->top)
					if (!wallIncr->top->isWall)
					{
						sum += doWall(wallIncr->top);
						insertToWallsNode(wallIncr, wallIncr->top);
					}
				if (wallIncr->down)
					if (!wallIncr->down->isWall)
					{
						sum += doWall(wallIncr->down);
						insertToWallsNode(wallIncr, wallIncr->down);
					}
				if (wallIncr->left)
					if (!wallIncr->left->isWall)
					{
						sum += doWall(wallIncr->left);
						insertToWallsNode(wallIncr, wallIncr->left);
					}
				if (wallIncr->right)
					if (!wallIncr->right->isWall)
					{
						sum += doWall(wallIncr->right);
						insertToWallsNode(wallIncr, wallIncr->right);
					}
				wallIncr = wallIncr->next;
			}
		}
	return sum;
}

inline void initFirst()
{
	cin >> tNum;
	n = new int[tNum];
	m = new int[tNum];
	maxs = new int[tNum] {INT32_MIN};
	mins = new int[tNum] {INT32_MAX};
	volumesResult = new int[tNum];
}

inline void init(int t)
{
	int maxHeightLast = (t == 0) ? 10000 : maxs[t - 1] + 1;
	for (int i = 0; i < maxHeightLast; i++)
	{		
		mapStartHeightNodesWalls[i] = nullptr;
		mapEndHeightNodesWalls[i] = nullptr;
	}
}

int main()
{
	initFirst();
	for (int t = 0; t < tNum; t++)
	{
		init(t);
		cin >> n[t] >> m[t];
		//n[t] = 3; m[t] = 6;
		a = createMatrix(n[t], m[t]);

		for (int i = 0; i < n[t]; i++)
			for (int j = 0; j < m[t]; j++)
			{
				//a[i][j]->height = testGrid2[i][j];
				cin >> a[i][j]->height;
				a[i][j]->isWall = isborder(i, j, n[t], m[t]);

				if (a[i][j]->isWall)
					addNodeToWalls(a[i][j]);

				if (mins[t] > a[i][j]->height)
					mins[t] = a[i][j]->height;
				if (maxs[t] < a[i][j]->height)
					maxs[t] = a[i][j]->height;
			}
		volumesResult[t] = calculateVolume(t);
		deleteMatrix(a, n[t], m[t]);
	}
	for (int t = 0; t < tNum; t++)
		cout << volumesResult[t] << '\n';
	return 0;
}