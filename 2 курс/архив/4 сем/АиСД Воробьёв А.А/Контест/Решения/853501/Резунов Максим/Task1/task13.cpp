#include <iostream>
#include <vector>
using namespace std;
/*
class Vertex
{
public:
	Vertex() :isUsed(false) {}
	inline void push_adjacent(Vertex* vertex)
	{
		verticesAdjacent.push_back(vertex);
	}
	inline bool getIsUsed() { return isUsed; }
	inline void setUsed(bool isUsed) { this->isUsed = isUsed; }
	bool go()
	{
		if (isUsed)
			return false;
		isUsed = true;

		for (Vertex* u : verticesAdjacent)
			u->go();

		return true;
	}
private:
	vector<Vertex*> verticesAdjacent;
	bool isUsed;
};
typedef Vertex* VertexPtr;

class Graph
{
public:
	Graph(int n, int m) : n(n), m(m), vertices(new VertexPtr[n])
	{
		for (int i = 0; i < n; i++)
			vertices[i] = new Vertex();
	}
	inline void setEdges()
	{
		int v1, v2;
		for (int i = 0; i < m; i++)
		{
			cin >> v1 >> v2;
			make_link(vertices[v1 - 1], vertices[v2 - 1]);
		}
	}
	inline int getConnectivityCount()
	{
		int result = 0;
		for (int i = 0; i < n; i++)
			if (vertices[i]->go())
				result++;
		return result;
	}
private:
	inline static void make_link(VertexPtr ver1, VertexPtr ver2)
	{
		ver1->push_adjacent(ver2);
		ver2->push_adjacent(ver1);
	}
	VertexPtr* vertices;
	int n;
	int m;
};

int main13()
{
	int n, m;
	cin >> n >> m;
	Graph* graph = new Graph(n, m);
	graph->setEdges();
	int connectivityCount = graph->getConnectivityCount();
	if (connectivityCount > 1)
		cout << -1;
	else
	{
		cout << m - n + 1;
	}
	return 0;
}*/