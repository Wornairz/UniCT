#include <iostream>
#include <math.h>
#include <typeinfo>
#define DIM 30
using namespace std;
class MyArray{
    private:
        int dim;
        short* data;
    public:
        MyArray(int dim){
            this->dim = dim;
            data = new short[dim];
            for(int i=0;i<dim;i++){
                data[i] = (short) (dim*sin(dim+i));
            }
        }
        float avg(){
            short media = 0;
            for(int i=0; i<dim;i++){
                media += data[i];
            }
            return (double) media/dim;
        }
        int greater(int param){
            int count = 0;
            for(int i=0;i<dim;i++){
                if(data[i]>param) count++;
            }
            return count;
        }
        virtual ostream& put(ostream& stream) const{
            stream << "[";
            for(int i=0; i<dim-1; i++){
                stream << data[i] << ", ";
            }
            stream << data[dim-1];
            stream << "], \t";
            return stream;
        }
};
ostream& operator <<(ostream& stream, const MyArray &x){
    return x.put(stream);
}

class A{
    private:
        int dim;
    protected:
        MyArray* x;
    public:
        A(int dim){
            this->dim = dim;
            x = new MyArray(dim);
        }
        virtual float f() const = 0;
        virtual ostream& put(ostream& stream) const {
            stream << "Class " << typeid(*this).name() << ", dim=" << this->dim << *x;
        }
};

ostream& operator <<(ostream& stream, const A &a){
    return a.put(stream);
}

class B : public A{
    public:
        B(int dim) : A(dim){}
        float f() const{
            return x->avg();
        }
        virtual ostream& put(ostream& stream) const {
            A::put(stream);
            stream << "\t\t f()=" << f();
        }
};
class C : public A{
    private:
        double w;
    public:
        C(int dim, double w) : A(dim){
            this->w = w;
        }
        float f() const{
            return x->greater((int) w);
        }
        float f(int param) const{
            return w*param;
        }
        virtual ostream& put(ostream& stream) const {
            A::put(stream);
            stream << "\t w=" << w << " f()=" << f() << " f(4)=" << f(4);
        }

};
int main(){
    A* vett[30];
    srand(833274768);
    float sum=0;
    int index, cont=0;
    float f4;
    for(int i=0;i<DIM;i++){
        int x=1+rand()%5;
        switch(x%2){
            case 0: {
                vett[i] = new B(x);
                break;
            }
            case 1: {
                vett[i] = new C(x, x/(double) RAND_MAX*10000);
                if(++cont==5){
                    index = i;
                    f4 = ((C*) vett[i])->f(4);
                };
                break;
            }
        }
        cout << i << ") " << *vett[i] << endl;
        sum += vett[i]->f();
    }
    cout << "punto 1: sum=" << sum << "\t punto 2: f(4)=" << f4 << " di indice " << index;
}
