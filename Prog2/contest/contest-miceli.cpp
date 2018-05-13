#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int *vett;
unsigned short n, r, minmo, caunter = 0;
vector<int> sol;
time_t inizio;

void stampa(vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

void ordinadec()
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (vett[j] > vett[i])
            {
                int tmp = vett[j];
                vett[j] = vett[i];
                vett[i] = tmp;
            }
        }
    }
}

void ordinacres()
{
    for (int i = 0; i < sol.size() - 1; i++)
    {
        for (int j = i + 1; j < sol.size(); j++)
        {
            if (sol[j] < sol[i])
            {
                int tmp = sol[j];
                sol[j] = sol[i];
                sol[i] = tmp;
            }
        }
    }
}

void ordinacres(vector<int> &mon_usate)
{
    for (int i = 0; i < mon_usate.size() - 1; i++)
    {
        for (int j = i + 1; j < mon_usate.size(); j++)
        {
            if (mon_usate[j] < mon_usate[i])
            {
                int tmp = mon_usate[j];
                mon_usate[j] = mon_usate[i];
                mon_usate[i] = tmp;
            }
        }
    }
}

void lessicografico(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] < sol[i])
        {
            sol = v;
            break;
        }
        else if (v[i] > sol[i])
            break;
    }
}

void completa(vector<int> mon_usate, int somma, int num_mon_usate)
{
    if (somma > r || num_mon_usate > minmo || abs(difftime(inizio, time(0))) > 10)
        return;
    else if (somma == r)
    {
        if (num_mon_usate > minmo)
            return;
        else if (num_mon_usate < minmo)
        {
            sol = mon_usate;
            minmo = num_mon_usate;
            return;
        }
        else
        {
            ordinacres();
            ordinacres(mon_usate);
            lessicografico(mon_usate);
            return;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            vector<int> tmp(mon_usate);
            tmp.push_back(vett[i]);
            completa(tmp, somma + vett[i], num_mon_usate + 1);
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
        cout << ++caunter << endl;
        istringstream iss(line);
        iss >> n;
        vett = new int[n];
        iss >> r;
        minmo = 15;
        for (int i = 0; i < n; i++)
        {
            iss >> vett[i];
        }
        ordinadec();
        time(&inizio);
        for (int i = 0; i < n; i++)
        {
            int quoz = r / vett[i];
            for (int j = quoz; j > 0; j--)
            {
                if(j>minmo)
                    continue;
                vector<int> temp(j, vett[i]);
                completa(temp, vett[i] * j, j);
            }
        }
        ordinacres();
        for (int i = 0; i < sol.size(); i++)
        {
            outfile << sol[i] << " ";
        }
        outfile.flush();
        outfile << "\n";
    }
    return 0;
}