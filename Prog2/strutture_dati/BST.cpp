#include <iostream>
#include <queue>

using namespace std;

template <class T>
class Nodo
{
public:
    Nodo()
    {
        padre = fdx = fsx = NULL;
    }
    Nodo(Nodo *padre)
    {
        this->padre = padre;
    }
    Nodo(Nodo *padre, Nodo *figlio, bool destro)
    {
        this->padre = padre;
        if (destro)
            fdx = figlio;
        else
            fsx = figlio;
    }
    Nodo(Nodo *padre, Nodo *fdx, Nodo *fsx)
    {
        this->padre = padre;
        this->fdx = fdx;
        this->fsx = fsx;
    }
    Nodo(T valore)
    {
        padre = fdx = fsx = NULL;
        this->valore = valore;
    }
    Nodo *getPadre()
    {
        return padre;
    }
    Nodo *getFDX()
    {
        return fdx;
    }
    Nodo *getFSX()
    {
        return fsx;
    }
    T getValore()
    {
        return valore;
    }
    void setPadre(Nodo *padre)
    {
        this->padre = padre;
    }
    void setFDX(Nodo *fdx)
    {
        this->fdx = fdx;
    }
    void setFSX(Nodo *fsx)
    {
        this->fsx = fsx;
    }
    void setValore(T valore)
    {
        this->valore = valore;
    }

private:
    T valore;
    Nodo *padre;
    Nodo *fdx;
    Nodo *fsx;
};

template <class T>
class Albero
{
public:
    Albero()
    {
        root = NULL;
    }
    Albero(T valore)
    {
        root = new Nodo<T>(valore);
    }
    Nodo<T> *getRoot()
    {
        return root;
    }
    Albero *inserisci(T valore)
    {
        Nodo<T> *nodo = new Nodo<T>(valore);
        return ins_ric(root, nodo);
    }
    void stampa(Nodo<T> *p = nullptr)
    {
        if(!p) p = root;
        visitaInOrder(p);
        cout << endl;
    }
    Albero *cancella(T valore)
    {
        Nodo<T> *nodo = search(valore);
        if (nodo != NULL)
            return cancellaNodo(nodo);
    }
    void naturalFill(Nodo<T> * p, queue<T> & q)
    {
        if(p != NULL)
        {
            naturalFill(p->getFSX(), q);
            p->setValore(q.front()); q.pop();
            naturalFill(p->getFDX(), q);
        }
    }
    int getAltezza()
    {
        return calcolaAltezza(root);
    }

private:
    Nodo<T> *root;
    void visitaInOrder(Nodo<T> *p)
    {
        if (p != NULL)
        {
            //Visita InOrder
            visitaInOrder(p->getFSX());
            cout << p->getValore() << " ";
            visitaInOrder(p->getFDX());
        }
        return;
    }
    Albero *ins_ric(Nodo<T> *nodo, Nodo<T> *nuovo)
    {
        if(root == NULL)
        {
            root = nuovo;
            return this;
        }
        if(nuovo->getValore() < nodo->getValore())
        {
            if(nodo->getFSX() == NULL)
            {
                nuovo->setPadre(nodo);
                nodo->setFSX(nuovo);
                return this;
            }
            else
                nodo = nodo->getFSX();
        }
        else
        {
            if(nodo->getFDX() == NULL)
            {
                nuovo->setPadre(nodo);
                nodo->setFDX(nuovo);
                return this;
            }
            else
                nodo = nodo->getFDX();
        }
        return ins_ric(nodo, nuovo);
    }
    Albero *inserisci(Nodo<T> *nodo)
    {
        Nodo<T> *prec = NULL;
        for (Nodo<T> *i = root; i != NULL;)
        {
            prec = i;
            if (nodo->getValore() < i->getValore())
                i = i->getFSX();
            else
                i = i->getFDX();
        }
        nodo->setPadre(prec);
        if (prec == NULL)
            root = nodo;
        else if (nodo->getValore() < prec->getValore())
            prec->setFSX(nodo);
        else
            prec->setFDX(nodo);
        return this;
    }
    Albero *cancellaNodo(Nodo<T> *nodo)
    {
        //if ed elseif -> massimo 1 figlio
        if (nodo->getFSX() == NULL) //se non ha figlio sinistro, trapiantiamo con il destro indipendetemente se sia NULL o meno
            trapianta(nodo->getFDX(), nodo);
        else if (nodo->getFDX() == NULL) //se non ha figlio destro, come sopra ma con il figlio sinistro
            trapianta(nodo->getFSX(), nodo);
        else
        {
            //2 figli
            Nodo<T> *succ = successore(nodo); //sarà il minimo del sottoalbero destro di nodo
            //troviamo il successore e lo togliamo dalla sua posizione originale
            if (succ->getPadre() != nodo)
            {
                trapianta(succ->getFDX(), succ);
                nodo->getFDX()->setPadre(succ);
                succ->setFDX(nodo->getFDX());
            }
            trapianta(succ, nodo);
            nodo->getFSX()->setPadre(succ);
            succ->setFSX(nodo->getFSX());
        }
        delete nodo;
        return this;
    }
    int calcolaAltezza(Nodo<T> *nodo)
    {
        if (nodo != NULL)
            return 1 + (max(calcolaAltezza(nodo->getFDX()), calcolaAltezza(nodo->getFSX())));
        else
            return 0;
    }
    int max(int a, int b)
    {
        if (a > b)
            return a;
        else
            return b;
    }
    Nodo<T> *search(T valore)
    {
        for (Nodo<T> *i = root; i != NULL;)
        {
            if (i->getValore() == valore)
                return i;
            else if (valore < i->getValore())
                i = i->getFSX();
            else
                i = i->getFDX();
        }
        return NULL;
    }
    void trapianta(Nodo<T> *v, Nodo<T> *u)
    {
        //trapianta v in u
        if (u->getPadre() == NULL)
            root = v;
        else if (u->getPadre()->getFDX() == u)
            u->getPadre()->setFDX(v);
        else
            u->getPadre()->setFSX(v);
        if (v != NULL)
            v->setPadre(u->getPadre());
    }

    Nodo<T> *successore(Nodo<T> *nodo)
    {
        if (nodo->getFDX() != NULL)
            return minimo(nodo->getFDX());
        else
        {
            Nodo<T> *i;
            for (i = nodo->getPadre(); i != NULL && nodo == i->getFDX(); nodo = i, i = i->getPadre())
                ;
            /*Nodo<T> *i = nodo->getPadre();
            while (i != NULL && nodo == i->getFDX())
            {
                nodo = i;
                i = i->getPadre();
            }*/
            return i;
        }
    }
    Nodo<T> *minimo(Nodo<T> *nodo)
    {
        Nodo<T> *prec = nodo;
        for (Nodo<T> *i = nodo; i != NULL; i = i->getFSX())
            prec = i;
        return prec;
    }
};

int main()
{
    Albero<int> *tree = new Albero<int>();
    tree->inserisci(10)->inserisci(3)->inserisci(12)->inserisci(-23)->inserisci(15);
    queue<int> coda;
    coda.push(1); coda.push(2); coda.push(4); coda.push(9); coda.push(15);
    tree->naturalFill(tree->getRoot(), coda);
    tree->stampa();
    return 0;
}
