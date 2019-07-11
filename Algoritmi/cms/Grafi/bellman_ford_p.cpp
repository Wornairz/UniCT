#include <iostream>
#include <fstream>

using namespace std;

class Arco{
    public:
        int da, a, peso;
};

//inutile, ho scoperto dopo che i nodi vanno da 0 a N-1 =(
int * find_nodi(Arco * archi, int m, int n){
    int * nodi = new int[n];
    int count = 0;
    for(int i=0; i<m && count<n; i++){
        int da = archi[i].da;
        int a = archi[i].a;
        bool n_da = true;
        bool n_a = true;
        for(int j=0; j<count; j++){
            if(nodi[j] == da)
                n_da = false;
            if(nodi[j] == a)
                n_a = false;
        }
        if(n_da)
            nodi[count++] = da;
        if(n_a)
            nodi[count++] = a;
    }
    return nodi;
}

int bellman_ford_p(int * pesi, int n, Arco * archi, int m, int s, int d, int k){
    for(int i=0; i<n; i++){
        pesi[i] = 1000000000;
    }
    pesi[s] = 0;
    for(int i=0; i<k; i++){
        for(int j=0; j<m; j++){
            //relax
            if(pesi[archi[j].a] > pesi[archi[j].da] + archi[j].peso)
                pesi[archi[j].a] = pesi[archi[j].da] + archi[j].peso;
        }
    }
    return(pesi[d]);
}

int main(){
    ifstream input("input.txt");
    ofstream output("output.txt");

    string temp;
    int n, m, k;
    Arco * archi;
    int * nodi;
    int s, d;

    for(int j=0; j<100; j++){
        input >> temp;
        n = stoi(temp);
        input >> temp;
        m = stoi(temp);
        input >> temp;
        k = stoi(temp);

        archi = new Arco[m];
        nodi = new int[n];

        for(int i=0; i<m; i++){
            input >> temp;
            archi[i].da = stoi(temp.substr(1));
            input >> temp;
            archi[i].a = stoi(temp);
            input >> temp;
            archi[i].peso = stoi(temp.substr(0, temp.length()-1));
        }

        input >> temp;
        s = stoi(temp);
        input >> temp;
        d = stoi(temp);

        int res = bellman_ford_p(nodi, n, archi, m, s, d, k);
        if(res == 1000000000)
            output << "inf." << endl;
        else
            output << res << endl;
    }
}