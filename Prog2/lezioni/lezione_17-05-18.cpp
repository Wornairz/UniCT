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
    void visitaPreOrder(Nodo *p)
    {
        if(p!=NULL)
        {
            cout << p->val << "\t";
            visitaPreOrder(p->left);
            visitaPreOrder(p->right);
        }
    }
    void visitaPostOrder(Nodo *p)
    {
        if(p!=NULL)
        {
            visitaPostOrder(p->left);
            visitaPostOrder(p->right);
            cout << p->val << "\t";
        }
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
        cout << "Visita Preorder: ";
        visitaPreOrder(radice);
        cout << endl;
        cout << "Visita Inorder: ";
        visitaInOrder(radice);
        cout << endl;
        cout << "Visita Postorder: ";
        visitaPostOrder(radice);
        cout << endl;
    }
};

int main()
{
    Albero tree;
    tree.inserisci(6);
    tree.inserisci(5);
    tree.inserisci(7);
    tree.inserisci(2);
    tree.inserisci(8);
    tree.inserisci(5);
    tree.stampa();
    return 0;
}
