#include <iostream>
using namespace std;

const int MAXV = 1000;
const int ISA = 0;
const int HASA = 1;

class edge
{
public:
	int dest;
	int type;
	edge *next;

	edge(int id, int it, edge* nxt) : dest(id), type(it), next(nxt)
	{};
};

class vertex
{
public:
	string name;
	bool visited, hasvisited;
	edge* list;
} vertices[MAXV];
int nvert;
bool firsthasa;

void printGraph()
{
	for(int i=0; i<nvert; i++) {
		cout << vertices[i].name << ":";
		for(edge* e=vertices[i].list; e != 0; e = e->next) {
			if (e->type == ISA)
				cout << " is-a ";
			else
				cout << " has-a ";
			cout << vertices[e->dest].name << ',';
		}
		cout << endl;
	}

}

void resetVisited()
{
	for(int i=0; i<nvert; i++)
		vertices[i].visited = vertices[i].hasvisited = false;
}

int getVertex(string s)
{
	for(int i=0; i<nvert; i++)
		if (s == vertices[i].name)
			return i;
	vertices[nvert].name = s;
	vertices[nvert].list = 0;
	return nvert++;
}

void addEdge(string src, string dest, string type)
{
	int is = getVertex(src);
	int id = getVertex(dest);
	int it = ISA;
	if (type == "has-a")
		it = HASA;
	vertices[is].list = new edge(id, it, vertices[is].list);
}

bool checkIsa(edge *ed, int dest)
{
	if (ed->type != ISA)
		return false;
	int d = ed->dest;
	if (vertices[d].visited)
		return false;
	else if (d == dest)
		return true;
	vertices[d].visited = true;
	for(edge* e = vertices[d].list; e != 0; e = e->next) {
		if (checkIsa(e, dest))
			return true;
	}
	return false;
}

bool checkIsa(string src, string dest)
{
	if (src == dest)
		return true;			 // special case
	int is = getVertex(src);
	int id = getVertex(dest);
	resetVisited();
	vertices[is].visited = true;
	for(edge* e = vertices[is].list; e != 0; e = e->next) {
		if (checkIsa(e, id))
			return true;
	}
	return false;
}

bool checkHasa(edge *ed, int dest, bool hasaFlag)
{
	if (ed->type == HASA)
		hasaFlag = true;
	int d = ed->dest;
	if (d == dest && hasaFlag)
		return true;
	else if (vertices[d].visited && ed->type == ISA)
		return false;
    else if (vertices[d].hasvisited && ed->type == HASA)
        return false;
    if (ed->type == ISA)
        vertices[d].visited = true;
    else {
        if (firsthasa) {
            for(int i=0; i<nvert; i++)      // allow isa links to be visited one more time now
                vertices[i].visited = false;
            firsthasa = false;
        }
        vertices[d].hasvisited = true;
    }
	for(edge* e = vertices[d].list; e != 0; e = e->next) {
		if (checkHasa(e, dest, hasaFlag))
			return true;
	}
	return false;
}

bool checkHasa(string src, string dest)
{
	int is = getVertex(src);
	int id = getVertex(dest);
	resetVisited();
	for(edge* e = vertices[is].list; e != 0; e = e->next) {
		if (checkHasa(e, id, false))
			return true;
	}
	return false;
}

int main()
{
	int n, m;
	string s1, s2, s3;

	cin >> n >> m;
	nvert = 0;
	for(int i=0; i<n; i++) {
		cin >> s1 >> s2 >> s3;
		addEdge(s1, s3, s2);
	}

	int count = 0;
	for(int i=1; i<=m; i++) {
		cin >> s1 >> s2 >> s3;
//		cout << s1 << s2 << s3;
		cout << "Query " << i << ": ";
		if (s2 == "is-a") {
			if (checkIsa(s1, s3))
//				count++;
				cout << "true" << endl;
			else
				cout << "false" << endl;
		}
		else {
            firsthasa = true;
			if (checkHasa(s1, s3))
//				count++;
				cout << "true" << endl;
			else
				cout << "false" << endl;
		}
	}
//	cout << count << endl;
}
