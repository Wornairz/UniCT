#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

unsigned short vbra, vcar;
bool brancata;

void azzera(char m[][3]){
  brancata = true;
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      m[i][j]=' ';
    }
  }
}

void stampa(char m[][3]){
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      cout << m[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void checkvittoria(char m[][3]){
  if(m[0][0]=='x' && m[0][1]=='x' && m[0][2]=='x'){
     vbra++; //1 riga bra
     azzera(m);
   }
  else if(m[1][0]=='x' && m[1][1]=='x' && m[1][2]=='x'){
     vbra++; //2 riga bra
     azzera(m);
   }
  else if(m[2][0]=='x' && m[2][1]=='x' && m[2][2]=='x'){
     vbra++; //3 riga bra
     azzera(m);
   }
  else if(m[0][0]=='x' && m[1][0]=='x' && m[2][0]=='x'){
     vbra++; //1 colonna  bra
     azzera(m);
   }
  else if(m[0][1]=='x' && m[1][1]=='x' && m[2][1]=='x'){
     vbra++; //2 colonna  bra
     azzera(m);
   }
  else if(m[0][2]=='x' && m[1][2]=='x' && m[2][2]=='x'){
     vbra++; //3 colonna  bra
     azzera(m);
   }
  else if(m[0][0]=='x' && m[1][1]=='x' && m[2][2]=='x'){
     vbra++; //1 diag bra
     azzera(m);
   }
  else if(m[0][2]=='x' && m[1][1]=='x' && m[2][0]=='x'){
     vbra++; //2 diag bra
     azzera(m);
   }

  else if(m[0][0]=='o' && m[0][1]=='o' && m[0][2]=='o'){
     vcar++; //1 riga car
     azzera(m);
   }
  else if(m[1][0]=='o' && m[1][1]=='o' && m[1][2]=='o'){
     vcar++; //2 riga car
     stampa(m);
     azzera(m);
   }
  else if(m[2][0]=='o' && m[2][1]=='o' && m[2][2]=='o'){
     vcar++; //3 riga car
     azzera(m);
   }
  else if(m[0][0]=='o' && m[1][0]=='o' && m[2][0]=='o'){
     vcar++; //1 colonna  car
     azzera(m);
   }
  else if(m[0][1]=='o' && m[1][1]=='o' && m[2][1]=='o'){
     vcar++; //2 colonna  car
     azzera(m);
   }
  else if(m[0][2]=='o' && m[1][2]=='o' && m[2][2]=='o'){
     vcar++; //3 colonna  car
     azzera(m);
   }
  else if(m[0][0]=='o' && m[1][1]=='o' && m[2][2]=='o'){
     vcar++; //1 diag car
     azzera(m);
   }
  else if(m[0][2]=='o' && m[1][1]=='o' && m[2][0]=='o'){
     vcar++; //2 diag car
     azzera(m);
   }
}

void inserisci(char m[][3], int i, int j){
  if(m[i][j] == ' '){
    if(brancata) m[i][j]='x';
    else m[i][j]='o';
    brancata = !brancata;
    checkvittoria(m);
  }
  else{
    azzera(m);
    inserisci(m, i, j);
  }
}


int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	unsigned short n;
  char m[3][3];
  string temp;
	while(getline(infile, line)){
		istringstream iss(line);
    azzera(m);
    vbra = 0; vcar = 0;
		iss >> n;
		while(!iss.eof()){
      iss >> temp;
      inserisci(m, (temp[1] - '0'), (temp[3] - '0')); << vbra << " " << vcar << "\n";
	}
	return 0;
}
