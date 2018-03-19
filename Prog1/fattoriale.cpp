#include <iostream>
using namespace std;

int f(int n){
	if(n<=1) return 1;
	else return n*f(n-1);
}
int main()
{
	int x = 0;
	cout << "Inserisci un valore: ";
	cin >> x;
	x=f(x);
	cout << "Il suo fattoriale e' " << x;
}
