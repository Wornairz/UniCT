#include <iostream>

using namespace std;
const int MaxDimCoda = 10;

class Coda
{
  private:
    int vett[MaxDimCoda];
    int testa, fine;
    //int n;
  public:
    Coda()
    {
        testa = -1;
        fine = -1;
        //n = 0;
    }
    void enqueue(int elem)
    {
        if (codaPiena())
            cout << "errore, coda piena" << endl;
        else
        {
            fine = (fine + 1) % MaxDimCoda;
            vett[fine] = x;
            //n++;
            if (codaVuota())
                testa++;
        }
    }
    int dequeue()
    {
        if (codaVuota())
            cout << "errore, coda vuota" << endl;
        else
        {
            int x = vett[testa];
            testa = (testa + 1) % MaxDimCoda;
            //n--;
            if ((testa - 1) % MaxDimCoda == fine) //fare attenzione al % di un numero negativo
                testa = coda = -1;
            return x;
        }
    }
    bool codaVuota()
    {
        //return (n==0 ? true : false);
        return testa == -1;
    }
    bool codaPiena()
    {
        //return (n==MaxDimCoda ? true : false);
        return ((fine + 1) % MaxDimCoda == testa);
    }
    void stampaCoda()
    {

        if (codaVuota())
            cout << "Coda vuota! \n";
        else
        {
            int i = testa, x = 0;
            while ((i % MaxDimCoda) != fine)
            {
                cout << "Posizione " << x << " : " << vett[i % MaxDimCoda] << endl;
                x++;
                i++;
            }
            cout << "Posizione " << x << " : " << vett[fine] << endl;
        }
    }
}

int
main()
{
    Coda coda;
    int x = coda.dequeue();
    for (int i = 0; i < MaxDimCoda; i++)
    {
        coda.enqueue((i + 1) * 10);
    }
    cout << endl;
    coda.stampaCoda();
    for (int i = 0; i < MaxDimCoda; i++)
    {
        coda.dequeue();
    }
    return 0;
}