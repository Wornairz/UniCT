#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

unsigned short maxocc = 0, caunter = 1;
unsigned short maxinterruzioni = 0, maxsalto = 0, inpiu = 0;
unsigned short n, m;
string stringa;

void checkcaunter()
{
    if (caunter <= 20)
    {
        maxinterruzioni = 0;
        maxsalto = 0;
    }
    else if (caunter > 20 && caunter <= 40)
    {
        maxinterruzioni = 1;
        maxsalto = 4;
    }
    else if (caunter > 40 && caunter <= 60)
    {
        maxinterruzioni = 2;
        maxsalto = 3;
    }
    else
    {
        maxinterruzioni = 3;
        maxsalto = 3;
    }
    inpiu = maxinterruzioni * maxsalto;
}

string controllo(string string1, string string2)
{
    string temp = "";
    /*cout << endl;
    cout << "string1 = " << string1 << "  string2 = " << string2 << endl;*/
    temp += string1[0];
    int occorrenze = 1, lastpos = 0;
    int interr = 0, salto = 0;
    bool bint = false;
    for (unsigned short i = 1; i < string1.length(); i++)
    {
        for (unsigned short j = lastpos + 1; j < (i + maxsalto > i ? i + maxsalto : m); j++)
        {
            //cout << "J= " << j << " I= " << i << " ";
            if (string1[i] == string2[j])
            {
                //cout << " i = " << string1[i] << " j = " << string2[j] << " | ";
                lastpos = j;
                bint = false;
                occorrenze++;
                temp += string1[i];
                break;
            }
            else if (maxinterruzioni > 0)
            {
                if (!bint)
                {
                    bint = true;
                    interr++;
                    if (interr > maxinterruzioni)
                        return "";
                }
                salto++;
                if (salto >= maxsalto)
                {
                    if (interr > maxinterruzioni)
                        return "";
                    else
                        salto = 0;
                }
            }
        }
        //cout << "temp= " << temp << " ";
        if (occorrenze == m)
            return temp;
    }
    return "";
}

string trovastringa()
{
    string canduff = "";
    for (int i = 0; i < n - 1; i++)
    {
        string candtemp = "";
        int occorrenze = 0;
        string temp = stringa.substr(i, m + inpiu);
        for (int j = i + 1; j < n; j++)
        {
            string temp2 = stringa.substr(j, m + inpiu);
            if (temp[0] == temp2[0])
            {
                temp2 = controllo(temp, temp2);
                if (temp2 != "")
                {
                    //cout << "temp2= " << temp2;
                    if (occorrenze == 0)
                        occorrenze++;
                    else if (candtemp == temp2)
                        occorrenze++;
                    candtemp = temp2;
                }
            }
        }
        if (occorrenze > maxocc)
        {
            maxocc = occorrenze;
            canduff = candtemp;
        }
    }
    return canduff;
}

string trovastringa2()
{
    int occorrenze = 0;
    string cand;
    for (int i = 0; i < n - m; i++)
    {
        string strtemp = stringa.substr(i, m);
        unsigned short occtemp = 0;
        for (int j = i; j < n - m; j++)
        {
            string tmp2 = stringa.substr(j, m);
            if (strtemp == tmp2)
                occtemp++;
            else if (strtemp[0] == tmp2[0])
            {
                tmp2 = stringa.substr(j, m + 4);
                unsigned short cont = 1;
                for (int k = 1; k < tmp2.length(); k++)
                {
                    if (tmp2[k] == strtemp[cont])
                        cont++;
                }
                if (cont == strtemp.length())
                    occtemp++;
            }
        }
        if (occtemp > occorrenze)
        {
            occorrenze = occtemp;
            cand = strtemp;
        }
    }
    return cand;
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
        iss >> stringa;
        checkcaunter();
        maxocc = 0;
        /*if (caunter <= 20)
            outfile << trovastringa2(stringa, n, m) << "\n";
        else*/
            outfile << trovastringa() << "\n";
        cout << caunter << endl;
        caunter++;
    }
    return 0;
}