//Lisp Interpreter Project
#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

string tokenVal = "";
string localbuffer = "";
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
		cout<<"In input 1 "<<'\n';
		cout<<"Return Int : "<<nxtToken<<'\n';
		cout<<"Token : "<<tokenVal<<'\n';			
		if(nxtToken == 1)
		{
			//cout<<"Return Int : "<<nxtToken<<'\n';
			//cout<<"Token : "<<tokenVal<<'\n';	
			SExp* s1 = input();
//			if(s1 -> val != -1)
//				cout<<"S1Exp Val : "<<s1->val<<'\n';
//			if(s1->name != "")
//				cout<<"S1Exp Name : "<<s1->name<<'\n';
			
			SExp* s2 = input2();						
//			if(s2 -> val != -1)
//				cout<<"S2Exp Val : "<<s2->val<<'\n';
//			if(s2->name != "")
//				cout<<"S2Exp Name : "<<s2->name<<'\n';
//			cout<<"Call to cons"<<'\n';
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
	
	SExp* input(int nxtToken, string tokenVal)
	{
		//int nxtToken = getNextToken();	
		cout<<"In input 1 "<<'\n';
		cout<<"Return Int : "<<nxtToken<<'\n';
		cout<<"Token : "<<tokenVal<<'\n';			
		if(nxtToken == 1)
		{
			//cout<<"Return Int : "<<nxtToken<<'\n';
			//cout<<"Token : "<<tokenVal<<'\n';	
			SExp* s1 = input();
//			if(s1 -> val != -1)
//				cout<<"S1Exp Val : "<<s1->val<<'\n';
//			if(s1->name != "")
//				cout<<"S1Exp Name : "<<s1->name<<'\n';
			
			SExp* s2 = input2();						
//			if(s2 -> val != -1)
//				cout<<"S2Exp Val : "<<s2->val<<'\n';
//			if(s2->name != "")
//				cout<<"S2Exp Name : "<<s2->name<<'\n';
//			cout<<"Call to cons"<<'\n';
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
	
	SExp* input2()
	{
		int nxtToken = getNextToken();	
		cout<<"In input 2"<<'\n';
		cout<<"Return Int : "<<nxtToken<<'\n';
		cout<<"Token : "<<tokenVal<<'\n';			
//		if(nxtToken == 1)
//		{
//			//cout<<"Return Int : "<<nxtToken<<'\n';
//			//cout<<"Token : "<<tokenVal<<'\n';	
//			SExp* s1 = input();
////			if(s1 -> val != -1)
////				cout<<"S1Exp Val : "<<s1->val<<'\n';
////			if(s1->name != "")
////				cout<<"S1Exp Name : "<<s1->name<<'\n';
//			
//			SExp* s2 = input2();						
////			if(s2 -> val != -1)
////				cout<<"S2Exp Val : "<<s2->val<<'\n';
////			if(s2->name != "")
////				cout<<"S2Exp Name : "<<s2->name<<'\n';
////			cout<<"Call to cons"<<'\n';
//			return cons(s1, s2);
//		} 	
//		else if(nxtToken == 4 || nxtToken == 7)
//		{
//			SExp* s1 = input();
//			SExp* s2 = input2();
//			return cons(s1, s2);
//			//cout<<"Return Int : "<<nxtToken<<'\n';	
//			//cout<<"Token : "<<tokenVal<<'\n';
//			/*int i = atoi(tokenVal.c_str());
//			SExp* temp = new SExp();
//			temp->val = i;
//			temp->type = 1;
//			//input();
//			return temp;*/
//		}
//		else if(nxtToken == 5 || nxtToken == 8)
//		{
//			SExp* s1 = input();
//			SExp* s2 = input2();
//			return cons(s1, s2);
//			//cout<<"Return Int : "<<nxtToken<<'\n';	
//			//cout<<"Token : "<<tokenVal<<'\n';			
//			/*SExp* temp = new SExp();
//			temp->name = tokenVal;
//			temp->type = 2;
//			//input();
//			return temp;*/
//			
//		}		
//		else if(nxtToken == 2)
//		{
//			SExp* temp = new SExp();
//			temp->name = "NIL";
//			temp->type = 2;
//			return temp;
//		}
//		else if(nxtToken >= 3 && nxtToken <= 8)
//		{
//			//cout<<"Return Int : "<<nxtToken<<'\n';	
//			//cout<<"Token : "<<tokenVal<<'\n';
//			input();	
//		}		
//		else
//			return NULL;	
		if(nxtToken == 2 || localbuffer == ")")
		{
			SExp* s1 = input(nxtToken,tokenVal);
			SExp* temp = new SExp();
			temp->name = "NIL";
			temp->type = 2;
			return cons(s1,temp);
		}	
		else if(nxtToken == 9)
			return NULL;
		else
		{
			SExp* s1 = input(nxtToken,tokenVal);
			SExp* s2 = input2();
			return cons(s1, s2);
		}		
	}
	
	int getNextToken()
	{		
		tokenVal = "";
		localbuffer = "";
		char c;
		if(fp)
			c = (char)fgetc(fp);
		else
		{
			cout<<"File pointer not found!";
			exit(1);
		}
		//cout<<"Char : "<<c<<'\n';
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
				c = (char)fgetc(fp);
			}
			if(c == ')')	
			{
				localbuffer = ')';
				return 7;
			}					
			else
				return 4;
		}
		if(c >= 'A' && c <= 'Z')
		{
			
			while((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
			{
			
				tokenVal += c;
				c = (char)fgetc(fp);
			}
			if(c == ')')
			{			
				localbuffer = ')';
				return 8;
			}			
			else
				return 5;
		}
		if(c == ' ' || c == '\t' || c == '\n')
		{
			return 6;
		}
		if(c == EOF)
			return 9;		
		return 10;
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
};

int main()
{
	SExp s;
	SExp* res;
	res = s.input();
	cout<<"> ";
	if(res->left == NULL && res->right == NULL)
	{
		if(res->type == 1)
			cout<<res->val;
		else
			cout<<res->name;
	}
	else
		s.print(res);
}


