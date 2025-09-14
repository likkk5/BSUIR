#include <iostream>
#include <string>
#include <cmath>
#include <queue>
using namespace std;

class Cell {
public:
	Cell() : Cell(0, 0, 0) {}
	Cell(int X, int Y, int Dist) : X(X), Y(Y), Dist(Dist) {}
	void inX() { cin >> this->X; X--; }
	void inY() { cin >> this->Y; Y--; }
	void setX(int X) { this->X = X; }
	void setY(int Y) { this->Y = Y; }
	void setDist(int Dist) { this->Dist = Dist; }
	int x() { return X; }
	int y() { return Y; }
	int distance() { return Dist; }
private:
	int X;
	int Y;
	int Dist;
};

class Chessboard
{
public:
	Chessboard() : Chessboard(0, 0) { reset_grid(); }
	Chessboard(int N, int M) : N(N), M(M) { reset_grid(); }
	void inNM()
	{
		cin >> this->N;
		cin >> this->M;
		reset_grid();
	}
	bool isInChessboard(int i, int j)
	{
		if (i >= 0 && i < N && j >= 0 && j < M)
			return true;
		else
			return false;
	}
	bool isUsed(int i, int j)
	{
		if (isInChessboard(i, j))
			return used[i][j];
		return false;
	}
	void setUsed(int i, int j, bool used)
	{
		if (isInChessboard(i, j))
			this->used[i][j] = used;
	}
private:
	void reset_grid()
	{
		if (used != nullptr)
		{
			for (int i = 0; i < N; i++)
				delete[] used[i];
			delete[] used;
			used = nullptr;
		}
		if (!(N == 0 || M == 0))
		{
			used = new bool*[N];
			for (int i = 0; i < N; i++)
			{
				used[i] = new bool[M];
				for (int j = 0; j < M; j++)
					used[i][j] = false;
			}
		}
	}
	int N, M;
	bool** used = nullptr;
};

int main4() {
	queue<Cell> q;
	Cell current, goal, next;
	
	Chessboard board;
	board.inNM();
	goal.inX(); goal.inY();

	board.setUsed(current.x(), current.y(), true);

	q.push(current);

	while (!(current.x() == goal.x() && current.y() == goal.y())) {
		if (q.empty())
		{
			cout << "NEVAR";
			return 0;
		}
		current = q.front();
		q.pop();
		next.setDist(current.distance() + 1);
		for (int i = -2; i <= 2; i++)
			if (i != 0)
				for (int j = -(3 - abs(i)); j <= 3 - abs(i); j += 2 * (3 - abs(i))) {
					next.setX(current.x() + i);
					next.setY(current.y() + j);
					if (board.isInChessboard(next.x(), next.y()) && !board.isUsed(next.x(), next.y()))
					{
						q.push(next);
						board.setUsed(next.x(), next.y(), true);
					}
				}
	}

	cout << current.distance();
	return 0;
}