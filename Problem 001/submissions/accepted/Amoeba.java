// Simplest solution: assuming that ONLY valid loops appear
// in the input, simply search the grid for black pixels,
// then recursively mark them by going around the loop.
//
// Time: O(m*n)

import java.util.*;

public class Amoeba {
  public static int m,n;
  public static Scanner in;
  public static int grid[][];

  public static void main(String[] args) {
    in = new Scanner(System.in);
    m = in.nextInt();
    n = in.nextInt();
    int loop = 2;
    grid = new int[m][n];

    for (int i=0; i < m; i++) {
      String s = in.next();
      for (int j=0; j < n; j++) {
        grid[i][j] = s.charAt(j)=='#'?1:0;
      }
    }

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          recurse(i,j,loop);
          loop++;
        }
      }
    }
    System.out.println(loop-2);
  }

  public static void recurse(int r, int c, int loop) {
    if (grid[r][c] == loop) {
      return; // reached beginning
    }
    grid[r][c] = loop;
    for (int i = -1; i <=1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i==0 && j == 0) continue;
        if (r+i < 0 || r+i >= m) continue;
        if (c+j < 0 || c+j >= n) continue;
        if (grid[r+i][c+j] == 1) {
          recurse(r+i,c+j,loop);
          return;
        }
      }
    }
  }
}
