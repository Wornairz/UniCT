#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

/*void shifta(int *valori, unsigned short n, int rotaz){
    for(int i=0; i<rotaz; i++){
        int temp = valori[n-1];
        for(int j=n-1; j>0; j--){
            valori[j] = valori[j-1];
        }
        valori[0] = temp;
    }
}*/

void stampa(vector<int> vett, unsigned short dim){
    for(int i=0;i<dim; i++){
        cout << vett[i] << " ";
    }
    cout << endl;
}

int getmin(vector<int> vett, unsigned short inizio, unsigned short fine){
    int min = vett[inizio];
    for(int i=inizio+1; i<fine; i++){
        if(vett[i]<min)
            min = vett[i];
    }
    return min;
}

int getmax(vector<int> vett, unsigned short inizio, unsigned short fine){
    int max = 0;
    for(int i=inizio; i<fine; i++){
        if(vett[i]>max)
            max = vett[i];
    }
    return max;
}

int main(){
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	unsigned short n, q;
    vector<int> valori;
    int tmp;
	while(getline(infile, line)){
		istringstream iss(line);
		iss >> n;
        valori.clear();
		for(int i=0; i<2*n; i++){
            iss >> tmp;
            valori.push_back(tmp);
		}
        //stampa(valori, 2*n);
        iss >> q;
        for(int i=0; i<q; i++){
            iss >> tmp;
            //shifta(valori, 2*n, rotaz[i]);
            rotate(valori.begin(), valori.begin() + valori.size() - (tmp % valori.size()), valori.end());
            //stampa(valori, 2*n);
            outfile << getmin(valori, 0, n) << " ";
            outfile << getmax(valori, n, 2*n) << " ";
        }
        //cout << endl;
		outfile << "\n";
	}
	return 0;
}