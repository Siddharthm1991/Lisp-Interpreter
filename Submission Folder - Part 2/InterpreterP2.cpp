/*
	CSE 6341 Project Part 2 - LISP Interpreter
	Purpose : Evaluate given S-Expression
	
	@Author : Siddharth Mathiazhagan
*/
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
	SExp *CONS;
	SExp *DEFUN;
	SExp *QUOTE;
	SExp *COND;	
	SExp *PLUS;
	SExp *MINUS;
	SExp *TIMES;
	SExp *QUOTIENT;
	SExp *REMAINDER;
	SExp *LESS;
	SExp *GREATER;
	SExp *EQ;	
	SExp *ATOM;
	SExp *dList;
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
			int nxtToken = getNextToken();			
			if(nxtToken == 2 || localBuffer == ')')
				return Nil;
			else
				k-= tokenVal.size();
			SExp* s1 = input();
			nxtToken = getNextToken();			
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
			else if(tokenVal == "PLUS")
			{
				return PLUS;
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
		if(localBuffer == ')')
			return Nil;
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
	
	SExp* car(SExp* s1)
	{
		if(atom(s1) == T)
		{
			cout<<"> Error : CAR operation being performed on an atomic s-expression\n";
			checkNextStr();
		}	
		else
			return s1->left;
	}	
	
	SExp* cdr(SExp* s1)
	{
		if(atom(s1) == T)
		{
			cout<<"> Error : CDR operation being performed on an atomic s-expression\n";
			checkNextStr();			
		}			
		else
			return s1->right;
	}
	
	SExp* eq(SExp* s1, SExp* s2)
	{
		if(s1->type != s2->type)
		{
			return Nil;
		}			
		
		if(s1->type == 1)
		{
			if(s1->val == s2->val)
				return T;
			else
				return Nil;
		}	
		else
		{
			if(s1->name == s2->name)
				return T;
			else
				return Nil;
		}	
	}
	
	SExp* atom(SExp *s1)
	{
		if(s1->left == NULL && s1->right == NULL)
			return T;
		else
			return Nil;	
	}
	
	SExp* intr(SExp *s1)
	{
		if(s1->type == 1)
			return T;
		else
			return Nil;
	}
	
	SExp* null(SExp *s1)
	{
		if(s1->name == "NIL")
			return T;
		else
			return Nil;
	}
	
	SExp* plus(SExp *s1, SExp *s2)
	{
		if(intr(s1) == T && intr(s2) == T)
		{
			SExp* temp = new SExp();
			temp->type = 1;
			temp->val = s1->val + s2->val;
			return temp;
		}
		else
		{
			cout<<"> Error : Integer atoms not being passed to PLUS\n";
			checkNextStr();
		}
	}
	
	SExp* minus(SExp *s1, SExp *s2)
	{
		if(intr(s1) == T && intr(s2) == T)
		{
			SExp* temp = new SExp();
			temp->type = 1;
			temp->val = s1->val - s2->val;
			return temp;
		}
		else
		{
			cout<<"> Error : Integer atoms not being passed to MINUS\n";
			checkNextStr();
		}
	}
	
	SExp* times(SExp *s1, SExp *s2)
	{
		if(intr(s1) == T && intr(s2) == T)
		{
			SExp* temp = new SExp();
			temp->type = 1;
			temp->val = s1->val * s2->val;
			return temp;
		}
		else
		{
			cout<<"> Error : Integer atoms not being passed to TIMES\n";
			checkNextStr();
		}
	}
	
	SExp* quotient(SExp *s1, SExp *s2)
	{
		if(intr(s1) == T && intr(s2) == T)
		{
			SExp* temp = new SExp();
			temp->type = 1;
			temp->val = s1->val / s2->val;
			return temp;
		}
		else
		{
			cout<<"> Error : Integer atoms not being passed to QUOTIENT\n";
			checkNextStr();
		}
	}
	
	SExp* remainder(SExp *s1, SExp *s2)
	{
		if(intr(s1) == T && intr(s2) == T)
		{
			SExp* temp = new SExp();
			temp->type = 1;
			temp->val = s1->val % s2->val;
			return temp;
		}
		else
		{
			cout<<"> Error : Integer atoms not being passed to REMAINDER\n";
			checkNextStr();
		}
	}
	
	SExp* less(SExp *s1, SExp *s2)
	{
		if(intr(s1) == T && intr(s2) == T)
		{
			if(s1->val < s2->val)
				return T;
			else
				return Nil;
		}
		else
		{
			cout<<"> Error : Integer atoms not being passed to LESS\n";
			checkNextStr();
		}
	}
	
	SExp* greater(SExp *s1, SExp *s2)
	{
		if(intr(s1) == T && intr(s2) == T)
		{
			if(s1->val > s2->val)
				return T;
			else
				return Nil;
		}
		else
		{
			cout<<"> Error : Integer atoms not being passed to GREATER\n";
			checkNextStr();
		}
	}
	
	SExp* evcon(SExp *be, SExp *aList)
	{
		if(null(be) == T)
		{
			cout<<"> Error : No more conditions to evaluate in COND\n";
			checkNextStr();
		}		
		if(eval(car(car(be)), aList) == T)
		{
			return eval(car(cdr(car(be))), aList);
		}
		else
		{
			return evcon(cdr(be), aList);
		}
	}
	
	SExp* evlis(SExp *list, SExp* aList)
	{
		if(null(list) == T || list == NULL) 
		{
			return Nil;
		}		
		else
		{
			if(atom(list) == Nil)
			{
				SExp* tempEvalRes = eval(car(list) , aList);
				SExp* tempEvlisRes = evlis(cdr(list), aList);
				SExp *evlisRes = cons(tempEvalRes , tempEvlisRes);		
				return evlisRes;	
			}			
			else
			{
				cout<<"> Error : Not a LISP Expression\n";
				checkNextStr();
			}
		}
	}
	
	SExp* getVal(SExp* exp, SExp* list)
	{
		if(null(list) == T)
		{
			return Nil;
		}
		if(eq(exp,car(car(list))) == T)
		{
			return cdr(car(list));
		}
		else
			return getVal(exp,cdr(list));
	}
	
	SExp* addPairs(SExp* pList, SExp* x, SExp* aList)
	{
		if(null(x) == T)
			return aList;
		else
		{
			SExp* temp = cons(car(pList),car(x));
			aList = cons(temp,aList);
			return addPairs(cdr(pList) , cdr(x) , aList);		
		}
	}
	
	SExp* in(SExp* a, SExp* aList)
	{
		if(null(aList) == T)
			return Nil;
		if(eq(a, car(car(aList))) == T)
			return T;
		else
			return in(a , cdr(aList));
	}
	
	int getLength(SExp* startNode)
	{
		int count = 0;
		while(startNode)
		{
			count++;
			startNode = startNode->right;
		}
		return count;
	}
	
	SExp* apply(SExp *f, SExp *x , SExp *aList)
	{
		int xCount = getLength(x) - 1;
		if(atom(f) == T)
		{
			if(eq(f,PLUS) == T)
			{
				if(xCount == 2)
					return plus(car(x) , car(cdr(x)));
				else if(xCount < 2)
				{
					cout<<"> Error : Too few arguments. Expected 2 arguments for PLUS\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 2 arguments for PLUS\n";
					checkNextStr();	
				}					
			}				
			
			if(eq(f,MINUS) == T)
			{
				if(xCount == 2)
					return minus(car(x) , car(cdr(x)));
				else if(xCount < 2)
				{
					cout<<"> Error : Too few arguments. Expected 2 arguments for MINUS\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 2 arguments for MINUS\n";
					checkNextStr();	
				}
			}				
				
			if(eq(f,CAR) == T)
			{				
				if(xCount == 1)
					return car(car(x));
				else if(xCount < 1)
				{
					cout<<"> Error : Too few arguments. Expected 1 argument for CAR\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 1 argument for CAR\n";
					checkNextStr();	
				}
			}				
				
			if(eq(f,CDR) == T)
			{
				if(xCount == 1)
					return cdr(car(x));
				else if(xCount < 1)
				{
					cout<<"> Error : Too few arguments. Expected 1 argument for CDR\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 1 argument for CDR\n";
					checkNextStr();	
				}
			}				
			
			if(eq(f,CONS) == T)
			{
				if(xCount == 2)
					return cons(car(x) , car(cdr(x)));	
				else if(xCount < 2)
				{
					cout<<"> Error : Too few arguments. Expected 2 arguments for CONS\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 2 arguments for CONS\n";
					checkNextStr();	
				}
			}				
			
			if(eq(f,EQ) == T)
			{
				if(xCount == 2)
					return eq(car(x) , car(cdr(x)));
				else if(xCount < 2)
				{
					cout<<"> Error : Too few arguments. Expected 2 arguments for EQ\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 2 arguments for EQ\n";
					checkNextStr();	
				}
			}
			
			if(eq(f,ATOM) == T)
			{
				if(xCount == 1)
					return atom(car(x));
				else if(xCount < 1)
				{
					cout<<"> Error : Too few arguments. Expected 1 argument for ATOM\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 1 argument for ATOM\n";
					checkNextStr();	
				}
			}				
				
			if(eq(f,TIMES) == T)
			{
				if(xCount == 2)
					return times(car(x) , car(cdr(x)));
				else if(xCount < 2)
				{
					cout<<"> Error : Too few arguments. Expected 2 arguments for TIMES\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 2 arguments for TIMES\n";
					checkNextStr();	
				}
			}				
			
			if(eq(f,QUOTIENT) == T)
			{
				if(xCount == 2)
					return quotient(car(x) , car(cdr(x)));
				else if(xCount < 2)
				{
					cout<<"> Error : Too few arguments. Expected 2 arguments for QUOTIENT\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 2 arguments for QUOTIENT\n";
					checkNextStr();	
				}
			}				
				
			if(eq(f,REMAINDER) == T)
			{
				if(xCount == 2)
					return remainder(car(x) , car(cdr(x)));
				else if(xCount < 2)
				{
					cout<<"> Error : Too few arguments. Expected 2 arguments for REMAINDER\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 2 arguments for REMAINDER\n";
					checkNextStr();	
				}
			}				
				
			if(eq(f,LESS) == T)
			{
				if(xCount == 2)
					return less(car(x) , car(cdr(x)));
				else if(xCount < 2)
				{
					cout<<"> Error : Too few arguments. Expected 2 arguments for LESS\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 2 arguments for LESS\n";
					checkNextStr();	
				}
			}				
			
			if(eq(f,GREATER) == T)
			{
				if(xCount == 2)
					return greater(car(x) , car(cdr(x)));
				else if(xCount < 2)
				{
					cout<<"> Error : Too few arguments. Expected 2 arguments for GREATER\n";
					checkNextStr();
				}					
				else
				{
					cout<<"> Error : Too many arguments. Expected 2 arguments for GREATER\n";
					checkNextStr();	
				}
			}				
											
			else
			{	
				if(atom(getVal(f,dList)) == T)
				{
					cout<<"> Error : Function not defined. Please check\n";
					checkNextStr();
				}
				else
				{
					int plCount = getLength(car(getVal(f,dList)));	
					int argCount = getLength(x);
					if(plCount > argCount)
					{
						cout<<"> Error : Too few arguments. Expected "<<plCount - 1<<" arguments for "<<f->name<<"\n";
						checkNextStr();
					}
					if(plCount < argCount)
					{
						cout<<"> Error : Too many arguments. Expected "<<plCount - 1<<" arguments for "<<f->name<<"\n";
						checkNextStr();
					}
					aList = addPairs(car(getVal(f,dList)), x , aList);				
					return eval(car(cdr(getVal(f,dList))) , aList);
				}				
			}
																																				
		}
		else
		{
			cout<<" > Error : Not a Lisp Expression.\n";
			checkNextStr();	
		}
	}
	
	SExp* eval(SExp *exp, SExp *aList)
	{			
		if(atom(exp) == T)
		{
			if(intr(exp) == T)
				return exp;
			else if(eq(exp,T) == T)
				return T;
			else if(eq(exp,Nil) == T)
				return Nil;
			else if(in(exp, aList) == T)
			{
				return getVal(exp, aList);			
			}				
			else
			{
				cout<<"> Error : Unbound atom.\n";
				checkNextStr();
			}			
		}
		else if(atom(car(exp)) == T)
		{			
			if(eq(car(exp),QUOTE) == T)
			{
				return car(cdr(exp));	
			}				
			if(eq(car(exp),COND) == T)
			{
				evcon(cdr(exp),aList);	
			}				
			else
			{
				apply(car(exp),evlis(cdr(exp),aList),aList);	
			}				
		}
		else
		{
			cout<<"> Error : Given expression is not a lisp expression!";
			checkNextStr();
		}
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
		if(eq(car(res),DEFUN) == T)
		{
			SExp* fName = car(car(cdr(res)));
			cout<<"> "<<fName->name<<'\n';			
			SExp* pl = car(cdr(car(cdr(res))));
			SExp* fb = cdr(cdr(res));			
			dList = cons(cons(fName,cons(pl,fb)), dList);
		}
		else
		{
			SExp *evalRes = eval(res,Nil);							
			cout<<"> ";			
			if(atom(evalRes) == T)
			{
				if(evalRes->type == 1)
				{
					cout<<evalRes->val<<'\n';
				}
				else if(evalRes->type == 2)
				{
					cout<<evalRes->name<<'\n';
				}			
			}
			else
			{
				print(evalRes);
				cout<<'\n';
			}
		}					
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
	s.CONS = new SExp("CONS");
	s.DEFUN = new SExp("DEFUN");
	s.COND = new SExp("COND");
	s.QUOTE = new SExp("QUOTE");
	s.PLUS = new SExp("PLUS");
	s.MINUS	= new SExp("MINUS"); 
	s.EQ = new SExp("EQ");
	s.ATOM = new SExp("ATOM");
	s.TIMES = new SExp("TIMES");
	s.QUOTIENT = new SExp("QUOTIENT");
	s.REMAINDER = new SExp("REMAINDER");
	s.LESS = new SExp("LESS");
	s.GREATER = new SExp("GREATER"); 
	s.dList = s.Nil;
	s.init();	
	cout<<"Done"<<'\n';
}

