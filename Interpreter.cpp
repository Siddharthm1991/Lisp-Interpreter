//Lisp Interpreter Project
#include<iostream>
#include<string>
#include<vector>
#include<stdio.h>
using namespace std;

string tokenVal = "";
class SExp
{	
	public:
	FILE *fp = stdin;
	int type;
	int val;
	string name;
	SExp *left;
	SExp *right;		
	SExp()
	{
		type = -1;
		val = -1;
		name = "";
		left = NULL;
		right = NULL;
	}			
	
	SExp* input()
	{
		int nxtToken = getNextToken();	
		cout<<"Return Int : "<<nxtToken<<'\n';	
		if(nxtToken >= 1 && nxtToken <=8)
		{
			cout<<"Token : "<<tokenVal<<'\n';	
			input();
		} 			
		else
			return NULL;		
	}	
	
	int getNextToken()
	{		
		tokenVal = "";
		char c = (char)fgetc(fp);
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
				return 7;
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
				return 8;
			else
				return 5;
		}
		if(c == ' ' || c == '\t' || c == '\n')
		{
			return 6;
		}
		if(c == EOF)
			return 9;		
	}
};

/*class Intr
{		
	SExp *head = NULL	;
	public:		
	void init()
	{		
		char c = (char)fgetc(fp);
		while(c != EOF)
		{	
			if(c == '(')
			{
				leftParan();
			}
			//cout<<"OUT"<<'\n';
			//cout<<"------------------";
			c = (char)fgetc(fp);
			//cout<<c<<'\n';
		}
	}
	
	void leftParan()
	{
		SExp *temp = new SExp();
		char c1 = (char)fgetc(fp);
		while(c1 == ' ' || c1 == '\t' || c1 == '\n')
		{
			c1 = (char)fgetc(fp);
		}
		if(c1 == '(')
			leftParan();
		if(c1 >= '0' && c1 <= '9')
		{
			SExp *temp1 = new SExp();
			temp1->val = c1 - 48;
			temp1->type = 1;
			temp->left = temp1;
			appendToDot(temp);
		}	
	}
	
	void appendToDot(SExp *node)
	{	
		cout<<"In Append method"<<'\n';
		cout<<"Val : "<<node->left->val<<'\n';
		if(head == NULL)
		{
			cout<<"Head in NULL"<<'\n';
			head = node;
		}
		else
		{
			cout<<"Head is NOT NULL"<<'\n';
			SExp *curr = head;
			while(curr->right != NULL)
				curr = curr->right;
			curr->right = node;
		}
	}
	
	void print()
	{
		SExp *curr = head;
		//cout<<"Val : "<<curr->left->val<<'\n';
		while(curr != NULL)
		{			
			curr = curr->right;
		}			
	}
};*/


int main()
{
	SExp s;
	s.input();
}
