#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

short *vett;
unsigned int maxdist = 0, caunter=0;

class Orario
{
public:
  unsigned short inizio, fine;
  Orario() {}
  Orario(unsigned short i, unsigned short f)
  {
    inizio = i;
    fine = f;
  }
};

void stampa(Orario *orario, unsigned short n)
{
  for (short i = 0; i < n; i++)
  {
    cout << orario[i].inizio << " " << orario[i].fine << " ";
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

bool maxmindist(Orario *orario, unsigned short n)
{
  for (int i = 1; i < n; i++)
  {
    if (orario[i].inizio >= vett[i - 1] + maxdist)
      vett[i] = orario[i].inizio;
    else if (vett[i - 1] + maxdist > orario[i].fine)
      return false;
    else
    {
      for (int j = 0; j <= abs(orario[i].fine - orario[i].inizio); j++)
      {
        if (orario[i].inizio + j >= vett[i - 1] + maxdist)
        {
          vett[i] = orario[i].inizio + j;
          break;
        }
      }
    }
  }
  return true;
}

int main()
{
  ifstream infile("input.txt");
  ofstream outfile("output.txt");
  string line;
  Orario *orario;
  bool una;
  unsigned short n, i, f;
  while (getline(infile, line))
  {
    istringstream iss(line);
    caunter++;
    iss >> n;
    orario = new Orario[n];
    vett = new short[n];
    una=true;
    for (int j = 0; j < n; j++)
    {
      iss >> i;
      iss >> f;
      if (abs(f - i) > maxdist)
        maxdist = f - i;
      orario[j] = Orario(i, f);
    }
    ordina(orario, n);
    //stampa(orario, n);
    while (maxdist > 0)
    {
      vett[0] = orario[0].inizio;
      if (maxmindist(orario, n)){
        break;
      }
      maxdist--;
    }
    for (int i = 0; i < n; i++)
    {
      outfile << vett[i] << " ";
    }
    outfile << "\n";
    delete orario;
    delete vett;
  }
  return 0;
}
