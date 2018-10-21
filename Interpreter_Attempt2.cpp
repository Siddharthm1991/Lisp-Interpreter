//Lisp Interpreter Project
#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

string tokenVal = "";
char localBuffer;
string str = "";
int k = 0;
class SExp
{	
	public:
	FILE *fp = stdin;
	int type;
	int val;
	string name;
	SExp *left;
	SExp *right;	
	SExp *root;	
	SExp()
	{
		type = -1;
		val = -1;
		name = "";
		left = NULL;
		right = NULL;		
		root = NULL;
	}			
	
	SExp* input()
	{		
		int nxtToken = getNextToken();	
//		cout<<"Return Int : "<<nxtToken<<'\n';
//		cout<<"Token : "<<tokenVal<<'\n';			
		if(nxtToken == 1)
		{
			//cout<<"Return Int : "<<nxtToken<<'\n';
			//cout<<"Token : "<<tokenVal<<'\n';	
			SExp* s1 = input();
			int nxtToken = getNextToken();
//			cout<<"-----------------------"<<'\n';
//			cout<<"Car cdr check"<<'\n';
//			cout<<"Token value : "<<tokenVal<<'\n';
//			cout<<"Ret Value : "<<nxtToken<<'\n';
//			cout<<"K = "<<k<<'\n';
//			cout<<"STR = "<<str<<'\n';			
//			cout<<"Local buffer : "<<localBuffer<<'\n';
//			cout<<"-----------------------"<<'\n';
			SExp *s2;
			if(localBuffer == '.')
			{
				s2 = input();
			}
			else
			{				
				s2 = input2(nxtToken);
			}								
			return cons(s1, s2);
		} 	
		else if(nxtToken == 4 || nxtToken == 7)
		{
			//cout<<"Return Int : "<<nxtToken<<'\n';	
			//cout<<"Token : "<<tokenVal<<'\n';
			int i = atoi(tokenVal.c_str());
			SExp* temp = new SExp();
			temp->val = i;
			temp->type = 1;
			//input();
			return temp;
		}
		else if(nxtToken == 5 || nxtToken == 8)
		{
			//cout<<"Return Int : "<<nxtToken<<'\n';	
			//cout<<"Token : "<<tokenVal<<'\n';			
			SExp* temp = new SExp();
			temp->name = tokenVal;
			temp->type = 2;
			//input();
			return temp;
			
		}		
		else if(nxtToken >= 2 && nxtToken <= 8)
		{
			//cout<<"Return Int : "<<nxtToken<<'\n';	
			//cout<<"Token : "<<tokenVal<<'\n';
			input();	
		}		
		else
			return NULL;				
	}	
	
	SExp* input2(int nxtToken)
	{			
		if(nxtToken == 2)
		{			
			SExp* temp = new SExp();
			temp->name = "NIL";
			temp->type = 2;
			return temp;
		}	
		else if(nxtToken == 10)
			return NULL;
		else
		{			
			SExp* s1 = input();			
			int nxtToken1 = getNextToken();
			SExp* s2 = input2(nxtToken1);
			return cons(s1, s2);
		}				
	}
	
	int getNextToken()
	{		
		tokenVal = "";		
		char c = str[k++];
		if(c=='(')
		{
			tokenVal += '(';
			return 1;	
		}			
		if(c == ')')
		{
			tokenVal += ')';
			return 2;
		}			
		if(c == '.')
		{
			tokenVal += '.';
			return 3;
		}			
		if(c >= '0' && c <= '9')
		{			
			while(c >= '0' && c <= '9')
			{
				tokenVal += c;	
				c = str[k++];
			}
			k--;
			return 4;
		}
		if(c >= 'A' && c <= 'Z')
		{
			
			while((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
			{
			
				tokenVal += c;
				c = str[k++];
			}
			k--;
			return 5;
		}
		if(c == ' ' || c == '\t' || c == '\n')
		{
			while(c == ' ' || c == '\t' || c == '\n')
			{
				c = str[k++];
			}						
			k--;
			if(str[k] == '.')
				localBuffer = '.';
			else
				localBuffer = 'n';
			return 6;			
		}
		if(c == EOF)
			return 9;				
	}
	
	SExp* cons(SExp* s1, SExp* s2)
	{		
		SExp* temp = new SExp();	
		temp->left = s1;
		temp->right = s2;
		root = temp;		
		return root;
	}
	
	void print(SExp* res)
	{
		if(res->left)
		{
			cout<<"(";
			if(res->left->type == 1)
				cout<<res->left->val;
			else
				cout<<res->left->name;
			print(res->left);
			cout<<" . ";
		}
		
		if(res->right)
		{
			if(res->right->type == 1)
				cout<<res->right->val;
			else
				cout<<res->right->name;
			print(res->right);			
			cout<<")";
		}
	}
	
	void checkNextStr()
	{
		char c = (char)fgetc(fp);
		if( c == '$')
			cout<<"> Bye!"<<'\n';
		else
			init();
	}
	
	void init()
	{	
		SExp *res;
		str = "";
		k = 0;
		char c = (char)fgetc(fp);
		while(c != '$')
		{
			str += c;
			c = (char)fgetc(fp);
		}		
		res = input();
		cout<<"> ";
		if(res->left == NULL && res->right == NULL)
		{
			if(res->type == 1)
				cout<<res->val;
			else
				cout<<res->name;
		}
		else
			print(res);	
		cout<<'\n';
		checkNextStr();		
	}
		
};



int main()
{	
	SExp s;	
	s.init();	
}

