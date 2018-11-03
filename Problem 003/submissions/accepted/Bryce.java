import java.util.*;

public class Bryce {

    static int MAXN = 500;
    static HashMap<String, Integer> clsToIdx = new HashMap<String, Integer>();

    static int getIdx(String cls) {
        if (!clsToIdx.containsKey(cls)) {
            int size = clsToIdx.size();
            clsToIdx.put(cls, size);
        }
        
        return clsToIdx.get(cls);
    }

    public static void main(String[] args) {
        int n, m;
        Scanner in = new Scanner(System.in);
        n = in.nextInt();
        m = in.nextInt();

        boolean[][] is_a = new boolean[MAXN][MAXN];
        boolean[][] has_a = new boolean[MAXN][MAXN];

        for (int i = 0; i < MAXN; ++i) {
            is_a[i][i] = true;
        }

        for (int i = 0; i < n; ++i) {
            String c1, r, c2;
            c1 = in.next();
            r = in.next();
            c2 = in.next();

            int id1 = getIdx(c1);
            int id2 = getIdx(c2);

            if (r.equals("is-a")) {
                is_a[id1][id2] = true;
            }
            else {
                has_a[id1][id2] = true;
            }
        }

        for (int k = 0; k < MAXN; ++k) {
            for (int i = 0; i < MAXN; ++i) {
                for (int j = 0; j < MAXN; ++j) {
                    is_a[i][j] = is_a[i][j] || (is_a[i][k] && is_a[k][j]);
                    has_a[i][j] = has_a[i][j] || (has_a[i][k] && has_a[k][j]);

                    has_a[i][j] = has_a[i][j] || (is_a[i][k] && has_a[k][j]);
                    has_a[i][j] = has_a[i][j] || (has_a[i][k] && is_a[k][j]);
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            String c1, r, c2;

            c1 = in.next();
            r = in.next();
            c2 = in.next();

            int id1 = getIdx(c1);
            int id2 = getIdx(c2);

            boolean success = false;
            if (r.equals("is-a")) {
                success = is_a[id1][id2];
            }
            else {
                success = has_a[id1][id2];
            }

            if (success) {
                System.out.println("Query " + (i+1) + ": true");
            }
            else {
                System.out.println("Query " + (i+1) + ": false");
            }
        }
    }
}
