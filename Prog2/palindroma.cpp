#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool isPalindroma(string stringa){
  unsigned short errori = 0;
  for(int i=0; i<(stringa.length()%2==0 ? stringa.length()/2 : stringa.length()/2+1); i++){
    if(stringa[i]==stringa[stringa.length()-i-1]) continue;
    else errori++;
  }
  if(errori<=1) return true;
  else return false;
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	unsigned short n;
  string stringa;
  vector<string> vett;
	while(getline(infile, line)){
    vett.clear();
		istringstream iss(line);
		iss >> n;
		for(int i=0; i<n; i++){
      iss >> stringa;
      if(isPalindroma(stringa)){
        vett.push_back(stringa);
      }
		}
		outfile << vett.size() << " ";
    for(int i=0; i<vett.size(); i++){
      outfile << vett[i] << " ";
    }
    outfile << "\n";
	}
	return 0;
}
