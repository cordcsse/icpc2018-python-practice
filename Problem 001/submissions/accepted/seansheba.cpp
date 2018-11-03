#include <iostream>
#include <vector>

using namespace std;

void Check(const vector<vector<char> >& Grid, int cur_r, int cur_c, int& next_r, int& next_c){
  if(cur_r >= 0 && cur_r < Grid.size() && cur_c >= 0 && cur_c < Grid[cur_r].size()){
    if(Grid[cur_r][cur_c] == '#'){
      next_r = cur_r;
      next_c = cur_c;
    }
    if(Grid[cur_r][cur_c] == '$' && next_r == -1){
      next_r = cur_r;
      next_c = cur_c;
    }
  }
}

void Erase(vector<vector<char> >& Grid, int r, int c){
  int cur_r = r;
  int cur_c = c;
  Grid[r][c] = '$';
  bool done = false;
  while(!done){
    int next_r = -1;
    int next_c = -1;
    
    Check(Grid, cur_r-1, cur_c-1, next_r, next_c);
    Check(Grid, cur_r-1, cur_c, next_r, next_c);
    Check(Grid, cur_r-1, cur_c+1, next_r, next_c);
    Check(Grid, cur_r, cur_c-1, next_r, next_c);
    Check(Grid, cur_r, cur_c+1, next_r, next_c);
    Check(Grid, cur_r+1, cur_c-1, next_r, next_c);
    Check(Grid, cur_r+1, cur_c, next_r, next_c);
    Check(Grid, cur_r+1, cur_c+1, next_r, next_c);
    Grid[next_r][next_c] = '.';
    cur_r = next_r;
    cur_c = next_c;
    if(next_r == r && next_c == c)
      done = true;
  }

}
  
int main(){
  int m, n;
  cin >> m >> n;
  vector<vector<char> > Grid(m);
  for(int i = 0; i < m; i++)
    Grid[i].resize(n);
  for(int i = 0; i < m; i++)
    for(int j = 0; j < n; j++)
      cin >> Grid[i][j];

  int num_amoebas = 0;
  for(int i = 0; i < m; i++)
    for(int j = 0; j < n; j++){
      if(Grid[i][j] == '#'){
	num_amoebas++;
	Erase(Grid, i, j);
      }
    }

  cout << num_amoebas << endl;

  return 0;
}
