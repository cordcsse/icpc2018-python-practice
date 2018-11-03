import java.util.*;

public class JohnPetri
{
    public static final int MAXS = 1000;

    public static Scanner in = new Scanner(System.in);

    public static int[][] grid = new int[MAXS+2][MAXS+2];
    public static int ncircuit;

    public static void erasePixels(int r, int c)
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

    public static boolean checkAdjacent(int r, int c, RC rc)
    {
        int count = 0;
        rc.row = rc.col = -1;
        for(int i=r-1; i<=r+1; i++) {
            for(int j=c-1; j<=c+1; j++) {
                if (i==r && j==c)
                    continue;
                if (grid[i][j] == 0) {
                    count++;
                    rc.row = i;
                    rc.col = j;
                }
                else if (grid[i][j] == ncircuit)
                    count++;
            }
            if (count > 2)
                return false;
        }
        return (count == 2);
    }

    public static boolean checkForCircuit(int r, int c, int startr, int startc)
    {
        RC rc = new RC();
        int nextr, nextc;
        if (!checkAdjacent(r, c, rc))
            return false;
        nextr = rc.row;
        nextc = rc.col;
        grid[r][c] = ncircuit;
        if (nextr == -1 && nextc == -1)
            return true;
        return checkForCircuit(nextr, nextc, startr, startc);
    }

    public static void main(String [] args)
    {
        int n, m;

        n = in.nextInt();
        m = in.nextInt();
        for(int i=0; i<n+2; i++)
            grid[i][0] = grid[i][m+1] = -1;
        for(int j=0; j<m+2; j++)
            grid[0][j] = grid[n+1][j] = -1;

        for(int i=1; i<=n; i++) {
            String line = in.next();
            for(int j=1; j<=m; j++) {
                char ch = line.charAt(j-1);
                if (ch == '.')
                    grid[i][j] = -1;
                else
                    grid[i][j] = 0;
            }
        }
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
        System.out.println(ncircuit-1);
    }
}

class RC
{
    public int row, col;
}
