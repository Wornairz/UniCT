#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void ordina(unsigned short* v, unsigned short n){
  for(int i=0; i<n-1; i++){
    for(int j=i+1; j<n; j++){
      if(v[i]>v[j]){
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
      }
    }
  }
}
void stampa(unsigned short* v, unsigned short n){
  for(int i=0; i<n; i++){
    cout << v[i] << endl;
  }
}

int mintempo(unsigned short* v, unsigned short n){
  ordina(v, n);
  //stampa(v, n);
  unsigned short min1 = v[0];
  unsigned short min2 = v[1];
  unsigned int somma = (min1+min2);
  int count = 0;
  for(int i=n-1; i>=2; i--){
    if(count==2){
      count=0;
    }
    if(count==0){
       somma+=v[i]+min2;
       i--;
    }
    else if(count==1){
      if(i==2){
        somma+=v[i]+min1;
      }
      else{
        somma+=min1+min2;
        i++;
      }
    }
    count++;
  }
  somma+=min2;
  return somma;
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	unsigned short n;
  unsigned short* vett;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n;
    vett = new unsigned short[n];
		for(int i=0; i<n; i++){
      iss >> vett[i];
		}
		outfile << mintempo(vett, n) << "\n";
	}
	return 0;
}
