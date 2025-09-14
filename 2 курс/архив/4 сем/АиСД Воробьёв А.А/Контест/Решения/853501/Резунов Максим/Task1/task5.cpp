#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Edge;
class Vertex
{
public:
	Vertex() : num(++counter) {}
	Vertex(int num) :num(num) {}
	inline void push_edge(Edge* vertex)
	{
		edgesAdjacent.push_back(vertex);
	}
	inline const vector<Edge*> & getEdges() const { return edgesAdjacent; }
	inline bool operator ==(const Vertex& vertex) const
	{
		return num == vertex.num;
	}
private:
	int num;
	vector<Edge*> edgesAdjacent;
	static int counter;
};
int Vertex::counter = 0;

class Edge
{
public:
	Edge(const Vertex &vertex1, const Vertex &vertex2, int weight) :
		vertex1(vertex1), vertex2(vertex2), weight(weight), isUsed(false), wasUsed(false) {}
	inline int getWeight() { return weight; }
	inline const Vertex &getVert1() { return vertex1; }
	inline const Vertex &getVert2() { return vertex2; }
	inline const Vertex &getOther(const Vertex &vertex)
	{
		if (!(vertex == vertex1))
			return vertex1;
		if (!(vertex == vertex2))
			return vertex2;
		return vertex;
	}
	inline bool getWasUsed() { return wasUsed; }
	inline bool getIsUsed() { return isUsed; }
	inline void setUsed(bool isUsed)
	{
		this->isUsed = isUsed;
		if (isUsed)
			wasUsed = true;
	}
private:
	const Vertex &vertex1, &vertex2;
	int weight;
	bool isUsed;
	bool wasUsed;
};
typedef Edge* EdgePtr;

class Path
{
public:
	Path() : edgeStart(nullptr), edgeGoal(nullptr), weight(0) {}
	Path(const Path & path) : edgeStart(path.edgeStart), edgeGoal(path.edgeGoal), weight(path.weight) {}
	inline void push_edge(EdgePtr edge)
	{
		if (edgeStart == nullptr && edgeGoal == nullptr)
		{
			edgeStart = edge;
			edgeGoal = edge;
		}
		else
			edgeGoal = edge;
		weight += edge->getWeight();
	}
	static list<Path*> build_pathes(const list<Path*> &pathes, const Vertex &start_t, const Vertex &goal)
	{
		/*bool wasUsed = true;
		for (auto edge : start_t->getEdges())
			if (!edge->getWasUsed())
				wasUsed = false;
		bool correct = true;
		for (auto path : pathes)
			if (!path->isCorrectPath(goal, goal))
				correct = false;*/
		if (start_t == goal/* && wasUsed && correct*/)
			return pathes;

		list<pair<const Vertex&, EdgePtr>> vertEdges;
		for (auto edge : start_t.getEdges())
		{
			const Vertex &other = edge->getOther(start_t);
			if (!edge->getIsUsed())
			{
				vertEdges.push_back(pair<const Vertex&, EdgePtr>(other, edge));
				edge->setUsed(true);
			}
		}

		if (vertEdges.empty())
			return pathes;

		list<Path*> pathes_out;
		for (auto iterVertEdge = vertEdges.cbegin(); iterVertEdge != vertEdges.cend(); iterVertEdge++)
		{
			auto VertEdgePair = *iterVertEdge;
			const Vertex &nextVertex = VertEdgePair.first;
			list<Path*> pathes_new;
			for (auto path : pathes)
				pathes_new.push_back(new Path(*path));
			for (auto path : pathes_new)
				path->push_edge(VertEdgePair.second);
			list<Path*> pathes_out_t = build_pathes(pathes_new, nextVertex, goal);
			for (auto path : pathes_out_t)
				pathes_out.push_back(path);
		}

		for (auto path : pathes)
			delete path;
		for (auto ve : vertEdges)
			ve.second->setUsed(false);
		return pathes_out;
	}
	static list<Path*> build_pathes_equal_SG(const list<Path*> &pathes, const Vertex &start_t, const Vertex &goal)
	{
		if (start_t == goal)
			return pathes;
		list<Path*> pathes_out;
		for (auto edge : start_t.getEdges())
		{
			const Vertex &other = edge->getOther(start_t);
			if (!edge->getIsUsed())
			{
				edge->setUsed(true);
				list<Path*> pathes_new;
				for (auto path : pathes)
					pathes_new.push_back(new Path(*path));
				for (auto path : pathes_new)
					path->push_edge(edge);
				list<Path*> pathes_out_t = build_pathes_equal_SG(pathes_new, other, goal);
				for (auto path : pathes_out_t)
					pathes_out.push_back(path);
				edge->setUsed(false);
			}
		}
		for (auto path : pathes)
			delete path;
		return pathes_out;
	}
	int getWeight() { return weight; }
	bool isCorrectPath(const Vertex &start, const Vertex &goal)
	{
		if (edgeStart == nullptr && edgeGoal == nullptr)
			return false;
		else if (edgeStart == edgeGoal)
			return ((edgeStart->getVert1() == start && edgeStart->getVert2() == goal) ||
			(edgeStart->getVert1() == goal && edgeStart->getVert2() == start));
		else
			return ((edgeStart->getVert1() == start || edgeStart->getVert2() == start) &&
			(edgeGoal->getVert1() == goal || edgeGoal->getVert2() == goal));
	}
private:
	EdgePtr edgeStart;
	EdgePtr edgeGoal;
	int weight;
};
typedef Path* PathPtr;

class Graph
{
public:
	Graph(int n, int m) : n(n), m(m), vertices(new Vertex[n]), edges(new EdgePtr[m])
	{
	}
	inline void setEdges()
	{
		int v1, v2, weight;
		for (int i = 0; i < m; i++)
		{
			cin >> v1 >> v2 >> weight;
			edges[i] = make_link(vertices[v1 - 1], vertices[v2 - 1], weight);
		}
	}
	int getMinWeightPath()
	{
		int vstart, vgoal;
		cin >> vstart >> vgoal;

		const Vertex &start = vertices[vstart - 1];
		const Vertex &goal = vertices[vgoal - 1];

		if (start == goal)
			return 0;

		list<Path*> pathes_in; pathes_in.push_back(new Path());
		list<Path*> pathes = Path::build_pathes_equal_SG(pathes_in, start, goal);
		int weight = INT32_MAX;
		for (auto path : pathes)
			if (weight > path->getWeight() && path->isCorrectPath(start, goal))
				weight = path->getWeight();
		return weight;
	}
private:
	inline static EdgePtr make_link(Vertex &ver1, Vertex &ver2, int weight)
	{
		EdgePtr edge = new Edge(ver1, ver2, weight);
		ver1.push_edge(edge);
		if (!(ver1 == ver2))
			ver2.push_edge(edge);
		return edge;
	}
	Vertex* vertices;
	EdgePtr* edges;
	int n;
	int m;
};

int main5()
{
	int n, m;
	cin >> n >> m;
	Graph* graph = new Graph(n, m);
	graph->setEdges();
	cout << graph->getMinWeightPath();
	return 0;
}
