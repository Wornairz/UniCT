#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

string swap(string s, int k){
  char temp = s[k];
  s[k] = s[k+1];
  s[k+1] = temp;
  return s;
}

bool cercascambi(string cercare, string stringa, int k){
  if(cercare == stringa) return true;
  else if(k>=cercare.length()) return false;
  else{
    for(int i=k; i<cercare.length()-1; i++){
      return (cercascambi(cercare, swap(stringa, i), i+2) || cercascambi(cercare, stringa, i+1));
    }
  }
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
  string cercare, testo;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> cercare;
    iss >> testo;
    for(int i=0; i<=(testo.length()-cercare.length()); i++){
      if(cercascambi(cercare, testo.substr(i, cercare.length()), 0)) outfile << i << " ";
    }
		outfile << "\n";
	}
	return 0;
}
