#include <iostream>

using namespace std;

template <class T>
class Nodo
{
  public:
    Nodo()
    {
        prec = succ = NULL;
    }
    Nodo(Nodo *prec, Nodo *succ, T valore)
    {
        this->prec = prec;
        this->succ = succ;
        this->valore = valore;
    }
    Nodo(Nodo *nodo, bool succe = true)
    {
        if (succe)
            succ = nodo;
        else
            prec = nodo;
    }
    Nodo(Nodo *prec, Nodo *succ)
    {
        this->prec = prec;
        this->succ = succ;
    }
    Nodo(T valore)
    {
        prec = succ = NULL;
        this->valore = valore;
    }
    Nodo *getPrec()
    {
        return prec;
    }
    Nodo *getSucc()
    {
        return succ;
    }
    T getValore()
    {
        return valore;
    }
    void setPrec(Nodo *prec)
    {
        this->prec = prec;
    }
    void setSucc(Nodo *succ)
    {
        this->succ = succ;
    }
    void setValore(T valore)
    {
        this->valore = valore;
    }

  private:
    T valore;
    Nodo *prec;
    Nodo *succ;
};

template <class T>
class LList
{
  private:
    Nodo<T> *head;
    LList<T> *inserisciInCoda(Nodo<T> *nodo)
    {
        Nodo<T> *i;
        for (i = head; i->getSucc() != NULL; i = i->getSucc())
            ;
        i->setSucc(nodo);
        nodo->setPrec(i);
        return this;
    }
    LList<T> *inserisciInTesta(Nodo<T> *nodo)
    {
        head->setPrec(nodo);
        nodo->setSucc(head);
        head = nodo;
        return this;
    }
    LList<T> *inserisci(Nodo<T> *nodo, int pos)
    {
        if (pos == 0)
            inserisciInTesta(nodo);
        else
        {
            Nodo<T> *i;
            int j;
            for (i = head, j = 0; i->getSucc() != NULL && j < pos; i = i->getSucc(), j++)
                ;
            i->getPrec()->setSucc(nodo);
            nodo->setPrec(i->getPrec());
            i->setPrec(nodo);
            nodo->setSucc(i);
        }
        return this;
    }

  public:
    LList()
    {
        head = NULL;
    }
    LList(T valore)
    {
        head = new Nodo<T>(valore);
    }
    LList<T> *inserisci(T valore, int pos)
    {
        Nodo<T> *nodo = new Nodo<T>(valore);
        return inserisci(nodo, pos);
    }
    LList<T> *inserisciInCoda(T valore)
    {
        Nodo<T> *nodo = new Nodo<T>(valore);
        return inserisciInCoda(nodo);
    }
    LList<T> *inserisciInTesta(T valore)
    {
        Nodo<T> *nodo = new Nodo<T>(valore);
        return inserisciInTesta(nodo);
    }
    LList<T> *cancellaTesta()
    {
        Nodo<T> *temp = head;
        head = head->getSucc();
        head->setPrec(NULL);
        delete temp;
        return this;
    }
    LList<T> *cancellaCoda()
    {
        Nodo<T> *i;
        for (i = head; i->getSucc() != NULL; i = i->getSucc())
            ;
        i->getPrec()->setSucc(NULL);
        delete i;
        return this;
    }
    LList<T> *cancella(T valore)
    {
        Nodo<T> *i;
        for (i = head; i != NULL && i->getValore() != valore; i = i->getSucc())
            ;
        if (i == head)
            head = head->getSucc();
        else if (i != NULL)
        {
            i->getPrec()->setSucc(i->getSucc());
            i->getSucc()->setPrec(i->getPrec());
        }
        delete i;
        return this;
    }
    void stampa()
    {
        for (Nodo<T> *i = head; i != NULL; i = i->getSucc())
            cout << i->getValore() << " ";
        cout << endl;
    }
};

int main()
{
    return 0;
}