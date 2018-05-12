#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    string line;
    unsigned short n, m, cont;
    int *vett;
    while (getline(infile, line))
    {
        istringstream iss(line);
        iss >> n;
        iss >> m;
        cont = 0;
        vett = new int[n];
        for (int i = 0; i < n; i++)
        {
            iss >> vett[n-1];
            if(vett[n-1]>m)
                vett[cont++]=vett[n-1];
        }
        outfile << cont << " ";
        for(int i=0; i<cont; i++){
            outfile << vett[i] << " ";
        }
        outfile << "\n";
    }
    return 0;
}