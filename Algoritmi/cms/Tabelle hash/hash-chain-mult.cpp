#include <ostream>
#include <fstream>
#include <sstream>
#include <list>


using namespace std;

template<class T>
class HashTable{
    private:
        list<T> * table;
        int bucketSize;

    public:
        HashTable(int bucketSize): bucketSize(bucketSize){
            this->table = new list<T>[bucketSize];
        }

        void insert(T key){
            table[h(key)].push_back(key);
        }

        int h(T k){
            double kA = k * 0.61803;
            double parteDecimale = kA - (int)(kA);
            return parteDecimale * bucketSize;
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