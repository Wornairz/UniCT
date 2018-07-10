#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    string line;
    string grp, temp;
    unsigned short n;
    int op1, op2;
    char op;
    while (getline(infile, line))
    {
        istringstream iss(line);
        iss >> n;
        for (int i = 0; i < n; i++)
        {
            iss >> grp;
            temp = "";
            for(int j=0; j<grp.length(); j++){
                if(grp[j]=='+' || grp[j]=='-' || grp[j]=='*' || grp[j]=='/'){
                    op = grp[j];
                    op1 = atoi(temp.c_str());
                    temp = "";
                }
                else
                    temp += grp[j];
            }
            op2 = atoi(temp.c_str());

            //cout << "op1 = " << op1 << " op2 = " << op2 << " op = " << op << endl;

            if(op == '+')
                outfile << op1+op2 << " ";
            else if(op == '-')
                outfile << op1-op2 << " ";
            else if(op == '*')
                outfile << op1*op2 << " ";
            else if(op == '/')
                outfile << op1/op2 << " ";
        }
        outfile << "\n";
    }
    return 0;
}
