#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Cofanetto{
public:
  unsigned short A, B, C;
  Cofanetto(){}
  Cofanetto(unsigned short A,unsigned short B, unsigned short C){
    this->A=A;
    this->B=B;
    this->C=C;
  }
  bool operator >(const Cofanetto& cofanetto){
    if(this->A > cofanetto.A && this->B > cofanetto.B && this->C > cofanetto.C) return true;
    else return false;
  }
  bool operator <(const Cofanetto& cofanetto){
    if(this->A < cofanetto.A && this->B < cofanetto.B && this->C < cofanetto.C) return true;
    else return false;
  }
  bool operator !=(const Cofanetto& cofanetto){
    if(this->A != cofanetto.A || this->B != cofanetto.B != this->C < cofanetto.C) return true;
    else return false;
  }
};

int ncof(Cofanetto* cofanetti, unsigned short n, int dis){
  int max=0, temp;
  for(short i=dis; i<n; i++){
    temp=0;
    if(cofanetti[dis]>cofanetti[i]) temp = 1 + ncof(cofanetti, n, i);
    if(temp>max) max = temp;
  }
  return max;
}

void stampa(Cofanetto* cofanetti, unsigned short n){
  for(short i=0; i<n; i++){
    cout << cofanetti[i].A << " " << cofanetti[i].B << " " << cofanetti[i].C << " ";
    cout << "\n";
  }
  cout << "\n";
}

void ordina(Cofanetto* cofanetti, unsigned short n){
  for(short i=0; i<n-1; i++){
    for(short j=i+1; j<n; j++){
      if(cofanetti[j].A + cofanetti[j].B + cofanetti[j].C > cofanetti[i].A + cofanetti[i].B + cofanetti[i].C){
        Cofanetto temp = cofanetti[j];
        cofanetti[j] = cofanetti[i];
        cofanetti[i] = temp;
      }
    }
  }
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
  Cofanetto* cofanetti;
	unsigned short n, a, b, c;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n;
    cofanetti = new Cofanetto[n];
		for(int i=0; i<n; i++){
      iss >> a; iss >> b; iss >> c;
      cofanetti[i] = Cofanetto(a, b, c);
		}
    ordina(cofanetti, n);
    stampa(cofanetti, n);
    int max = 1+ncof(cofanetti, n, 0);
    for(int i=1; i<7; i++){
      int tmp = 1+ncof(cofanetti, n, i);
      if(tmp>max) max=tmp;
    }
		outfile << max << "\n";
    delete cofanetti;
	}
	return 0;
}
