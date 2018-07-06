#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template <class T>
class Graph
{
  public:
    Graph()
    {
        n = curr = 0;
        direzionato = false;
    }
    Graph(int n, bool direzionato = false)
    {
        curr = 0;
        this->n = n;
        mad = new bool *[n];
        for (int i = 0; i < n; i++)
        {
            mad[i] = new bool[n]();
        }
        array = new int[n];
        this->direzionato = direzionato;
    }
    void setDim(int n)
    {
        for (int i = 0; i < this->n; i++)
        {
            delete mad[i];
        }
        delete[] mad;
        delete array;
        this->n = n;
        mad = new bool *[n];
        for (int i = 0; i < n; i++)
        {
            mad[i] = new bool[n]();
        }
        array = new int[n];
        curr = 0;
    }
    Graph<T> *inserisciArco(T val1, T val2)
    {
        int index1 = findIndex(val1);
        int index2 = findIndex(val2);
        if (!(index1 == -1 || index2 == -1)) //se entrambi i valori sono presenti nell'array
        {
            mad[index1][index2] = true;
            if (!direzionato)
                mad[index2][index1] = true;
        }
        return this;
    }
    Graph<T> *inserisciNodo(T val)
    {
        if (curr < n)
            array[curr++] = val;
        return this;
    }
    Graph<T> *deleteArco(T val1, T val2)
    {
        int index1 = findIndex(val1);
        int index2 = findIndex(val2);

        if (!(index1 == -1 || index2 == -1)) //se entrambi i valori sono presenti nell'array
        {
            mad[index1][index2] = false;
            if (!direzionato)
                mad[index2][index1] = false;
        }
        return this;
    }
    Graph<T> *deleteNodo(T val)
    {
        cout << "In costruzione" << endl;
        return this;
    }
    void topologicalSort()
    {
        if(DFS()) //ha cicli
            cout << "Impossibile ordinare, rilevati cicli" << endl;
        else{
            while(!pila.empty()){
                int index = pila.top();
                pila.pop();
                cout << array[index] << " ";
            }
            cout << endl;
        }
    }
    void camminoMinimo(T source, T dest)
    {
        int indexSource = findIndex(source);
        int indexDest = findIndex(dest);
        BFS(indexSource);
        cout << "Il camminimo minimo e': " << array[indexDest] << "<-";
        while (pred[indexDest] != -1)
        {
            cout << array[pred[indexDest]] << "<-";
            indexDest = pred[indexDest];
        }
        cout << "\b\b" << endl;
    }
    void stampa()
    {
        for (int i = 0; i < curr; i++)
        {
            cout << "Elemento " << array[i] << "\t Collegamenti : ";
            for (int j = 0; j < curr; j++)
            {
                if (mad[i][j])
                    cout << array[j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

  private:
    bool **mad;
    T *array;
    bool direzionato;
    int n, curr; // n è la dimensione dell'array, curr è il numero attuale di elementi
    enum Color
    {
        white,
        grey,
        black
    };
    Color *color;
    int *dist, *pred;
    int *d, *f, time;
    stack<int> pila;

    int findIndex(T val)
    {
        int index = -1;
        for (int i = 0; i < curr; i++)
        {
            if (array[i] == val)
                index = i;
        }
        return index;
    }
    void BFS(int source)
    {
        queue<int> queue;
        color = new Color[curr](); //alloca e inizializza tutto a white
        pred = new int[curr];
        dist = new int[curr];
        for (int i = 0; i < curr; i++)
            dist[i] = pred[i] = -1;
        dist[source] = 0;
        pred[source] = -1;
        color[source] = Color::grey;
        queue.push(source);
        while (!queue.empty())
        {
            int nodo = queue.front();
            queue.pop();
            for (int i = 0; i < curr; i++)
            {
                if (mad[nodo][i] && color[i] == Color::white)
                {
                    queue.push(i);
                    pred[i] = nodo;
                    dist[i] = dist[nodo] + 1;
                    color[i] = Color::grey;
                }
            }
            color[nodo] = Color::black;
        }
    }
    bool DFS()
    {
        time = 0;
        bool ha_cicli = false;
        color = new Color[curr]();
        d = f = new int[curr]();
        pred = new int[curr];
        for (int i = 0; i < curr; i++)
            pred[i] = -1;

        for (int i = 0; i < curr; i++)
        {
            if (color[i] == Color::white)
                ha_cicli = DFS_visit(i) || ha_cicli;
        }
        return ha_cicli;
    }
    bool DFS_visit(int nodo)
    {
        color[nodo] = Color::grey;
        d[nodo] = ++time;
        bool ha_cicli = false;
        for(int i=0; i<n; i++){
            if(mad[nodo][i] && color[i]==Color::white){
                pred[i] = nodo;
                ha_cicli = DFS_visit(i) || ha_cicli;
            }
            else if(mad[nodo][i] && color[i] == Color::grey){
                ha_cicli = true;
            }
        }
        f[nodo] = ++time;
        pila.push(nodo);
        color[nodo] = Color::black;
        return ha_cicli;    
    }
};

int main()
{
    Graph<int> *grafo = new Graph<int>(5, true);
    grafo->inserisciNodo(5)->inserisciNodo(7)->inserisciNodo(15)->inserisciNodo(18);
    grafo->inserisciNodo(36);
    grafo->inserisciArco(15, 18)->inserisciArco(5, 7)->inserisciArco(15, 36);
    grafo->inserisciArco(5, 36)->inserisciArco(18, 7)->inserisciArco(5, 18);
    grafo->inserisciArco(18, 36);
    grafo->stampa();
    grafo->topologicalSort();
    return 0;
}