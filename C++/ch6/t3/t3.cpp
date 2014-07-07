/*
This is example calc with using RPN.
Reverse Polish notation (RPN) is a mathematical notation in which every operator follows all of its operands,
in contrast to Polish notation, which puts the operator in the prefix position.

The infix expression "5 + ((1 + 2) × 4) − 3" can be written down like this in RPN:
5 1 2 + 4 × + 3 −
*/


#include <iostream>
#include <ctype.h>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

enum Token_type
{
	NAME,NUMB,MUL='*',DIV='/',PLUS='+',MINUS='-',ASSIGN='=',SPACE,END=';',PRINT='\n',ERR
};
struct Token_value
{
	double numb;
	string name;
	Token_type type;

	Token_value()
	{
		numb=0;
		name="";
		type=PRINT;
	}
	bool operator >(Token_value const & a)
    {
        return getPriority(*this) > getPriority(a);
    }
    bool operator <=(Token_value const & a)
    {
        return getPriority(*this) <= getPriority(a);
    }
    int getPriority(Token_value const & a)
    {
        switch(a.type)
        {
            case MUL: case DIV: return 2;
            case PLUS: case MINUS: return 1;
            case ASSIGN: return 0;
        }
    }
};

Token_type getToken();
bool getExpr();
void calc();

stack<Token_value*> istr;
stack<Token_value*> rnotation;
Token_type curToken;

int main()
{

	getExpr();
	return 0;
}
bool getExpr()
{
    Token_type token=PRINT;
    while(token!=END)
    {
     token=getToken();
     switch(token)
     {
         case ERR: return false;
         case PRINT: calc();
         case END: {calc(); return true;}
     }
    }
    return false;
}


void convertToRPN()
{
    Token_value *cur;

	stack<Token_value*> operands;
	//позже перенесу эту часть функционала в getExpr
	while(!istr.empty())
	{
		cur=istr.top();
		istr.pop();
		if(cur->type==NAME||cur->type==NUMB)
            rnotation.push(cur);
        else
            {
                 if(operands.top()<=cur)
                    operands.push(cur);
                 else
                 {
                    while(!operands.empty())
                       { rnotation.push(operands.top());
                       	operands.pop();
                       }
                    operands.push(cur);
                 }
            }
	}
}
void calc()
{
    stack<Token_value*> tmp;
    double result;
    Token_value *lleft,*rright,*opr,*cur;
    lleft->type=rright->type=PRINT;

    while(!rnotation.empty())
    {
        cur=rnotation.top();
        rnotation.pop();
        switch(cur->type)
        {
            case NUMB: case NAME:
                if(lleft->type==PRINT)
                    lleft=cur;
                else
                {
                    if(rright->type==PRINT)
                        rright=cur;
                    else
                    {
                        tmp.push(lleft);
                        lleft=rright;
                        rright=cur;
                    }
                }
                break;
            case PLUS:
                    if(!tmp.empty())
                        {
                        	rright->numb=(tmp.top())->numb+rright->numb;
                        	tmp.pop();
                        }
                    break;
            case MINUS: 
					{		
            		if(!tmp.empty())
                        rright->numb=(tmp.top())->numb-rright->numb;
                    else
                    	rright->numb=-rright->numb;
                    tmp.pop();
                    break;
               		 }
            case MUL:
            {
            		if(!tmp.empty())
                        rright->numb=(tmp.top())->numb*rright->numb;
                    else
                    {
                    	cout<<"error in expression in mul operations";
                    	return;
                    }
                    tmp.pop();
                    break;
                }
            case DIV:
            {
            		if(!tmp.empty())
                        rright->numb=(tmp.top())->numb/rright->numb;
                    else
                    {
                    	cout<<"error in expression in div operations";
                    	return;
                    }
                    tmp.pop();
                    break;
                }
        }

    }
    cout.setf(ios_base::fixed);
    cout<< rright->numb<<'\n';
}
Token_type getToken()
{
	char ch;
	Token_value *value;

	while(cin.get(ch))
	{
		value=new Token_value();
		if(isalpha(ch))
		{
			cin.putback(ch);
			cin>>value->name;
			value->type=NAME;
			istr.push(value);
			return curToken=NAME;
		}
		else
		{

			switch(ch)
			{
				case ',':
					cin.putback('.');
					break;
				case '1': case '2': case '3': case '4': case '5': case '6':
				case '7': case '8': case '9': case '0': case '.':
					{
					    cin.putback(ch);
                        cin>>value->numb;
                        value->type=NUMB;
                        istr.push(value);
                        return curToken=NUMB;
					 }
				case '+': case '-': case '*': case '/':
				    {
				    	value->type=Token_type(ch);
                        istr.push(value);
                        return curToken=Token_type(ch);

				    }
                case ';': case '\n':
                        return curToken=Token_type(ch);
				default:
					return curToken=ERR;
			}
		}
	}
	return curToken= END;
}