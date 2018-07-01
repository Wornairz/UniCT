#include <iostream>

using namespace std;

template <class T>
class Nodo
{
  public:
    Nodo()
    {
        succ = NULL;
    }
    Nodo(Nodo *succ, T valore)
    {
        this->succ = succ;
        this->valore = valore;
    }
    Nodo(Nodo *succ)
    {
        this->succ = succ;
    }
    Nodo(T valore)
    {
        succ = NULL;
        this->valore = valore;
    }
    Nodo *getSucc()
    {
        return succ;
    }
    T getValore()
    {
        return valore;
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
    Nodo *succ;
};

template <class T>
class List
{
  private:
    Nodo<T> *head;
    List<T> *inserisciInCoda(Nodo<T> *nodo)
    {
        Nodo<T> *i;
        for (i = head; i->getSucc() != NULL; i = i->getSucc())
            ;
        i->setSucc(nodo);
        return this;
    }
    List<T> *inserisciInTesta(Nodo<T> *nodo)
    {
        nodo->setSucc(head);
        head = nodo;
        return this;
    }
    List<T> *inserisci(Nodo<T> *nodo, int pos)
    {
        if (pos == 0)
            inserisciInTesta(nodo);
        else
        {
            Nodo<T> *prec, *i;
            int j;
            for (i = prec = head, j = 0; i != NULL && j < pos; i = i->getSucc(), j++)
                prec = i;
            if (i == NULL)
                prec->setSucc(nodo);
            else
            {
                prec->setSucc(nodo);
                nodo->setSucc(i);
            }
        }
        return this;
    }

  public:
    List()
    {
        head = NULL;
    }
    List(T valore)
    {
        head = new Nodo<T>(valore);
    }
    List<T> *inserisci(T valore, int pos)
    {
        Nodo<T> *nodo = new Nodo<T>(valore);
        return inserisci(nodo, pos);
    }
    List<T> *inserisciInCoda(T valore)
    {
        Nodo<T> *nodo = new Nodo<T>(valore);
        return inserisciInCoda(nodo);
    }
    List<T> *inserisciInTesta(T valore)
    {
        Nodo<T> *nodo = new Nodo<T>(valore);
        return inserisciInTesta(nodo);
    }
    List<T> *cancellaTesta()
    {
        Nodo<T> *temp = head;
        head = head->getSucc();
        delete temp;
        return this;
    }
    List<T> *cancellaCoda()
    {
        Nodo<T> *i;
        for (i = head; i->getSucc()->getSucc() != NULL; i = i->getSucc())
            ;
        delete i->getSucc();
        i->setSucc(NULL);
        return this;
    }
    List<T> *cancella(T valore)
    {
        Nodo<T> *prec = head;
        Nodo<T> *i;
        for (i = head; i != NULL && i->getValore() != valore; i = i->getSucc())
            prec = i;
        if (i == head)
            head = head->getSucc();
        else if (i != NULL)
            prec->setSucc(i->getSucc());
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