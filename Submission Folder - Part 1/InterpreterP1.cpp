//Lisp Interpreter Project
#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<map>
using namespace std;

string tokenVal = "";
char localBuffer;
string str = "";
bool listNot = 0;
int k = 0;
class SExp
{	
	public:
	map<string,SExp*> idMap;
	FILE *fp = stdin;
	int type;
	int val;
	string name;
	SExp *left;
	SExp *right;	
	SExp *root;
	SExp *Nil;
	SExp *T;
	SExp *CAR;
	SExp *CDR;
	SExp *DEFUN;
	SExp *QUOTE;
	SExp *COND;	
	SExp()
	{
		type = -1;
		val = -1;
		name = "";
		left = NULL;
		right = NULL;		
		root = NULL;
	}	
	SExp(string txt)
	{
		type = 2;
		val = -1;
		name = txt;
		left = NULL;		
		right = NULL;
		root = NULL;
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
	
	
	SExp* input()
	{		
		int nxtToken = getNextToken();	
		if(nxtToken == 20)
		{
			cout<<"> Error : Unexpected token "<<tokenVal<<"\n";
			checkNextStr();
		}	
		else if(nxtToken == 1)
		{
			SExp* s1 = input();
			int nxtToken = getNextToken();
			SExp *s2;
			if(localBuffer == '.')
			{				
				s2 = input();
				if(listNot == 1 && !str[k++] == ')')
					k--;
			}			
			else
			{							
				listNot = 1;
				s2 = input2(nxtToken);
			}			
			return cons(s1, s2);
		} 	
		else if(nxtToken == 4 || nxtToken == 7)
		{
			int i = atoi(tokenVal.c_str());
			SExp* temp = new SExp();
			temp->val = i;
			temp->type = 1;
			return temp;
		}
		else if(nxtToken == 5 || nxtToken == 8)
		{
			if(tokenVal == "NIL")	
			{				
				return Nil;	
			}	
			else if(tokenVal == "T")
			{				
				return T;
			}
			else if(tokenVal == "CAR")
			{				
				return CAR;
			}
			else if(tokenVal == "CDR")
			{				
				return CDR;
			}
			else if(tokenVal == "DEFUN")
			{				
				return DEFUN;
			}
			else if(tokenVal == "QUOTE")
			{				
				return QUOTE;
			}
			else if(tokenVal == "COND")
			{				
				return COND;
			}
			else
			{
				SExp* temp = new SExp();			
				if(idMap[tokenVal])
				{
					temp = idMap[tokenVal];
				}
				else
				{
					temp->name = tokenVal;
					temp->type = 2;
					idMap[tokenVal] = temp;
				}			
				return temp;						
			}						
		}		
		else if(nxtToken >= 2 && nxtToken <= 8)
		{
			input();	
		}		
		else
			return NULL;				
	}	
	
	SExp* input2(int nxtToken)
	{			
		if(nxtToken == 2)
		{					
			return Nil;
		}	
		else if(nxtToken == 10)
			return NULL;
		else
		{			
			SExp* s1 = input();			
			int nxtToken1 = getNextToken();
			if(nxtToken1 == 6 && localBuffer == ')')
				nxtToken1 = 2;		
			SExp* s2 = input2(nxtToken1);
			return cons(s1, s2);
		}				
	}
	
	int getNextToken()
	{		
		tokenVal = "";
		localBuffer = ' ';		
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
			c = str[k++];
			while(c == ' ' || c == '\t' || c == '\n')
			{
				c = str[k++];
			}
			k--;
			if(c == '.')
			{
				cout<<"> Error : Unexpected token dot\n";
				checkNextStr();	
			}				
			if(c == ')')
			{
				cout<<"> Error : Unexpected token right paranthesis\n";
				checkNextStr();
			}				
			else
			{
				return 3;	
			}			
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
		if(c == '+' || c == '-')
		{
			char op = c;
			c = str[k++];
			if(c >= '0' && c <= '9')
			{
				tokenVal += op;
				while(c >= '0' && c <= '9')
				{	
					tokenVal += c;	
					c = str[k++];
				}
				k--;
				return 4;
			}
			else
			{
				cout<<"> Error : Unexpected token "<<op<<'\n';
				checkNextStr();
			}
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
				localBuffer = str[k];
			return 6;			
		}
		if(c == EOF)
			return 9;	
		else
		{						
			tokenVal += c;
			return 20;				
		}
			
	}
	
	SExp* cons(SExp* s1, SExp* s2)
	{		
		SExp* temp = new SExp();	
		temp->left = s1;
		temp->right = s2;
		root = temp;		
		return root;
	}	
	void checkNextStr()
	{
		char c = (char)fgetc(fp);
		if( c == '$')
		{
			cout<<"> Bye!"<<'\n';
			exit(1);
		}		
		else
			init();
	}
	
	void skipTheRest()
	{
		str = "";		
		char c = (char)fgetc(fp);
		while(c != '$')
		{
			str += c;
			c = (char)fgetc(fp);
		}
		if(int(str[str.size() - 1]) != 10)
		{
			skipTheRest();
		}
	}
	
	void init()
	{	
		SExp *res;
		str = "";
		k = 0;
		int lpan = 0;
		int rpan = 0;
		idMap.clear();
		char c = (char)fgetc(fp);
		while(c != '$')
		{
			str += c;
			if(c == '(')
				lpan++;
			if(c == ')')
				rpan++;
			c = (char)fgetc(fp);
		}		
		if(int(str[str.size() - 1]) != 10)
		{
			cout<<"> Error : Unexpected token $"<<'\n';
			skipTheRest();
			c = fgetc(fp);
			init();
		}
		if(lpan != rpan)
		{
			cout<<"> Error : Left and right paranthesis mismatch"<<'\n';
			init();
		}
		int nxtToken = getNextToken();
		if(nxtToken == 1)
		{
			int nxtToken = getNextToken();
			if(localBuffer == ')' || nxtToken == 2)
			{
				res = Nil;
			}
			else
			{
				k = 0;
				res = input();
			}
		}
		else
		{
			k = 0;
			res = input();	
		}		
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
	s.Nil = new SExp("NIL");
	s.T = new SExp("T");
	s.CAR = new SExp("CAR");
	s.CDR = new SExp("CDR");
	s.DEFUN = new SExp("DEFUN");
	s.COND = new SExp("COND");
	s.QUOTE = new SExp("QUOTE");
	s.init();	
	cout<<"Done"<<'\n';
}

