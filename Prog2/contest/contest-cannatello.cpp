#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

unsigned short caunter;
unsigned int n, m, k;
short bestpath;
short *peso;
time_t inizio;
bool **strade;
unsigned short *pasticcerie;

void stampastrade()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << strade[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void percorso(unsigned short linea, const unsigned short dest, unsigned short somma)
{
    peso[linea] = somma;
    if (linea == dest)
        return;
    else
        for (int i = 0; i < n; i++)
            if (strade[linea][i] == true && (peso[i] == -1 || somma + 1 < peso[i]))
                percorso(i, dest, somma + 1);
}

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    string line;
    int tmp1, tmp2;
    while (getline(infile, line))
    {
        cout << "riga = " << ++caunter << "\n";
        istringstream iss(line);
        iss >> n;
        iss >> m;
        iss >> k;
        strade = new bool *[n];
        bestpath = -1;
        peso = new short[n];
        pasticcerie = new unsigned short[k];
        for (int i = 0; i < n; i++)
        {
            strade[i] = new bool[n];
            peso[i] = -1;
            for (int j = 0; j < n; j++)
                strade[i][j] = false;
        }
        for (int i = 0; i < k; i++)
        {
            iss >> pasticcerie[i];
            pasticcerie[i]--;
        }
        for (int i = 0; i < m; i++)
        {
            iss >> tmp1;
            iss >> tmp2;
            strade[tmp1 - 1][tmp2 - 1] = true;
            strade[tmp2 - 1][tmp1 - 1] = true;
        }
        time(&inizio);
        //stampastrade();
        for (int i = 0; i < k; i++)
        {
            for (int i = 0; i < n; i++)
                peso[i] = -1;
            percorso(0, pasticcerie[i], 0);
            tmp1 = peso[pasticcerie[i]];
            if (tmp1 == -1)
                continue;
            for (int i = 0; i < n; i++)
                peso[i] = -1;
            percorso(pasticcerie[i], n - 1, tmp1);
            if (peso[n - 1] == -1)
                continue;
            if (peso[n - 1] < bestpath || bestpath == -1)
                bestpath = peso[n - 1];
        }
        outfile << bestpath << "\n";
        delete[] peso;
        delete[] pasticcerie;
        for (int i = 0; i < n; i++)
            delete[] strade[i];
        delete[] strade;
        outfile.flush();
    }
    return 0;
}
