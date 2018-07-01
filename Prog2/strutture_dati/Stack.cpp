#include <iostream>

using namespace std;

template <class T>
class Nodo
{
  public:
    Nodo()
    {
        next = NULL;
    }
    Nodo(Nodo *next, T valore)
    {
        this->next = next;
        this->valore = valore;
    }
    Nodo(Nodo *next)
    {
        this->next = next;
    }
    Nodo(T valore)
    {
        next = NULL;
        this->valore = valore;
    }
    Nodo *getNext()
    {
        return next;
    }
    T getValore()
    {
        return valore;
    }
    void setNext(Nodo *next)
    {
        this->next = next;
    }
    void setValore(T valore)
    {
        this->valore = valore;
    }

  private:
    T valore;
    Nodo *next;
};

template <class T>
class Stack
{
  private:
    Nodo<T> *head;
    void push(Nodo<T> *nodo)
    {
        nodo->setNext(head);
        head = nodo;
    }

  public:
    Stack()
    {
        head = NULL;
    }
    Stack(T valore)
    {
        head = new Nodo<T>(valore);
    }
    void push(int valore)
    {
        Nodo<T> *nodo = new Nodo<T>(valore);
        return push(nodo);
    }
    Nodo<T> *pop()
    {
        if (head != NULL)
        {
            Nodo<T> *temp = head;
            head = head->getNext();
            return temp;
        }
    }
    void stampa()
    {
        for (Nodo<T> *i = head; i != NULL; i = i->getNext())
            cout << i->getValore() << " ";
        cout << endl;
    }
};

int main()
{
    Stack<int> *pila = new Stack<int>(10);
    pila->pop();
    pila->pop();
    pila->push(20);
    pila->push(30);
    pila->stampa();
    pila->pop();
    pila->stampa();
    return 0;
}