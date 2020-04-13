#include "RBTree.cpp"

int main(){
    ifstream in("./input.txt");
    ofstream out("./output.txt");
    string type;
    int n;
    while(in >> type && in >> n){
        if(type == "int"){
            RBTree<int> * tree = new RBTree<int>();
            int temp;
            for(int i = 0; i < n; i++){
                in >> temp;
                tree->insert(temp);
            }
            out << tree->getTreeHeight() << "\n";
            delete tree;
        }
        else{
            RBTree<double> * tree = new RBTree<double>();
            double temp;
            for(int i = 0; i < n; i++){
                in >> temp;
                tree->insert(temp);
            }
            out << tree->getTreeHeight() << "\n";
            delete tree;

        }
    }

    return 0;
}