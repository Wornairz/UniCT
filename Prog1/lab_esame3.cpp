#include <iostream>
#include <cmath>
#include <typeinfo>
using namespace std;

class A{
    protected:
        int x;
    public:
        A(int _x){
            x = _x;
        }
        virtual int f() const = 0;
        virtual ostream& put(ostream& stream) const = 0;
};
class B: public A{
    private:
        char b;
    public:
        B(int _x, char _b) : A(_x){
            b = _b;
        }
        int f() const{
            if(x%2==0) return ((int) b);
            else return ((int) b)*2;
        }
        ostream& put(ostream& stream) const{
            stream << "Class " << typeid(this).name();
            stream << ": \t x=" << x << " b='" << b << "'\t f()=" << f();
            return stream;
        }
        friend B operator ++(B dummy){ //lolly Camuso
            B copia = *this;
            x++;
            return copia;
        }
};
ostream& operator <<(ostream& stream, const A* a){
    a->put(stream);
}
template <typename T>
class C: public A{
    private:
        T c;
    public:
        C(int _x, T _c) : A(_x){
            c = _c;
        }
        int f() const{
            return x + ((int)(20*c));
        }
        T f(double eps) const{
            if(sizeof(T) == sizeof(char)){
                return c+1;
            }
            else{
                return f()+((T) eps);
            }
        }
        ostream& put(ostream& stream) const{
            stream << "Class " << typeid(this).name();
            stream << "<" << typeid(T).name() << ">: x=" << x << " c=" << c << " f()=" << f() << " f(0.03)=" << f(0.03);
            return stream;
        }
};
int main(){
    const int DIM = 50;
    int maxf = 0;
    string conc = "";
    A* vett[DIM];
    srand(328832748);
    for(int i=0; i<DIM; i++){
        int x = 1+rand()%100;
        int c = 'a' + rand()%26;
        switch (rand()%3){
            case 0: vett[i] = new B(x, c); break;
            case 1: vett[i] = new C<double>(x,rand()/(double)RAND_MAX); break;
            case 2: {
                 vett[i] = new C<char>(x, c+1);
                 conc += ((C<char>*) vett[i])->f(0.03);
                 break;
            }
        }
        if(vett[i]->f() > maxf) maxf = vett[i]->f();
        cout << vett[i] << endl;
    }
    cout << "Punto 1: max = " << maxf << endl;
    cout << "Punto 2: conc = \"" << conc << "\"" <<endl;
}
