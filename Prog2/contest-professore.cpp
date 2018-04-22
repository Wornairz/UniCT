#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> stvett;

string replaceChar(string str, char toReplace, char replacement) {
  for (int i=0; i<str.length(); i++) {
    if (str[i] == toReplace){
       str[i] = replacement;
       break;
     }
  }
  return str;
}

void anagramma(string comb, vector<char> vect){
  if(vect.size()==1){
    stvett.push_back(replaceChar(comb, '*', vect.front()));
  }
  else{
    for(int i=0; i<vect.size(); i++){
      char tmp = vect[i];
      vector<char> tve = vect;
      tve.erase(tve.begin()+i);
      anagramma(replaceChar(comb, '*', tmp), tve);
    }
  }
}

void ordina(vector<string> &vett){
  for(int i=0; i<vett.size()-1; i++){
    for(int j=i+1; j<vett.size(); j++){
      if((vett[i]).compare(vett[j])>0){
        string temp = vett[i];
        vett[i] = vett[j];
        vett[j] = temp;
      }
    }
  }
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	unsigned short n;
  char* fv;
  vector<char> vect;
  string comb;
  char tmp;
	while(getline(infile, line)){
		istringstream iss(line);
    vect.clear();
    stvett.clear();
    fv = new char[n];
		iss >> n;
		for(int i=0; i<n; i++){
      iss >> fv[i];
		}
    iss >> comb;
    for(int i=0; i<n; i++){
      if(comb.find(fv[i]) == std::string::npos) vect.push_back(fv[i]);
    }
    anagramma(comb, vect);
    ordina(stvett);
    for(int i=0; i<stvett.size(); i++){
      outfile << stvett[i] << " ";
    }
		outfile << "\n";
	}
	return 0;
}
