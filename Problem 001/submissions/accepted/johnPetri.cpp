#include <iostream>
using namespace std;

const int MAXS = 1000;

int grid[MAXS+2][MAXS+2];
int ncircuit;

void printGraph(int rows, int cols)
{
	for(int i=1; i<=rows; i++) {
		for(int j=1; j<=cols; j++) {
			if (grid[i][j] >= 0)
				cout << grid[i][j];
			else
				cout << '.';
		}
		cout << endl;
	}
}

void erasePixels(int r, int c)
{
	if (grid[r][c] == 0 || grid[r][c] == ncircuit) {
		grid[r][c] = -1;
		erasePixels(r-1, c-1);
		erasePixels(r, c-1);
		erasePixels(r+1, c-1);
		erasePixels(r-1, c);
		erasePixels(r+1, c);
		erasePixels(r-1, c+1);
		erasePixels(r, c+1);
		erasePixels(r+1, c+1);
	}
}

bool checkAdjacent(int r, int c, int& nextr, int& nextc)
{
	int count = 0;
	nextr = nextc = -1;
	for(int i=r-1; i<=r+1; i++) {
		for(int j=c-1; j<=c+1; j++) {
//cout << "  " << i << ',' << j << ' ' << nextr << ',' << nextc << endl;
			if (i==r && j==c)
				continue;
			if (grid[i][j] == 0) {
				count++;
//cout << "  setting nextr, nextc to " << i << ',' << j << endl;
				nextr = i;
				nextc = j;
			}
			else if (grid[i][j] == ncircuit)
				count++;
		}
		if (count > 2)
			return false;
	}
//cout << "  count = " << count << ", returning " << nextr << ',' << nextc << endl;
	return (count == 2);
}

bool checkForCircuit(int r, int c, int startr, int startc)
{
//cout << "check for circuit: r, c = " << r << ',' << c << endl;
	int nextr, nextc;
	if (!checkAdjacent(r, c, nextr, nextc))
		return false;
	grid[r][c] = ncircuit;
	if (nextr == -1 && nextc == -1)
		return true;
	return checkForCircuit(nextr, nextc, startr, startc);
}

int main()
{
	int n, m;

	cin >> n >> m;
	for(int i=0; i<n+2; i++)
		grid[i][0] = grid[i][m+1] = -1;
	for(int j=0; j<m+2; j++)
		grid[0][j] = grid[n+1][j] = -1;

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			char ch;
			cin >> ch;
			if (ch == '.')
                grid[i][j] = -1;
            else
                grid[i][j] = 0;
        }
	}
//	printGraph(n, m);
									// find all closed curves
	ncircuit = 1;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++){
			if (grid[i][j] == 0) {
				if (!checkForCircuit(i, j, i, j))
					erasePixels(i, j);
				else
					ncircuit++;
			}
		}
	}
	cout << ncircuit-1 << endl;
//	printGraph(n,m);
}
