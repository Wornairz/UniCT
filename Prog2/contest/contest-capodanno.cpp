#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

unsigned short caunter = 0;
unsigned short n, t;
int maxsomma;
class Orario
{
  public:
    unsigned short inizio, durata, fine;
    Orario() {}
    Orario(unsigned short i, unsigned short f)
    {
        inizio = i;
        durata = f;
        fine = inizio + durata;
    }
};

Orario *orario;
Orario *Adelina;

void stampa(Orario *orario, unsigned short n)
{
    for (short i = 0; i < n; i++)
    {
        cout << orario[i].inizio << " " << orario[i].durata << " " << orario[i].fine << " ";
        cout << "\n";
    }
    cout << "\n";
}

void ordina(Orario *orario, unsigned short n)
{
    for (short i = 0; i < n - 1; i++)
    {
        for (short j = i + 1; j < n; j++)
        {
            if (orario[j].inizio < orario[i].inizio)
            {
                Orario temp = orario[j];
                orario[j] = orario[i];
                orario[i] = temp;
            }
            else if (orario[j].inizio == orario[i].inizio && orario[j].fine < orario[i].fine)
            {
                Orario temp = orario[j];
                orario[j] = orario[i];
                orario[i] = temp;
            }
        }
    }
}

int mintempo2(int indice)
{
    int somma = 0;
    int fineprec = 0;
    bool una = true;
    for (int i = indice; i < n; i++)
    {
        if (una && orario[i].inizio == Adelina->inizio && orario[i].durata == Adelina->durata && orario[i].fine == Adelina->fine)
        {
            una = false;
            somma += Adelina->durata;
            fineprec = Adelina->fine;
        }
        else if (una && orario[i].fine > Adelina->inizio)
        {
            continue;
        }
        else
        {
            if (orario[i].inizio >= fineprec)
            {
                fineprec = orario[i].fine;
                somma += orario[i].durata;
            }
        }
        //cout << somma << endl;
    }
    return t - somma;
}

int mass(int i1, int i2){
    if(i1>i2)
        return i1;
    else
        return i2;
}

void mintempo(int i, int somma, int fineprec, bool una)
{
    if(i >= n){
        if(somma>maxsomma)
            maxsomma = somma;
        return;
    }
    if (una && orario[i].inizio == Adelina->inizio && orario[i].durata == Adelina->durata && orario[i].fine == Adelina->fine)
    {
        una = false;
        somma += Adelina->durata;
        fineprec = Adelina->fine;
    }
    else if(una && orario[i].fine > Adelina->inizio){
        somma=0;
    }
    else
    {
        if (orario[i].inizio >= fineprec)
        {
            fineprec = orario[i].fine;
            somma += orario[i].durata;
        }
    }
    mintempo(i+1, somma, fineprec, una);
    mintempo(i+2, somma, fineprec, una);
    mintempo(i+3, somma, fineprec, una);
    mintempo(i+4, somma, fineprec, una);
    mintempo(i+5, somma, fineprec, una);
    mintempo(i+6, somma, fineprec, una);
    return;
}

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    string line;
    unsigned short i, d;
    while (getline(infile, line))
    {
        istringstream iss(line);
        caunter++;
        iss >> n;
        iss >> t;
        orario = new Orario[n];
        iss >> i;
        iss >> d;
        Adelina = new Orario(i, d);
        orario[0] = Orario(i, d);
        for (int j = 1; j < n; j++)
        {
            iss >> i;
            iss >> d;
            orario[j] = Orario(i, d);
        }
        ordina(orario, n);
        //stampa(orario, n);
        maxsomma = 0;
        mintempo(0,0,0, true);
        mintempo(1,0,0, true);
        mintempo(2,0,0, true);
        mintempo(3,0,0, true);
        mintempo(4,0,0, true);
        mintempo(5,0,0, true);
        outfile << t-maxsomma << "\n";
        delete orario;
    }
    return 0;
}
