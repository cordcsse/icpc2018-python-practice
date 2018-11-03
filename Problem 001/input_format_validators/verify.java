// Check bounds on m, n.
// Check every black pixel to see that (a) it is not part of a trivial
// 3-pixel "corner loop" (no interior white square) and (b) it has
// exactly two black pixels as neighbors

// More checking needs to be done (e.g., insufficient or too much data), but
// this is  at least a start.

import java.util.*;

public class verify {
  public static int m,n;
  public static Scanner in;
  public static int grid[][];
  public static boolean error;

  public static void main(String[] args) {
    in = new Scanner(System.in);
    error = false;
    m = in.nextInt();
    n = in.nextInt();
    if (m <1 || m > 100 || n < 1 || n > 100) {
      System.out.println ("Bad value(s) for m, n: "+m+" "+n);
      error = true;
    }
    grid = new int[m][n];

    for (int i=0; i < m; i++) {
      String s = in.next();
      for (int j=0; j < n; j++) {
        if (s.charAt(j) != '#' && s.charAt(j) != '.') {
          System.out.println("Bad character in line " + i+", col " + j);
          error = true;
        }
        grid[i][j] = s.charAt(j)=='#'?1:0;
      }
    }

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == 1) {
          check(i,j);
        }
      }
    }
    if (!error) {
       System.exit(42);
    } else {
      System.exit(1);
    }
  }

  public static void check(int r, int c) {
/*
    // check for "corners" (four cases):
    // ##
    // #.
    if (r+1 < m && c+1<n && grid[r+1][c]!=0 && grid[r][c+1]!=0){
      System.out.println("Corner at " + r + " " + c);
      System.out.println("##\n#.");
      error = true;
    }
    // #.
    // ##
    if (r-1>=0 && c+1<n && grid[r-1][c]!=0 && grid[r][c+1]!=0){
      System.out.println("Corner at " + r + " " + c);
      System.out.println("#.\n##");
      error = true;
    }
    // .#
    // ##
    if (r-1>=0 && c-1>=0 && grid[r-1][c]!=0 && grid[r][c-1]!=0){
      System.out.println("Corner at " + r + " " + c);
      System.out.println(".#\n##");
      error = true;
    }
    // ##
    // .#
    if (r+1<m && c-1>=0 && grid[r+1][c]!=0 && grid[r][c-1]!=0){
      System.out.println("Corner at " + r + " " + c);
      System.out.println("##\n.#");
      error = true;
    }
*/

    // verify neighbor count:
    int count = 0;
    for (int i = -1; i <=1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i==0 && j == 0) continue;
        if (r+i < 0 || r+i >= m) continue;
        if (c+j < 0 || c+j >= n) continue;
        
        if (grid[r+i][c+j] != 0) {
          count++;
        }
      }
    }
    if (count != 2) {
      System.out.println("Wrong neighbor count at "+r+" "+c);
      error = true;
    }
    return;
  }
}
