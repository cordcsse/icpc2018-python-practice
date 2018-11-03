import java.util.*;

public class IsaHasaJohn 
{
	public static Vertex vertices[] = new Vertex[1000];
	
	public static int MAXV = 1000;
	public static int ISA = 0;
	public static int HASA = 1;
	
	public static int nvert;
	public static boolean firsthasa;
	
	public static void main(String[] args) 
	{
		Scanner scan = new Scanner(System.in);
		
		int n = scan.nextInt();
		int m = scan.nextInt();
		String s1, s2, s3;
		
		nvert = 0;
		for (int i = 0; i < n; i++)
		{
			s1 = scan.next();
			s2 = scan.next();
			s3 = scan.next();
			addEdge(s1, s3, s2);
		}
		
		for (int i = 1; i <= m; i++)
		{
			s1 = scan.next();
			s2 = scan.next();
			s3 = scan.next();

			System.out.print("Query " + i + ": ");
			
			if (s2.equals("is-a"))
			{
				if (checkIsa(s1, s3))
				{
					System.out.println("true");
				}
				else
				{
					System.out.println("false");
				}
			}
			else {
	            firsthasa = true;
				if (checkHasa(s1, s3))
				{
					System.out.println("true");
				}
				else
				{
					System.out.println("false");
				}
			}
		}
		
		scan.close();
	}
	
	public static void addEdge(String src, String dest, String type)
	{
		int is = getVertex(src);
		int id = getVertex(dest);
		int it = ISA;
		if (type.equals("has-a"))
			it = HASA;
		
		vertices[is].list = new Edge(id, it, vertices[is].list);
	}
	
	public static boolean checkIsa(String src, String dest)
	{
		if (src.equals(dest))
			return true;			 // special case
		int is = getVertex(src);
		int id = getVertex(dest);
		resetVisited();
		vertices[is].visited = true;
		for(Edge e = vertices[is].list; e != null; e = e.next) {
			if (checkIsa(e, id))
				return true;
		}
		return false;
	}
	
	public static boolean checkIsa(Edge ed, int dest)
	{
		if (ed.type != ISA)
			return false;
		int d = ed.dest;
		if (vertices[d].visited)
			return false;
		else if (d == dest)
			return true;
		vertices[d].visited = true;
		for(Edge e = vertices[d].list; e != null; e = e.next) {
			if (checkIsa(e, dest))
				return true;
		}
		return false;
	}
	
	public static boolean checkHasa(String src, String dest)
	{
		int is = getVertex(src);
		int id = getVertex(dest);
		resetVisited();
		for (Edge e = vertices[is].list; e != null; e = e.next) {
			if (checkHasa(e, id, false))
				return true;
		}
		return false;
	}
	
	public static boolean checkHasa(Edge ed, int dest, boolean hasaFlag)
	{
		if (ed.type == HASA)
			hasaFlag = true;
		int d = ed.dest;
		if (d == dest && hasaFlag)
			return true;
		else if (vertices[d].visited && ed.type == ISA)
			return false;
	    else if (vertices[d].hasvisited && ed.type == HASA)
	        return false;
	    if (ed.type == ISA)
	        vertices[d].visited = true;
	    else {
	        if (firsthasa) {
	            for(int i=0; i<nvert; i++)      // allow isa links to be visited one more time now
	                vertices[i].visited = false;
	            firsthasa = false;
	        }
	        vertices[d].hasvisited = true;
	    }
		for(Edge e = vertices[d].list; e != null; e = e.next) {
			if (checkHasa(e, dest, hasaFlag))
				return true;
		}
		return false;
	}
	
	public static int getVertex(String s)
	{
		for(int i=0; i<nvert; i++)
			if (s.equals(vertices[i].name))
				return i;
		
		vertices[nvert] = new Vertex();
		vertices[nvert].name = s;
		vertices[nvert].list = null;
		return nvert++;
	}
	
	public static void resetVisited()
	{
		for(int i=0; i<nvert; i++)
			vertices[i].visited = vertices[i].hasvisited = false;
	}
	
	static class Vertex
	{
		public String name;
		public boolean visited;
		public boolean hasvisited;
		public Edge list;
	}
	
	static class Edge
	{
		public int dest;
		public int type;
		public Edge next;
		
		public Edge(int id, int it, Edge nxt)
		{
			dest = id;
			type = it;
			next = nxt;
		}
	}
}
