#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

unsigned short caunter;
unsigned int n, m;
short *peso;
time_t inizio;

class Strada
{
  public:
    int i, f;
    Strada(int i, int f)
    {
        this->i = i;
        this->f = f;
    }
    Strada()
    {
        i = f = -1;
    }
    bool percorribile(int tempo)
    {
        if (tempo >= i && tempo < f)
            return true;
        else
            return false;
    }
};

Strada **strade;

void stampastrade()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (strade[i][j].i == 0 && strade[i][j].f == 0)
                cout << "0";
            else
                cout << "1";
        }
        cout << endl;
    }
    cout << endl;
}

void funzione(unsigned short linea, unsigned short somma)
{
    //cout << "somma = " << somma << " | linea = " << linea << endl;
    if (abs(difftime(inizio, time(0))) > 20)
        exit(0);
    if (somma < peso[linea])
        peso[linea] = somma;
    else if (peso[linea] < somma)
        return;
    if (linea == n - 1)
        return;
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (strade[linea][i].i != -1 && strade[linea][i].f != -1)
            {
                if (strade[linea][i].percorribile(somma))
                {
                    if(somma+1<peso[i])
                        funzione(i, somma + 1);
                }
                else if(somma<strade[linea][i].f && somma + abs(strade[linea][i].i-somma)<peso[i])
                {
                    funzione(i, somma + abs(strade[linea][i].i-somma)+1);
                }
            }
        }
    }
}

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    string line;
    unsigned int tmp1, tmp2, tmp3, tmp4;
    while (getline(infile, line))
    {
        cout << "riga = " << ++caunter << "\n";
        istringstream iss(line);
        iss >> n;
        iss >> m;
        strade = new Strada *[n];
        peso = new short[n];
        for (int i = 0; i < n; i++)
        {
            strade[i] = new Strada[n];
            peso[i] = 1000;
            for (int j = 0; j < n; j++)
            {
                strade[i][j] = Strada();
            }
        }
        for (int i = 0; i < m; i++)
        {
            iss >> tmp1;
            iss >> tmp2;
            iss >> tmp3;
            iss >> tmp4;
            strade[tmp1][tmp2] = Strada(tmp3, tmp4);
            strade[tmp2][tmp1] = Strada(tmp3, tmp4);
        }
        time(&inizio);
        //stampastrade();
        funzione(0, 0);
        if(peso[n-1]==1000)
            outfile << "-1";
        else
            outfile << peso[n-1];
        outfile << "\n";
        outfile.flush();
    }
    return 0;
}