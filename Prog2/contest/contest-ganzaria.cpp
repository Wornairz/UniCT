#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>

using namespace std;

unsigned int caunter=0;
unsigned short n, m;
unsigned short **mat, **aux;
class Punto
{
  public:
    unsigned short x, y;
    Punto(unsigned short x, unsigned short y)
    {
        this->x = x;
        this->y = y;
    }
    Punto()
    {
        x = 0;
        y = 0;
    }
    bool operator==(const Punto &tmp)
    {
        if (tmp.x == this->x && tmp.y == this->y)
            return true;
        else
            return false;
    }
};

Punto A, B;

void stampa(short **mat, unsigned short n, unsigned short m)
{
    cout << endl;
    cout << "Punto A(" << A.x << "," << A.y << ")\t"
         << "Punto B(" << B.x << "," << B.y << ")";
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
int minim(int v[], int dim)
{
    int min = v[0];
    for (int i = 1; i < dim; i++)
    {
        if (v[i] < min)
            min = v[i];
    }
    return min;
}
void findpath(Punto dis, int dislivello)
{
    //stampa(aux, n, m);
    if (aux[dis.x][dis.y] == -1 || aux[dis.x][dis.y] > dislivello)
        aux[dis.x][dis.y] = dislivello;
    else if (aux[dis.x][dis.y] <= dislivello)
        return;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (abs(i) == abs(j))
                continue;
            else
            {
                if (dis.x + i >= 0 && dis.x + i < n && dis.y + j >= 0 && dis.y + j < m)
                {
                    Punto temp(dis.x + i, dis.y + j);
                    if (mat[dis.x + i][dis.y + j] > mat[dis.x][dis.y])
                        findpath(temp, dislivello + mat[dis.x + i][dis.y + j] - mat[dis.x][dis.y]);
                    else
                        findpath(temp, dislivello);
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
    while (getline(infile, line))
    {
        istringstream iss(line);
        iss >> n;
        iss >> m;
        iss >> A.x;
        iss >> A.y;
        iss >> B.x;
        iss >> B.y;
        mat = new unsigned short *[n];
        aux = new unsigned short *[n];
        for (int i = 0; i < n; i++)
        {
            mat[i] = new unsigned short[m];
            aux[i] = new unsigned short[m];
            for (int j = 0; j < m; j++)
            {
                iss >> mat[i][j];
                aux[i][j] = -1;
            }
        }
        //cout << "mat(" << n << "x" << m << ")" << endl;
        //stampa(mat, n, m);
        cout << ++caunter << endl;
        findpath(A, 0);
        //stampa(aux, n, m);
        //cout << " caunter= " << ++caunter << endl;
        outfile << aux[B.x][B.y] << "\n";
    }
    return 0;
}
