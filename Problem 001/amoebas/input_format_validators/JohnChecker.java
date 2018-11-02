import java.util.*;

// Checker for Sheba's Amoebas

public class JohnChecker
{
    public static final int MINNM = 1;
	public static final int MAXNM = 100;

	public static String [] lines = new String[MAXNM];

	public static void printError(int line, String msg)
	{
		System.out.println("ERROR Line " + line + ": " + msg);
		System.exit(-1);
	}

    public static void checkIntBounds(int x, int min, int max, String name, int nLines)
    {
        if (x < min || x > max)
            printError(nLines, "invalid " + name + " value: " + x);
    }

    public static void checkForRepeats(int size, int nLines)
    {
        for(int i=0; i<size-1; i++)
            if (lines[i].equals(lines[size-1]))
                printError(nLines, "repeated line " + lines[size-1]);
    }
	public static void main(String [] args)
	{
		Scanner in = new Scanner(System.in);
		int n, m, nLines = 0;
		String line;

        line = in.nextLine();
        nLines++;
        StringTokenizer st = new StringTokenizer(line);
        if (st.countTokens() != 2)
            printError(nLines, "number of values on line incorrect");
		m = Integer.parseInt(st.nextToken());
        n = Integer.parseInt(st.nextToken());
		checkIntBounds(m, MINNM, MAXNM, "m", nLines);
		checkIntBounds(n, MINNM, MAXNM, "n", nLines);
		for(int i=0; i<m; i++) {
			line = in.nextLine();
			nLines++;
			if (line.length() != n)
                printError(nLines, "number of characters on line incorrect");
			for(int j=0; j<n; j++) {
                char ch = line.charAt(j);
                if (ch != '#' && ch != '.')
                    printError(nLines, "illegal character: " + ch);
			}
		}
		if (in.hasNextLine())
			printError(nLines, "extra number of lines");
    System.exit(42);
	}
}
