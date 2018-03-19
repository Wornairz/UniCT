#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <cstdlib>

using namespace std;
class A
{
private:
    string s;
public:
    A(string _s)
    {
        s = _s;
    }
    string getS() const
    {
        return s;
    }
    virtual bool doppia()
    {
        for(int i=0; i<s.length()-1; i++)
        {
            char cerc = s[i];
            for(int j=i+1; j<s.length(); j++)
            {
                if(s[i]==s[j])
                {
                    return true;
                }
            }
        }
        return false;
    }
    virtual string nuova() = 0;
    virtual ostream& put(ostream& stream) const = 0;
};

class B : public A
{
private:
    int y;
public:
    B(string _s, int _y) : A(_s)
    {
        y = _y;
    }
    bool doppia()
    {
        string temp = getS();
        for(int i=0; i<temp.length()-1; i++)
        {
            if(temp[i]=='a' || temp[i]=='e' || temp[i]=='i' || temp[i]=='o' || temp[i]=='u')
            {
                char cerc = temp[i];
                for(int j=i+1; j<temp.length(); j++)
                {
                    if(temp[i]==temp[j])
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    string nuova(){
        stringstream sstream;
        if(y%3==0){
            sstream << getS().substr(getS().length()-3, 3);
        }
        else{
            sstream << getS().substr(0,3);
        }
        return sstream.str();
    }
    ostream& put(ostream& stream) const{
        stream << "Class B:";
        stream << " y=" << y;
        return stream;
    }
};
class C : public A{
protected:
    char c;
public:
    C(string _s, char _c) : A(_s){
        c = _c;
    }
    virtual string nuova(){
        string temp = getS();
        for(int i=1; i<temp.length();i++){
            temp[i] = '*';
        }
    }
};
class D : public C{
public:
    D(string _s, char _c) : C(_s, _c){}
    string nuova(short x){
        stringstream sstream;
        sstream << c;
        for(int i=0;i<x;i++){
            sstream << getS()[i];
        }
        return sstream.str();
    }
    ostream& put(ostream& stream) const{
        stream << "Class D:";
        stream << " c='" << c << "'";
        return stream;
    }
};

ostream& operator <<(ostream& stream, const A& a){
    return a.put(stream);
}
int main()
{
    const int DIM = 30;
    A* vett[30];
    stringstream nuova;
    stringstream nuova3;
    int doppi = 0;
    srand(111222333);
    for(int i=0; i<DIM; i++){
        int p = rand()%5+3;
        string str = "";
        for(int j=0;j<p;j++){
            str += (char) ('a'+rand()%26);
        }
        if(rand()%2==1){
            vett[i] = new D(str, (char) ('a' + rand()%26));
            nuova3 << ((D*) vett[i])->nuova(3);
        }
        else {
            vett[i] = new B(str, rand()%15);
        }
        if(vett[i]->doppia()) doppi++;
        nuova << (vett[i]->nuova()).substr(0,2);
        cout << *vett[i] << endl;
    }
    cout << "nuova()= " << nuova.str() << endl;
    cout << "nuova(3)= " << nuova3.str() << endl;
    cout << "doppi = " << doppi << endl;
    return 0;
}
