#include <ostream>
#include <fstream>
#include <sstream>



using namespace std;

template<class T>
class Node{
    private:
        T * value;
        Node<T> * next;
    public:
        Node(T * value){
            this->value = value;
            this->next = NULL;
        }
        void setNext(Node<T> * next){
            this->next = next;
        }
        Node<T> * getNext(){
            return this->next;
        } 
};
template<class T>
class Lista{
    private:
        Node<T> * dummy;
        int _size;
    public: 
        Lista(){
            dummy = new Node<T>(NULL);
            _size = 0;
        }
        void insert(T key){
            Node<T> * nuovo = new Node<T>(new T(key));
            dummy->setNext(nuovo);
            _size++;
        }
        int size(){
            return this->_size;
        }
};
template<class T>
class HashTable{
    private:
        Lista<T> * table;
        int bucketSize;

    public:
        HashTable(int bucketSize): bucketSize(bucketSize){
            this->table = new Lista<T>[bucketSize];
        }

        void insert(T key){
            table[h(key)].insert(key);
        }

        int h(int k){
            return k % bucketSize;
        }

        void print(ofstream & out){
            for(int i = 0;  i < bucketSize; i++){
                out << table[i].size() << " ";
            }
        }

};

int main(){
    ifstream input("./input.txt");
    ofstream output("./output.txt");
    string type;
    int bucketSize, n;

    while(input >> type && input >> bucketSize && input >> n){
        if(type == "int"){
            HashTable<int> * table = new HashTable<int>(bucketSize);
            int temp;
            for(int i = 0; i < n; i++){
                input >> temp;
                table->insert(temp);
            }
            table->print(output);
        }
        else if(type == "double"){
            HashTable<double> * table = new HashTable<double>(bucketSize);
            double temp;
            for(int i = 0; i < n; i++){
                input >> temp;
                table->insert(temp);
            }
            table->print(output);
        }
        else if(type == "char"){
            HashTable<char> * table = new HashTable<char>(bucketSize);
            char temp;
            for(int i = 0; i < n; i++){
                input >> temp;
                table->insert(temp);
            }
            table->print(output);
        }
        else if(type == "bool"){
            HashTable<bool> * table = new HashTable<bool>(bucketSize);
            bool temp;
            for(int i = 0; i < n; i++){
                input >> temp;
                table->insert(temp);
            }
            table->print(output);
        }
        output << "\n";
    }
    return 0;
}