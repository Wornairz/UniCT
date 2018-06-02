#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    string line;
    unsigned short n, m;
    int *vett, temp;
    unsigned int somma;
    while (getline(infile, line))
    {
        somma = 0;
        istringstream iss(line);
        iss >> n;
        iss >> m;
        vett = new int[n];
        for (int i = 0; i < n; i++)
        {
            iss >> vett[i];
        }
        for(int i=0; i<m; i++){
            iss >> temp;
            for(int j=0; j<n; j++){
                if(temp == vett[j]){
                    somma += 5;
                    break;
                }
            }
        }
        outfile << somma << "\n";
    }
    return 0;
}
