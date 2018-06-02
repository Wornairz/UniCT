#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Passeggero
{
  public:
	char azione;
	int posto;
	Passeggero()
	{
		azione = ' ';
		posto = -1;
	}
	Passeggero(char azione, unsigned short posto)
	{
		this->azione = azione;
		this->posto = posto;
	}
};

unsigned short cambi, primodisp;
unsigned short n, q, caunter = 0;
Passeggero *passeggeri;

void scendi(Passeggero pass){
	for(int i=0; i<n; i++){
		if(passeggeri[i].posto==pass.posto){
			passeggeri[i] = Passeggero();
			break;
		}
	}
}

void inserisci(Passeggero pass, bool postogiusto)
{
	if(postogiusto){
		if(passeggeri[pass.posto].posto == -1){
			passeggeri[pass.posto] = pass;
		}
		else{
			Passeggero abusivo = passeggeri[pass.posto];
			passeggeri[pass.posto] = pass;
			cambi++;
			inserisci(abusivo, true);
		}
	}
	else if (pass.posto >= primodisp && passeggeri[primodisp].posto == -1)
	{
		passeggeri[primodisp] = pass;
	}
	else
	{
		inserisci(pass, true);
	}
}

void calcolaprimodisp(){
	for(int i=0; i<n; i++){
		if(passeggeri[i].posto==-1){
			primodisp = i;
			break;
		}
	}
}

void stampa(){
	for(int i=0; i<q; i++){
		cout << "posto " << i << " : " << passeggeri[i].azione << " " << passeggeri[i].posto << endl;
	}
	cout << endl;
}

int main()
{
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	string line;
	char tmpc;
	unsigned short tmpus;
	while (getline(infile, line))
	{
		cout << "riga = " << ++caunter << "\n";
		istringstream iss(line);
		iss >> n;
		iss >> q;
		cambi = 0;
		primodisp = 0;
		passeggeri = new Passeggero[n];
		for (int i = 0; i < q; i++)
		{
			iss >> tmpc;
			iss >> tmpus;
			Passeggero tmppas(tmpc, tmpus);
			if (tmpc == 'b')
				inserisci(tmppas, false);
			else
				scendi(tmppas);
			calcolaprimodisp();
		}
		delete passeggeri;
		outfile << cambi << "\n";
	}
	return 0;
}