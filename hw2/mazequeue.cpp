#include <queue>
#include <iostream>
using namespace std;

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
	queue<Coord> coordQueue;
	coordQueue.push(Coord(sr, sc));
	maze[sr][sc] = '*'; // '*' for discovered sites
	while (!coordQueue.empty())
	{
		Coord temp = coordQueue.front(); // top() for Stack while front() for Queue
		coordQueue.pop(); // Do not forget to REMOVE the top item in the stack
		// reach goal
		if (temp.r() == er && temp.c() == ec)
			return true;
		// search possible directions
		if (temp.c() < nCols - 1 && maze[temp.r()][temp.c() + 1] == '.')
		{
			coordQueue.push(Coord(temp.r(), temp.c() + 1));
			maze[temp.r()][temp.c() + 1] = '*';
		}

		if (temp.r() < nRows - 1 && maze[temp.r() + 1][temp.c()] == '.')
		{
			coordQueue.push(Coord(temp.r() + 1, temp.c()));
			maze[temp.r() + 1][temp.c()] = '*';
		}

		if (temp.c() > 0 && maze[temp.r()][temp.c() - 1] == '.')
		{
			coordQueue.push(Coord(temp.r(), temp.c() - 1));
			maze[temp.r()][temp.c() - 1] = '*';
		}

		if (temp.r() > 0 && maze[temp.r() - 1][temp.c()] == '.')
		{
			coordQueue.push(Coord(temp.r() - 1, temp.c()));
			maze[temp.r() - 1][temp.c()] = '*';
		}
	}
	return false;
}

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X...X..X.X",
		"X..XX....X",
		"X.X.XXXX.X",
		"XXX......X",
		"X...X.XX.X",
		"X.X.X..X.X",
		"X.XXXX.X.X",
		"X..X...X.X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}