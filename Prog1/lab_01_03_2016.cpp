#include <iostream>
#include <typeinfo>
#include <cmath>
using namespace std;
class MyDouble{
    private: double x;
    public:
        MyDouble(){}
        MyDouble(float _x){
            x = _x;
        }
        int trunc(){
            return ((int) x);
        }
        MyDouble operator ^(const MyDouble& op){
            return MyDouble((pow(x, op.x)));
        }
        bool operator >(const MyDouble& op){
            if(x>op.x) return true;
            else return false;
        }
        friend ostream& operator <<(ostream& stream, const MyDouble md){
            stream << md.x;
            return stream;
        }
};
class A{
    private: float w;
    protected:
        static const int dim = 4;
        MyDouble* mat[dim];
    public:
        A(double _w)
        {
            w = _w;
            for(int i=0;i<dim;i++){
                mat[i] = new MyDouble[dim];
                for(int j=0;j<dim;j++){
                    mat[i][j] = MyDouble((w*10)+i+j);
                }
            }
        }
        virtual double f() = 0;
        virtual ostream& put(ostream& stream) {
            stream << "Class " << typeid(*this).name() << " ";
            return stream;
        }
        float getW(){
            return w;
        }

};
ostream& operator <<(ostream& stream, A& a){
    return a.put(stream);
}
class B: public A{
    public:
        B(double _w) : A(_w){}
        double f(){
            double sum = 0.0;
            for(int i=0;i<dim;i++){
                sum+=(mat[0][i]).trunc();
            }
            return sum;
        }
        ostream& put(ostream& stream) {
            A::put(stream);
            stream << " x=" << getW() << "\t f()=" << f();
            return stream;
        }
};
template <typename T>
class C: public A{
    private: T c;
    public:
        C(double _w, T _c) : A(_w){}
        double f(){
            int count = 0;
            for(int i=0;i<dim;i++){
                for(int j=0;j<dim;j++){
                    if(mat[i][j]>MyDouble(5.0)) count++;
                }
            }
            return count;
        }
        MyDouble f(T p){
            if(typeid(p).name() == typeid(double).name() ){
                return MyDouble(p);
            }
            else{
                return ((mat[0][0])^(mat[dim-1][dim-1]));
            }
        }
        ostream& put(ostream& stream) {
            A::put(stream);
            stream << "<" << typeid(T).name() << ">:" << " w=" << getW() << " c=" << c << " f()=" << f() << " f(3)=" << f(3);
            return stream;
        }
};
int main(){
    srand(328832748);
    double sommaf = 0;
    MyDouble f3;
    int index = 0;
    bool flag = false;
    const int DIM = 30;
    A* vett[DIM];
    for(int i=0;i<DIM;i++){
        double x = rand()/(double) RAND_MAX;
        rand();
        switch(rand()%3){
            case 0: vett[i] = new B(x); break;
            case 1: vett[i] = new C<double> (x, rand()/(double) RAND_MAX); break;
            case 2: {
                vett[i] = new C<int> (x, (int) (x*10));
                if(!flag){
                    flag = true;
                    f3 = ((C<int>*) vett[i])->f(3);
                    index = i;
                }
                break;
            }
        }
        sommaf += (vett[i])->f();
        cout << i << ") " << *vett[i] << endl;
    }
    cout << "punto 1 : sum = " << sommaf << "\t punto 2 :  f(3) = " << f3 << " di indice " << index;
}
