#include <iostream>

using namespace std;

const int MaxDimTree = 100;

class Nodo
{
public:
    int val;
    Nodo *left;
    Nodo *right;
    Nodo *padre;
};

class Albero
{
private:
    Nodo *radice;
    void visitaInOrder(Nodo *p)
    {
        if(p!=NULL)
        {
            visitaInOrder(p->left);
            cout << p->val << "\t";
            visitaInOrder(p->right);
        }
    }
    void trapianta(Nodo *u, Nodo *v)
    {
        if(u->padre == NULL)
            radice = v;
        else if(u == u->padre->left)
            u->padre->left = v;
        else
            u->padre->right = v;
        if(v!=NULL)
            v->padre=u->padre;
    }
    Nodo* minimo(Nodo *x)
    {
        Nodo *mi = x;
        //attenzione se x = NULL
        while(mi->left!=NULL)
            mi = mi->left;
        return mi;
    }
public:
    Albero() : radice(NULL) {}
    void inserisci(int valore)
    {
        Nodo *nuovo = new Nodo;
        Nodo *x = radice, *y = NULL;

        nuovo->val = valore;
        nuovo->left = NULL;
        nuovo->right = NULL;
        while (x!=NULL)
        {
            y=x;
            if(valore < x->val)
                x = x->left;
            else
                x = x->right;
        }
        nuovo->padre=y;
        if(y == NULL)
            radice = nuovo;
        else if(valore < y->val)
            y->left = nuovo;
        else
            y->right = nuovo;
    }
    void stampa()
    {
        cout << "Visita Inorder: ";
        visitaInOrder(radice);
        cout << endl;
    }
    Nodo* trova(int x)
    {
        Nodo *iter = radice;
        while(iter!=NULL && x!=iter->val)
        {
            if(x<iter->val)
                iter=iter->left;
            else
                iter=iter->right;
        }
        return iter;
    }
    void cancella(Nodo *z)
    {
        Nodo *y;
        if(z->left==NULL)
            trapianta(z, z->right);
        else if(z->right==NULL)
            trapianta(z, z->left);
        else
        {
            y = minimo(z->right);
            if(y->padre!=z)
            {
                trapianta(y, y->right);
                y->right=z->right;
                y->right->padre = y;
            }
            trapianta(z,y);
            y->left=z->left;
            y->left->padre = y;
        }
        delete z;
    }
};

int main()
{
    Albero tree;
    tree.inserisci(26);
    tree.inserisci(15);
    tree.inserisci(37);
    tree.inserisci(2);
    tree.inserisci(48);
    tree.inserisci(19);
    tree.inserisci(16);
    tree.inserisci(17);
    tree.stampa();
    Nodo *elem = tree.trova(15);
    if(elem == NULL)
        cout << "Elemento non trovato" << endl;
    else
    {
        cout << "Elemento da cancellare: " << elem->val << endl;
        tree.cancella(elem);
    }
    tree.stampa();
    //per casa: provare a sostituire il val di z con il val di y, poi cancellare y (dovrebbe funzionare)
    return 0;
}
