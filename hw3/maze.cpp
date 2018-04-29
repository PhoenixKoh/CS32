//#include <iostream>
//using namespace std;

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

	if (sr == er && sc == ec)
		return true;	
	maze[sr][sc] = '*'; // '*' for discovered sites

	// search possible directions
	if (sc < nCols - 1 && maze[sr][sc + 1] == '.')
	{
		bool temp = pathExists(maze, nRows, nCols, sr, sc + 1, er, ec);
		if (temp == true) return true; // if (temp == false), do NOT return false
	}

	if (sr < nRows - 1 && maze[sr + 1][sc] == '.')
	{
		bool temp = pathExists(maze, nRows, nCols, sr + 1, sc, er, ec);
		if (temp == true) return true;
	}

	if (sc > 0 && maze[sr][sc - 1] == '.')
	{
		bool temp = pathExists(maze, nRows, nCols, sr, sc - 1, er, ec);
		if (temp == true) return true;
	}

	if (sr > 0 && maze[sr - 1][sc] == '.')
	{
		bool temp = pathExists(maze, nRows, nCols, sr - 1, sc, er, ec);
		if (temp == true) return true;
	}
	return false; // final decision
}

//int main()
//{
//	string maze[10] = {
//		"XXXXXXXXXX",
//		"X...X..X.X",
//		"X..XX....X",
//		"X.X.XXXX.X",
//		"XXX......X",
//		"X...X.XX.X",
//		"X.X.X..X.X",
//		"X.XXXX.X.X",
//		"X..X...X.X",
//		"XXXXXXXXXX"
//	};
//
//	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
//		cout << "Solvable!" << endl;
//	else
//		cout << "Out of luck!" << endl;
//}