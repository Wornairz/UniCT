#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
using namespace std;
int main()
{
	string a[2][3]= {"ab", "ac", "ad", "ae", "af", "ag"};
	srand(time(0));
	string* p = new string[10];
	for(int i=0; i<10; i++){
		int r = rand()%2;
		int c = rand()%3;
		p[i]=a[r][c];
	}
	cout << p[9];
	delete[] p;
	return 0;
}
