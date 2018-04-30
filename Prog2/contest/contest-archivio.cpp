#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

bool ordinato(int *vett, unsigned short dim)
{
    for (int i = 0; i < dim-1; i++)
    {
        if (vett[i + 1] < vett[i])
            return false;
    }
    return true;
}

void stampa(int *vett, unsigned short dim)
{
    for (int i = 0; i < dim; i++)
    {
        cout << vett[i] << " ";
    }
    cout << endl;
}

int minconsult(int *vett, unsigned short n)
{
    unsigned short consult = 0;
    while (!ordinato(vett, n))
    {

        //stampa(vett, n);
        for (int i = 1; i < n - 1; i++)
        {
            if (vett[i - 1] > vett[i + 1])
            { //oppure se i-1 > i+1
                int temp = vett[i + 1];
                vett[i + 1] = vett[i-1];
                vett[i-1] = temp;
                consult++;
            }
        }
    }
    return consult;
}

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    string line;
    unsigned short n;
    int *vett;
    while (getline(infile, line))
    {
        istringstream iss(line);
        iss >> n;
        vett = new int[n];
        for (int i = 0; i < n; i++)
        {
            iss >> vett[i];
        }
        //stampa(vett, n);
        outfile << minconsult(vett, n) << "\n";
    }
    return 0;
}
