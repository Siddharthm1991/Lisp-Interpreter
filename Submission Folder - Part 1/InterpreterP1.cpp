//Things left to do
/*
	1. Standard SExp for T and NIL (Done)
	2. Run program for "()" input (Done) 
	3. Use the same identifier instead of creating new ones (Implement by map) (Done)
	4. Error checking (Unexpected characters (Done), Multiple dots in a row (Done), $ inside s-expression(Done), Parenthesis mismatch(Done))	
	5. Some s-expressions not being handled ( Right parenthesis issue (Done) , dot and list mixed issue not working)
	6. Signed integers (Done)	
	7. Create the primitive functions (Done)
*/
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
			//cout<<"::"<<res->left;
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
			//cout<<"}}"<<res->right;
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
//		cout<<"Return Int : "<<nxtToken<<'\n';
//		cout<<"Token : "<<tokenVal<<'\n';
//		cout<<"Localbuffer : "<<localBuffer<<'\n';
//		cout<<"___________________________"<<'\n';										
		if(nxtToken == 20)
		{
			cout<<"> Error : Unexpected token "<<tokenVal<<"\n";
			checkNextStr();
		}	
		else if(nxtToken == 1)
		{
//			cout<<"Return Int : "<<nxtToken<<'\n';
//			cout<<"Token : "<<tokenVal<<'\n';	
			SExp* s1 = input();
//			cout<<"________________"<<'\n';
//			cout<<"S1 ::: "<<'\n';
//			print(s1);
//			cout<<"________________"<<'\n';
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
				if(listNot == 1 && !str[k++] == ')')
					k--;
			}			
			else
			{							
				listNot = 1;
				s2 = input2(nxtToken);
			}			
//			cout<<"________________"<<'\n';
//			cout<<"S2 ::: "<<'\n';
//			print(s2);
//			cout<<"________________"<<'\n';											
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
				//cout<<"TokenVal in ID : "<<tokenVal<<'\n';
				if(idMap[tokenVal])
				{
					//cout<<"Existing ID"<<'\n';
					temp = idMap[tokenVal];
				}
				else
				{
					//cout<<"Creating New Id"<<'\n';
					temp->name = tokenVal;
					temp->type = 2;
					idMap[tokenVal] = temp;
					//input();					
				}			
				return temp;						
			}						
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
			return Nil;
		}	
		else if(nxtToken == 10)
			return NULL;
		else
		{			
			SExp* s1 = input();			
//			cout<<"________________"<<'\n';
//			cout<<"S1 Input 2::: "<<'\n';
//			print(s1);
//			cout<<"________________"<<'\n';
			int nxtToken1 = getNextToken();
			if(nxtToken1 == 6 && localBuffer == ')')
				nxtToken1 = 2;		
			SExp* s2 = input2(nxtToken1);
//			cout<<"________________"<<'\n';
//			cout<<"S2 Input 2 ::: "<<'\n';
//			print(s2);
//			cout<<"________________"<<'\n';
			return cons(s1, s2);
		}				
	}
	
	int getNextToken()
	{		
		tokenVal = "";
		localBuffer = ' ';		
		char c = str[k++];
		//cout<<"C = "<<c<<'\n';
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
			/*if(c != '(' || !(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'Z'))
			{				
			}*/
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
		//cout<<"In checkNextStr"<<'\n';
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
		//cout<<"Start"<<'\n';
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
//		cout<<"Input : "<<str<<'\n';
//		cout<<"K = "<<k<<'\n';
		int nxtToken = getNextToken();
//		cout<<"NXT Token 1 : "<<nxtToken<<'\n';
		if(nxtToken == 1)
		{
			int nxtToken = getNextToken();
//			cout<<"NXT Token 2 : "<<nxtToken<<'\n';
			if(localBuffer == ')' || nxtToken == 2)
			{
				//cout<<"In localbuffer"<<'\n';				
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
		//print(res->right->left);
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

