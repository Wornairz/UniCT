#include <iostream>
#include <fstream>

using namespace std;

class Arco{
    public:
        int da, a;
        int peso;
};

int * nodi;
int n, m;
Arco * archi;

int getIndex(int nodo){
    for(int i=0; i<n; i++){
        if(nodi[i] == nodo)
            return i;
    }
    return -1;
}

void relax(Arco arco, int* pesi, int n){
    if(pesi[getIndex(arco.a)] > pesi[getIndex(arco.da)] + arco.peso){
        pesi[getIndex(arco.a)] = pesi[getIndex(arco.da)] + arco.peso;
    }
}

int * bellman_ford(int s, int d){
    int * pesi = new int[n];
    for(int i=0; i<n; i++){
        pesi[i] = 1000000000; //infinito
    }
    pesi[getIndex(s)] = 0; //caso banale s->s
    for(int i=0; i<n-1; i++){
        for(int j=0; j<m; j++){
            relax(archi[j], pesi, n);
        }
    }
    return pesi;
}

bool cicli_negativi(int s, int d, const int * pesi){
    for(int j=0; j<m; j++){
         if(pesi[getIndex(archi[j].a)] > pesi[getIndex(archi[j].da)] + archi[j].peso)
            return true;
    }
    return false;

}

int main(){
    ifstream input("input.txt");
    ofstream output("output.txt");

    string temp, tipo;
    int s, d;
    double tmp;

    for(int j=0; j<100; j++){
        input >> temp;
        n = stoi(temp);
        input >> temp;
        m = stoi(temp);
        input >> tipo;

        nodi = new int[n];
        archi = new Arco[m];

        for(int i=0; i<n; i++){
            input >> temp;
            if(tipo == "double"){
                tmp = stod(temp);
                nodi[i] = tmp*10;
            }
            else
                nodi[i] = stoi(temp);
        }
        for(int i=0; i<m; i++){
            if(tipo == "double"){
                input >> temp;
                tmp = stod(temp.substr(1));
                archi[i].da = tmp*10;
                input >> temp;
                tmp = stod(temp);
                archi[i].a = tmp*10;
            }
            else{
                input >> temp;
                archi[i].da = stoi(temp.substr(1));
                input >> temp;
                archi[i].a = stoi(temp);
            }
            input >> temp;
            archi[i].peso = stoi(temp.substr(0, temp.length()-1));
        }

        if(tipo == "double"){
            input >> temp;
            tmp = stod(temp);
            s = tmp * 10;
            input >> temp;
            tmp = stod(temp);
            d = tmp * 10;
        }
        else{
            input >> temp;
            s = stoi(temp);
            input >> temp;
            d = stoi(temp);
        }
        
        /*for(int i=0; i<n; i++){
            cout << nodi[i] << " ";
        }
        cout << endl;
        for(int i=0; i<m; i++){
            cout << i << ") " << archi[i].da << "->" << archi[i].a << " - p = " << archi[i].peso << endl;
        }
        cout << endl;*/

        int * pesi = bellman_ford(s, d);

        if(pesi[getIndex(d)] == 1000000000)
            output << "inf." << endl;
        else if (cicli_negativi(s, d, pesi))
            output << "undef." << endl;
        else
            output << pesi[getIndex(d)] << endl;
    }
    return 0;
}