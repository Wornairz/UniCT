#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template<class T>
class RBTree{
    private:
        enum colors {R, B};
        struct Node{
            T value;
            Node * parent;
            Node * left;
            Node * right;
            colors color;
            Node(T _value): value(_value), parent(nullptr), left(nullptr), right(nullptr), color(R){}
            ~Node(){
                delete left;
                delete right;
            }
        };
        Node * root;
        void pre_order(Node * node, ofstream & out){
            if(node == nullptr)
                return;
            out << "(" << node->value << "," << (node->color == B ? 'B' : 'R') << ") ";
            pre_order(node->left, out);
            pre_order(node->right, out);
        }
        void in_order(Node * node, ofstream & out){
            if(node == nullptr)
                return;
            in_order(node->left, out);
            out << "(" << node->value << "," << (node->color == B ? 'B' : 'R') << ") ";
            in_order(node->right, out);
        }
        void post_order(Node * node, ofstream & out){
            if(node == nullptr)
                return;
            post_order(node->left, out);
            post_order(node->right, out);
            out << "(" << node->value << "," << (node->color == B ? 'B' : 'R') << ") ";
        }
        Node* seekParent(T value){
            Node * parent = nullptr;
            Node * current = root;
            while (current != nullptr){
                parent = current;
                if (value < current->value) current = current->left;
                else current = current->right;
            }
            // Viene restituito nullptr sse nell'albero non è ancora stato inserito nessun nodo (root == nullptr)
            return parent;
        }
        bool isLeftChild(Node * parent, Node * child){
            return (parent->left == child);
        }
        int getHeight(Node * node){
            if(node == nullptr)
                return 0;
            int left = getHeight(node->left);
            int right = getHeight(node->right);
            return max(left, right)+1;
        }

        void rightRotate(Node * parent){
            Node * leftChild = parent->left;
            Node * grandparent = parent->parent;
            parent->left = leftChild->right;
            if(leftChild->right != nullptr)
                leftChild->right->parent = parent;
            if(grandparent == nullptr)
                root = leftChild;
            else if(isLeftChild(grandparent, parent))
                grandparent->left = leftChild;
            else
                grandparent->right = leftChild;
            leftChild->parent = grandparent;
            leftChild->right = parent;
            parent->parent = leftChild;
        }

        void leftRotate(Node * parent){
            Node * rightChild = parent->right;
            Node * grandparent = parent->parent;
            parent->right = rightChild->left;
            if(rightChild->left != nullptr)
                rightChild->left->parent = parent;
            if(grandparent == nullptr)
                root = rightChild;
            else if(isLeftChild(grandparent, parent))
                grandparent->left = rightChild;
            else
                grandparent->right = rightChild;
            rightChild->parent = grandparent;
            rightChild->left = parent;
            parent->parent = rightChild;
        }
        void insertFixUp(Node * node){
            if(node == root){
                node->color = B;
                return;
            }
            Node * parent = node->parent;
            if(parent->color == B)
                return;

            //padre rosso, ciò implica che il nonno esiste per forza (poiché la radice è nera)    
            Node * grandparent = node->parent->parent;
            Node * uncle = (grandparent->left == parent) ? grandparent->right : grandparent->left;
            //zio rosso
            if(uncle != nullptr && uncle->color == R){
                uncle->color = B;
                parent->color = B;
                grandparent->color = R;
                insertFixUp(grandparent);
            }
            else if(isLeftChild(grandparent, uncle)){ //zio nero sinistro
                if(isLeftChild(parent, node)){
                    //Qui parent e node verrano scambiati, quindi si aggiorna il riferimento al node
                    node = parent;
                    rightRotate(parent);
                }
                leftRotate(grandparent);
                //Adesso il nonno è il figlio sinistro
                node->parent->color = B;
                node->parent->left->color = R;
            }
            else { //zio nero destro
                if(!isLeftChild(parent, node)){
                    //Qui parent e node verrano scambiati, quindi si aggiorna il riferimento al node
                    node = parent;
                    leftRotate(parent);
                }
                rightRotate(grandparent);
                //Adesso il nonno è il figlio destro
                node->parent->color = B;
                node->parent->right->color = R;
            }
        }
    public:
        RBTree() = default;
        ~RBTree(){
            delete root;
        }
        RBTree<T>* insert(T value){
            Node * nuovo = new Node(value);
            Node * parent = seekParent(value);
            if(parent == nullptr){
                root = nuovo;
                nuovo->color = B;
            }
            else{
                if(value < parent->value)
                    parent->left = nuovo;
                else 
                    parent->right = nuovo;
                nuovo->parent = parent;
                insertFixUp(nuovo);
            }
            return this;
        }

        int getTreeHeight(){
            return getHeight(root);
        }

        void dfsVisit(string type, ofstream & out){
            if(type == "preorder")
                pre_order(root, out);
            else if(type == "inorder")
                in_order(root, out);
            else
                post_order(root, out);
            out << "\n";
        }

};




