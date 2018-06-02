#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>


using namespace std;

unsigned short caunter;
unsigned int n, m, t;
short *peso;
bool **mad, **rmad;
time_t inizio;

void stampamad(bool **mad)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mad[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void funzione(unsigned short linea, unsigned short somma, bool asp, bool altamarea)
{
    //cout << "somma = " << somma << " | linea = " << linea << endl;
    if(abs(difftime(inizio, time(0)))>40)
        return;
    if (peso[linea] == -1)
        peso[linea] = somma;
    else if(somma < peso[linea])
        peso[linea] = somma;
    else if (peso[linea] < somma && !asp )
        return;
    
    if (somma == t)
    {
        altamarea = true;
    }
    if (linea == n - 1)
        return;
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (!altamarea && mad[linea][i] == true)
            {
                funzione(i, somma + 1, false, altamarea);
            }
            else if (altamarea && rmad[linea][i] == true)
            {
                funzione(i, somma + 1, false, altamarea);
            }
        }
    }
    if (somma < t)
        funzione(linea, somma + 1, true, altamarea);
}

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    string line;
    unsigned int tmp1, tmp2;
    while (getline(infile, line))
    {
        cout << "riga = " << ++caunter << "\n";
        istringstream iss(line);
        iss >> n;
        iss >> m;
        iss >> t;
        mad = new bool *[n];
        rmad = new bool *[n];
        peso = new short[n];
        for (int i = 0; i < n; i++)
        {
            mad[i] = new bool[n];
            rmad[i] = new bool[n];
            peso[i] = -1;
            for (int j = 0; j < n; j++)
            {
                mad[i][j] = false;
                rmad[i][j] = false;
            }
        }
        for (int i = 0; i < m; i++)
        {
            iss >> tmp1;
            iss >> tmp2;
            mad[tmp1][tmp2] = true;
            rmad[tmp2][tmp1] = true;
        }
        //stampamad(mad);
        //stampamad(rmad);
        time(&inizio);
        funzione(0, 0, 0, 0);
        outfile << peso[n - 1] << "\n";
        outfile.flush();
    }
    return 0;
}