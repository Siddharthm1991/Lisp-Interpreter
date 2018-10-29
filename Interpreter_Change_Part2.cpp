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
//		cout<<print(s1)<<'\n';
//		cout<<'\n';
		if(atom(s1) == T)
			cout<<" > Error : CAR operation being performed on an atomic s-expression\n";
		else
			return s1->left;
	}	
	
	SExp* cdr(SExp* s1)
	{
		if(atom(s1) == T)
			cout<<" > Error : CDR operation being performed on an atomic s-expression\n";
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
//		cout<<"In plus"<<'\n';
//		cout<<"________"<<'\n';
//		cout<<s1->type<<'\n';
//		cout<<s2->type<<'\n';
//		cout<<"________"<<'\n';
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
//		cout<<"IN cond \n";		
//		cout<<(car(car(car(be))))->name;
//		cout<<'\n';
		if(null(be) == T)
		{
			cout<<" > Error : No conditions in cond!\n";
		}		
		if(eval(car(car(be)), aList) == T)
		{
//			cout<<"Result evaluation true"<<'\n';
//			print(car(cdr(car(be))));
//			cout<<'\n';
			return eval(car(cdr(car(be))), aList);
		}
		else
		{
			return evcon(cdr(be), aList);
		}
	}
	
	SExp* evlis(SExp *list, SExp* aList)
	{
//		cout<<"In evlis"<<'\n';
//		cout<<list<<'\n';
//		if(atom(list) == Nil)
//		{
//			print(list);
//			cout<<'\n';	
//		}			
//		else
//		{
//			if(list->type == 1)
//				cout<<"Value : "<<list->val<<'\n';
//			else
//				cout<<"Name : "<<list->name<<'\n';
//		}
//		cout<<"Null return value : "<<null(list)->name<<'\n';
		//cout<<'\n';
		if(null(list) == T || list == NULL) 
		{
//			cout<<"list is null in  evlis"<<'\n';
			return Nil;
		}		
		else
		{
//			cout<<"List is not null in evlis"<<'\n';
			SExp* tempEvalRes = eval(car(list) , aList);
			SExp* tempEvlisRes = evlis(cdr(list), aList);
			SExp *evlisRes = cons(tempEvalRes , tempEvlisRes);
			//SExp* evlisRes =  cons(eval(car(list) , aList) , evlis(cdr(list), aList));
			return evlisRes;
		}
	}
	
	SExp* getVal(SExp* exp, SExp* list)
	{
//		cout<<"In get val ::"<<'\n';
//		cout<<exp->name<<'\n';
//		print(list);
//		cout<<'\n';
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
//		cout<<"In add pairs of aList"<<'\n';
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
//		cout<<"Checking if parameter is in aList"<<'\n';
		if(null(aList) == T)
			return Nil;
		if(eq(a, car(car(aList))) == T)
			return T;
		else
			return in(a , cdr(aList));
	}
	
	SExp* apply(SExp *f, SExp *x , SExp *aList)
	{
//		cout<<"Print evlis result"<<'\n';
//		print(x);
//		cout<<"In apply : "<<f->name<<'\n';
		if(atom(f) == T)
		{
//			cout<<"F is atom"<<'\n';
			if(eq(f,PLUS) == T)
				return plus(car(x) , car(cdr(x)));	
			
			if(eq(f,MINUS) == T)
				return minus(car(x) , car(cdr(x)));
				
			if(eq(f,CAR) == T)
				return car(car(x));
				
			if(eq(f,CDR) == T)
				return cdr(car(x));
			
			if(eq(f,CONS) == T)
				return cons(car(x) , cdr(x));	
			
			if(eq(f,EQ) == T)
				return eq(car(x) , car(cdr(x)));
			
			if(eq(f,ATOM) == T)
				return atom(car(x));
				
			if(eq(f,TIMES) == T)
				return times(car(x) , car(cdr(x)));
			
			if(eq(f,QUOTIENT) == T)
				return quotient(car(x) , car(cdr(x)));
				
			if(eq(f,REMAINDER) == T)
				return remainder(car(x) , car(cdr(x)));
				
			if(eq(f,LESS) == T)
				return less(car(x) , car(cdr(x)));
			
			if(eq(f,GREATER) == T)
				return greater(car(x) , car(cdr(x)));
											
			else
			{				
				aList = addPairs(car(getVal(f,dList)), x , aList);				
				return eval(car(cdr(getVal(f,dList))) , aList);
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
//		cout<<"In eval"<<'\n';
//		if(null(aList) == Nil)
//		{
//			cout<<"aList is not null"<<'\n';
//			print(aList);
//			cout<<'\n';
//		}
//		else
//		{
//			cout<<"aList is empty"<<'\n';
//		}
//		if(atom(exp) == Nil)
//		{
//			cout<<"EXP in Eval : "<<'\n';
//			print(exp);
//			cout<<'\n';	
//			cout<<"F Name : "<<car(exp)->name<<'\n';
//		}			
		if(atom(exp) == T)
		{
//			cout<<"Atomic expression"<<'\n';
			//cout<<"Value : "<<in(exp, aList)->name<<'\n';
//			cout<<"Line 544"<<'\n';
			if(intr(exp) == T)
				return exp;
			else if(eq(exp,T) == T)
				return T;
			else if(eq(exp,Nil) == T)
				return Nil;
			else if(in(exp, aList) == T)
			{
//				cout<<"Getting val of parameter"<<'\n';
				return getVal(exp, aList);			
			}				
			else
			{
				cout<<"> Error : Unbound atom.\n";
				checkNextStr();
			}			
//			cout<<"Line 561"<<'\n';											
		}
		else if(atom(car(exp)) == T)
		{
			//cout<<"In second if "<<'\n';
			if(eq(car(exp),QUOTE) == T)
			{
//				cout<<"Calling Quote : "<<'\n';
				return car(cdr(exp));	
			}				
			if(eq(car(exp),COND) == T)
			{
//				cout<<"Calling apply COND : "<<'\n';
				evcon(cdr(exp),aList);	
			}				
			else
			{
////				cout<<"Calling apply : "<<'\n';
//				if(null(aList) == Nil)
//				{
////					cout<<"aList is not null"<<'\n';
//					print(aList);
//					cout<<'\n';
//				}
//				else
//				{
////					cout<<"aList is empty"<<'\n';
//				}
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
//		cout<<" Dot Notation : ";
//		if(res->left == NULL && res->right == NULL)
//		{
//			if(res->type == 1)
//				cout<<res->val;
//			else
//				cout<<res->name;
//		}
//		else
//			print(res);	
//		cout<<'\n';
		//Evaluation - Part 2 starts here
		
		// Checking if the CAR of the expression if DEFUN
		
		if(eq(car(res),DEFUN) == T)
		{
//			cout<<"_____________________\n";
//			cout<<" Defun expression.\n";
//			SExp* fName = car(car(cdr(cdr(res))));
			SExp* fName = car(car(cdr(res)));
			cout<<"> "<<fName->name<<'\n';			
//			print(fName);
//			cout<<'\n';
//			if(null(fName) == Nil)
//				cout<<" Function Name : "<<fName->name<<'\n';			
			//SExp* pl = car(cdr(cdr(res)));
			SExp* pl = car(cdr(car(cdr(res))));
//			cout<<"Parameter List : ";
//			print(pl);
//			cout<<'\n';
			SExp* fb = cdr(cdr(res));			
//			cout<<"Function Body : ";
//			print(fb);
//			cout<<'\n';
			dList = cons(cons(fName,cons(pl,fb)), dList);
//			cout<<" DList : ";
//			print(dList);
//			cout<<'\n';			
		}
		else
		{
			SExp *evalRes = eval(res,Nil);							
			//Output the Evaluation result
//			cout<<" Evaluated Result : ";
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

