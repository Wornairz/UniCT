#include <iostream>

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
    Albero(Nodo<T> *nodo)
    {
        root = nodo;
    }
    Nodo<T> *getRoot()
    {
        return root;
    }
    Albero *inserisci(T valore)
    {
        Nodo<T> *nodo = new Nodo<T>(valore);
        return inserisci(nodo);
    }
    void stampa(Nodo<T> *p)
    {
        visitaInOrder(p);
        cout << endl;
    }
    Albero *cancellaNodo(T valore)
    {
        Nodo<T> *nodo = search(valore);
        if (nodo != NULL)
            return cancellaNodo(nodo);
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
        if (nodo->getFSX() == NULL) //se non ha figlio sinistro, trapiantiamo con il destro indipendetemente se sia NULL o meno
            trapianta(nodo, nodo->getFDX());
        else if (nodo->getFDX() == NULL) //se non ha figlio destro, come sopra ma con il figlio sinistro
            trapianta(nodo, nodo->getFSX());
        else
        {
            Nodo<T> *succ = successore(nodo);
            if (succ->getPadre()->getFDX() == succ)
                succ->getPadre()->setFDX(NULL);
            else
                succ->getPadre()->setFSX(NULL);
            succ->setFSX(nodo->getFSX());
            succ->setFDX(nodo->getFDX());
            trapianta(nodo, succ);
        }
        delete nodo;
        return this;
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
    void trapianta(Nodo<T> *u, Nodo<T> *v)
    { //trapianta v in u
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
            Nodo<T> *i = nodo->getPadre();
            //for(i = nodo->getPadre(); i != NULL && nodo == i->getFDX(); nodo = i, i = i->getPadre())
            while (i != NULL && nodo == i->getFDX())
            {
                nodo = i;
                i = i->getPadre();
            }
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
    return 0;
}