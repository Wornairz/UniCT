#include <iostream>
#include <fstream>

using namespace std;

class Arco{
    public:
        int da, a, peso;
};

    int n, m;
    int * nodi;
    Arco * archi;

int getIndex(int val){
   for(int i=0; i<n; i++){
       if(nodi[i] == val)
        return i;
   } 
   return -1;
}

int getMin(int * array, int n, bool * check){
    int min = 1000000001;
    int index = 0;
    for(int i=0; i<n; i++){
        if(array[i] < min && !check[i]){ //minimo tra i non visitati
            min = array[i];
            index = i;
        }
    }
    if(min != 1000000001)
        return index;
    else
        return -1;
}

Arco * archi_uscenti(Arco * archi, int m, int &cont, int da){
    cont = 0;
    Arco * archi_usc = new Arco[m];
    for(int i=0; i<m; i++){
        if(getIndex(archi[i].da) == da)
            archi_usc[cont++] = archi[i];
    }
    return archi_usc;
}

int dijkstra(int s, int d){
    int pesi[n];
    bool visitati[n];
    for(int i=0; i<n; i++){
        pesi[i] = 1000000000;
        visitati[i] = false;
    }
    pesi[getIndex(s)] = 0;

    int min = getMin(pesi, n, visitati);
    while(min != -1){
        visitati[min] = true;
        int n_archi_usc = 0;
        Arco * archi_usc = archi_uscenti(archi, m, n_archi_usc, min);
        for(int i=0; i<n_archi_usc; i++){
            if(pesi[getIndex(archi_usc[i].a)] > pesi[getIndex(archi_usc[i].da)] + archi_usc[i].peso)
                pesi[getIndex(archi_usc[i].a)] = pesi[getIndex(archi_usc[i].da)] + archi_usc[i].peso;
        }
        min = getMin(pesi, n, visitati);
    }

    return pesi[getIndex(d)];
}

int main(){
    ifstream input("input.txt");
    ofstream output("output.txt");

    string temp, tipo;
    int s, d;

    for(int j=0; j<100; j++){
        input >> temp;
        n = stoi(temp);
        input >> temp;
        m = stoi(temp);
        input >> tipo;

        nodi = new int[n];
        archi = new Arco[m];
        for(int i = 0; i<n; i++){
            input >> temp;
            nodi[i] = stoi(temp);
        }

        for(int i = 0; i<m; i++){
            if(tipo == "int"){
                input >> temp;
                archi[i].da = stoi(temp.substr(1));
                input >> temp;
                archi[i].a = stoi(temp);
                input >> temp;
                archi[i].peso = stoi(temp.substr(0, temp.length()-1));
            }
            else{
                double tmp;
                input >> temp;
                tmp = stod(temp.substr(1));
                archi[i].da = tmp*10;
                input >> temp;
                tmp = stod(temp);
                archi[i].a = tmp*10;
                input >> temp;
                tmp = stod(temp.substr(0, temp.length()-1));
                archi[i].peso = tmp*10;
            }
        }

        if(tipo == "int"){
            input >> temp;
            s = stoi(temp);
            input >> temp;
            d = stoi(temp);
        }
        else{
            double tmp;
            input >> temp;
            tmp = stod(temp);
            s = tmp*10;
            input >> temp;
            tmp = stod(temp);
            d = tmp*10;
        }

        int res = dijkstra(s, d);
        if(res != 1000000000)
            output << res << endl;
        else
            output << "inf." << endl;
    }
    return 0;
}