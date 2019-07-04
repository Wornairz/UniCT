#include <iostream>
#include <fstream>

using namespace std;

void ordina(int *a, int n, int *b)
{
    //ordina per tempo di fine crescente
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
            {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                //spostiamo anche i relativi tempi di inizio
                temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (a[i] == a[i + 1] && b[i] > b[i + 1])
        {
            int j = i + 1;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            //spostiamo anche i relativi tempi di inizio
            temp = b[i];
            b[i] = b[j];
            b[j] = temp;
        }
    }
}

int max_tempo(int *inizio, int *fine, int n)
{
    int **m = new int*[n+1];

    for (int i = 0; i <= n; i++)
    {
        m[i] = new int[n+1];
        m[i][i] = 0;
    }

    //nella matrice le righe rappresentano il tempo che scorre e le colonne le varie attività
    for (int tempo = 1; tempo <= fine[n-1]; tempo++)
    {
        for (int i = 1; i <= n; i++)
        {
            if(tempo<fine[i-1]) 
                m[tempo][i] = m[tempo][i-1];
            else
                m[tempo][i] = max( m[tempo][i-1] , m[inizio[i-1]][i-1] + (fine[i-1]-inizio[i-1]));
        }
    }

    return m[fine[n-1]][n];
}

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n;
    int *inizio, *fine;
    for (int j = 0; j < 100; j++)
    {
        input >> n;
        inizio = new int[n];
        fine = new int[n];
        for (int i = 0; i < n; i++)
        {
            string temp;
            input >> temp;
            inizio[i] = stoi(temp.substr(1));
            input >> temp;
            fine[i] = stoi(temp.substr(0, temp.length() - 1));
        }
        ordina(fine, n, inizio);
        ordina(fine, n, inizio);
        output << max_tempo(inizio, fine, n) << endl; 
    }
}