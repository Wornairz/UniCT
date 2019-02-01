#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>

using namespace std;

ifstream input("input.txt");
ofstream output("output.txt");

class Monomio
{
public:
    int val;
    int grado;
    Monomio* next;
    Monomio() : val(0), grado(0), next(NULL) {}
};

class Lista
{
public:
    Monomio* testa;
    Lista(){
        testa = new Monomio();
    }

    void inserisciMonomio(bool piu, int grado, int numero)
    {
        Monomio* puntatore = testa;
        Monomio* prec = testa;

        //cout << "num = " << numero << " grado = " << grado << " piu = " << piu << endl;

        for(int i=0; i< grado; i++)
        {
            prec = puntatore;
            if(puntatore == NULL)
            {
                puntatore = new Monomio();
                puntatore->grado = i;
                prec->next = puntatore;
            }
            puntatore = puntatore->next;
        }
        puntatore = new Monomio();
        if(piu) puntatore->val += numero;
        else puntatore->val -= numero;
        puntatore->grado = grado;

        //cout << "test" << testa->next << endl;

    }

    void stampa()
    {
        Monomio* puntatore = testa;
        while(puntatore != NULL)
        {
            cout << puntatore->val << "x^" << puntatore->grado << "+";
            puntatore = puntatore->next;
        }
        cout << endl;
    }
};

int main()
{
    string line, temp;
    int n;
    while(getline(input, line))
    {
        istringstream iss(line);
        iss >> n;
        Lista lista = Lista();

        for(int i=0; i<n+n-1; i++)
        {
            bool piufuori = true;
            bool piudentro = true;
            int numero = 0;
            string elevato = "";

            iss >> temp;

            if(temp == "+")
            {
                piufuori=true;
            }
            else if(temp == "-")
            {
                piufuori=false;
            }
            else
            {

                temp.erase(0, 1);
                temp.erase(temp.length()-1, 1);

                cout << "temp = " << temp << "\n";

                //cout << "piuf " << piufuori << "\t";

                for( int j=0; j<temp.length(); j++)
                {
                    if(temp[j] == '+')
                        piudentro=true;
                    else if(temp[j] == '-')
                        piudentro=false;
                    else
                    {
                        //cout << "piud " << piudentro << "\t";
                        int inizio = j;
                        while(temp[j] >= '0' && temp[j] <= '9')
                            j++;

                        numero = stoi(temp.substr(inizio, j));
                        //cout << "numero = " << numero << "\t";

                        if(temp[j] == 'x')
                        {
                            j++;
                            elevato = "1";
                            if(temp[j] == '^')
                            {
                                j++;
                                elevato = "";
                                elevato += temp[j];
                                j++;
                                if(temp[j] >= '0' && temp[j] <= '9')
                                {
                                    elevato += temp[j++];
                                }
                                //cout << "elevato = " << elevato << "\t";
                            }
                            j--;
                        }
                        else
                            elevato = "0";
                    lista.inserisciMonomio((piufuori ? piudentro : !piudentro), stoi(elevato), numero);
                    }

                }
            }
        }
        lista.stampa();
    }

    input.close();
    output.close();
    return 0;
}
