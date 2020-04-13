#include "RBTree.cpp"

int main(){
    ifstream in("./input.txt");
    ofstream out("./output.txt");
    string type, visit;
    int n;
    while(in >> type && in >> n && in >> visit){
        if(type == "int"){
            RBTree<int> * tree = new RBTree<int>();
            int temp;
            for(int i = 0; i < n; i++){
                in >> temp;
                tree->insert(temp);
            }
            tree->dfsVisit(visit, out);
            delete tree;
        }
        else{
            RBTree<double> * tree = new RBTree<double>();
            double temp;
            for(int i = 0; i < n; i++){
                in >> temp;
                tree->insert(temp);
            }
            tree->dfsVisit(visit, out);
            delete tree;

        }
    }

    return 0;
}