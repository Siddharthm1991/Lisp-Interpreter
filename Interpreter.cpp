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
	SExp *root;	
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
//		cout<<"Return Int : "<<nxtToken<<'\n';
//		cout<<"Token : "<<tokenVal<<'\n';			
		if(nxtToken == 1)
		{
			//cout<<"Return Int : "<<nxtToken<<'\n';
			//cout<<"Token : "<<tokenVal<<'\n';	
			SExp* s1 = input();
//			if(s1 -> val != -1)
//				cout<<"S1Exp Val : "<<s1->val<<'\n';
//			if(s1->name != "")
//				cout<<"S1Exp Name : "<<s1->name<<'\n';
			
			SExp* s2 = input();						
//			if(s2 -> val != -1)
//				cout<<"S2Exp Val : "<<s2->val<<'\n';
//			if(s2->name != "")
//				cout<<"S2Exp Name : "<<s2->name<<'\n';
			//cout<<"Call to cons"<<'\n';
			return cons(s1, s2);
		} 	
		else if(nxtToken == 4 || nxtToken == 7)
		{
			//cout<<"Return Int : "<<nxtToken<<'\n';	
			//cout<<"Token : "<<tokenVal<<'\n';
			int i = stoi(tokenVal);
			SExp* temp = new SExp();
			temp->val = i;
			temp->type = 1;
			return temp;
		}
		else if(nxtToken == 5 || nxtToken == 8)
		{
			//cout<<"Return Int : "<<nxtToken<<'\n';	
			//cout<<"Token : "<<tokenVal<<'\n';			
			SExp* temp = new SExp();
			temp->name = tokenVal;
			temp->type = 2;
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
	
	SExp* cons(SExp* s1, SExp* s2)
	{
		if(root == NULL)
		{
			root->left = s1;
			root->right = s2;
		}
		else
		{
			SExp* temp = new SExp();	
			temp->left = s1;
			temp->right = s2;
			root = temp;
		}
		
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
	s.print(res);
	//cout<<"Final Result : "<<res->right->right->name<<'\n';
}


//Approach 1 Code

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

