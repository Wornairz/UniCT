#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

unsigned int bestpath, caunter;
time_t inizio;

class Punto{
  public:
    unsigned short x, y;
    Punto(unsigned short x,unsigned short y){
      this->x=x;
      this->y=y;
    }
    Punto(){
      x=0;
      y=0;
    }
};

int minimo(vector<int> v){
  int min=v[0];
  for(int i=1; i<v.size(); i++){
    if(v[i]<min) min=v[i];
  }
  return min;
}
bool giapass(vector<Punto*> v, Punto* p){
  for(int i=0; i<v.size(); i++){
    if((v[i])->x == p->x && (v[i])->y == p->y) return true;
  }
}
void stampa(char** mat, unsigned short n, unsigned short m){
    cout << endl;
    for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
        cout << mat[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
}

void findpath(char** mat, unsigned short n, unsigned short m, unsigned int count, Punto* p, Punto& u, vector<Punto*> puntiv){
  //cout << "x=" << p->x << " y=" << p->y << endl;
  //cout << bestpath << endl;
  if(giapass(puntiv, p) || count+((sqrt(pow(p->x-u.x,2)+pow(p->y-u.y,2)))/2)>=bestpath || abs(difftime(inizio, time(0)))>40){
    return;
  }
  else if(p->x == u.x && p->y == u.y)
  {
    if(count < bestpath) bestpath = count;
    return;
  }
  else{
    puntiv.push_back(p);
    Punto* temp;
    if(p->x-2>=0 && mat[p->x-2][p->y]!='X' && p->x>u.x){
      temp = new Punto(p->x-2, p->y);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->x+2<n && mat[p->x+2][p->y]!='X' && p->x<u.x){
      temp = new Punto(p->x+2, p->y);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->y+2<m && mat[p->x][p->y+2]!='X' && p->y<u.y){
      temp = new Punto(p->x, p->y+2);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->y-2>=0 && mat[p->x][p->y-2]!='X' && p->y>u.y){
      temp = new Punto(p->x, p->y-2);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->x+1<n && p->y+1<m && mat[p->x+1][p->y+1]!='X' && (p->x<u.x || p->y<u.y)){
      temp = new Punto(p->x+1, p->y+1);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->x+1<n && p->y-1>=0 && mat[p->x+1][p->y-1]!='X' && (p->x<u.x || p->y>u.y) ){
      temp = new Punto(p->x+1, p->y-1);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->x-1>=0 && p->y-1>=0 && mat[p->x-1][p->y-1]!='X' && (p->x>u.x || p->y>u.y)){
      temp = new Punto(p->x-1, p->y-1);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->x-1>=0 && p->y+1<m && mat[p->x-1][p->y+1]!='X' && (p->x>u.x || p->y<u.y)){
      temp = new Punto(p->x-1, p->y+1);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->x+1<n && mat[p->x+1][p->y]!='X' && p->x<u.x){
      temp = new Punto(p->x+1, p->y);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->x-1>=0 && mat[p->x-1][p->y]!='X' && p->x>u.x){
      temp = new Punto(p->x-1, p->y);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->y+1<m && mat[p->x][p->y+1]!='X' && p->y<u.y){
      temp = new Punto(p->x, p->y+1);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
    if(p->y-1>=0 && mat[p->x][p->y-1]!='X' && p->y>u.y){
      temp = new Punto(p->x, p->y-1);
      findpath(mat, n, m, count+1, temp, u, puntiv);
      delete temp;
    }
  }
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	unsigned short n, m;
  Punto* E;
  Punto U;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n; iss >> m;
    bestpath = (n+m)*2;
    char** mat = new char*[n];
		for(int i=0; i<n; i++){
      mat[i] = new char[m];
      for(int j=0; j<m; j++){
        iss >> mat[i][j];
        if(mat[i][j]=='E'){
          E = new Punto(i, j);
        }
        else if(mat[i][j]=='U'){
          U.x=i;
          U.y=j;
        }
      }
		}
    time(&inizio);
    vector<Punto*> puntiv;
    //stampa(mat, n, m);
    cout << " caunter= " << ++caunter << endl;
    findpath(mat, n, m, 0, E, U, puntiv);
		outfile << bestpath << "\n";
	}
	return 0;
}
