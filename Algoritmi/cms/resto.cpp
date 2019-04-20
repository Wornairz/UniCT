#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

int resto(int * monete, int n, int resto){
	int * r = new int[resto+1];
	r[0] = 0;
	for(int i=1; i<=resto; i++){
		int q = INT_MAX;
		for(int j=0; j<n; j++){
			if(i-monete[j]>=0 && r[i-monete[j]]!=INT_MAX)
				q = min(q, r[i-monete[j]]+1);
		}
		r[i] = q;
	}
	return r[resto];
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string line;
    int r, n;
    int * monete;
    while(getline(input, line)) {
        istringstream iss(line);
        iss >> r;
        iss >> n;
        monete = new int[n];
        for(int i=0; i<n; i++) {
            iss >> monete[i];
        }
		output << resto(monete, n, r) << "\n";
    }
    return 0;
}
