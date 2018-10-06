//Lisp Interpreter Project
#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
using namespace std;

class SExp
{
	int type;
	int val;
	string name;
	SExp* left;
	SExp* right;
};

int main()
{
	FILE *fp = stdin;
	char c = '';
	while( c != '\0')
	{
		c = (char)fgetc(fp);	
		cout<<c<<'\n';
	}		
	string input;
	getline(cin,input);
	//cout<<"String : "<<input<<'\n';
}
