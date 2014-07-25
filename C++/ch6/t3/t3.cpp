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
    	if (this==NULL)
            return true;
    	else
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
void convertToRPN();
void print();

vector<Token_value*> istr;
vector<Token_value*> rnotation;

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
         case ERR:
        {
            cout<<"error in exp parse"<<'\n';
            istr.clear();
     		break;
        }
         case PRINT:case END:
         {
         	calc();
         	istr.clear();
     		break;
     	 }
      }
    }
    return true;
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
			istr.push_back(value);
			return NAME;
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
                        istr.push_back(value);
                        return NUMB;
					 }
				case '+': case '-': case '*': case '/':
				    {
				    	value->type=Token_type(ch);
                        istr.push_back(value);
                        return Token_type(ch);

				    }
                case ';': case '\n':
                        return Token_type(ch);
				default:
					{
					    cin.clear();
                        cin.sync();
					    return ERR;

					}
			}
		}
	}
}

void convertToRPN()
{
    Token_value *cur;
    Token_value *prev;
	vector<Token_value*> operands;
	for(auto it = istr.begin(); it != istr.end(); ++it)
	{
		cur=*it;
		if(cur->type==NAME||cur->type==NUMB)
            rnotation.push_back(cur);
        else
            {
            	if(operands.size())
					    prev=operands.back();
				else
					prev=NULL;
                if(*prev<=*cur)
                    operands.insert(operands.begin(),cur);
                else
                 {
                    rnotation.insert(rnotation.end(),operands.begin(),operands.end());
                    operands.clear();
                    operands.insert(operands.begin(),cur);
                 }
            }
	}
	rnotation.insert(rnotation.end(),operands.begin(),operands.end());
}
void print()
{
    Token_value* cur;
    for(auto it = rnotation.begin(); it != rnotation.end(); ++it)
    {
        cur=*it;
        switch(cur->type)
        {
            case NUMB: case NAME:
            {
                cout<<cur->numb;
                break;
            }
            case PLUS:case MINUS:case MUL: case DIV:
                cout<<(char)cur->type;
                break;
        }
    }
    cout<<'\n';
}
void calc()
{
	convertToRPN();
    vector<Token_value*> tmp;
    double result;
    Token_value *lleft,*rright,*opr,*cur;
   for(auto it = rnotation.begin(); it != rnotation.end(); ++it)
    {
        cur=*it;
        switch(cur->type)
        {
            case NUMB: case NAME:
            {
                tmp.push_back(cur);
                break;
            }
            case PLUS:
                    {
                        if(tmp.size()>=2)
                        {
                            lleft=*(tmp.end()-2);
                            rright=*(tmp.end()-1);
                            cout<<lleft->numb<<" + "<<rright->numb;
                            rright->numb=lleft->numb+rright->numb;
                            cout<<" ="<<rright->numb<<'\n';
                            tmp.erase(tmp.end()-2);
                        }
                        else
                            cout<<"Error in calculate exp" <<'\n';

                    break;
                    }
            case MINUS:
					{
					    switch(tmp.size())
					    {
					        case 0: cout<<"Error in calculate exp" <<'\n'; break;
					        case 1:
                                {
                                    rright=*(tmp.end()-1);
                                    cout<<" - "<<rright->numb;
                                    rright->numb=-rright->numb;
                                    cout<<" ="<<rright->numb<<'\n';
                                    break;
                                }
                            default:
                                {
                                    lleft=*(tmp.end()-2);
                                    rright=*(tmp.end()-1);
                                    cout<<lleft->numb<<" - "<<rright->numb;
                                    rright->numb=lleft->numb-rright->numb;
                                    cout<<" ="<<rright->numb<<'\n';
                                    tmp.erase(tmp.end()-2);
                                    break;
                                }
					    }
					    break;
               		 }
            case MUL:
            {
                if(tmp.size()>=2)
                {
                    lleft=*(tmp.end()-2);
                    rright=*(tmp.end()-1);
                    cout<<lleft->numb<<" * "<<rright->numb;
                    rright->numb=lleft->numb*rright->numb;
                    cout<<" ="<<rright->numb<<'\n';
                    tmp.erase(tmp.end()-2);

                }
                else
                    cout<<"Error in calculate exp" <<'\n';
                break;
                }
            case DIV:
            {
            		if(tmp.size()>=2)
                {
            		lleft=*(tmp.end()-2);
                    rright=*(tmp.end()-1);
                    cout<<lleft->numb<<" / "<<rright->numb;
                    rright->numb=lleft->numb/rright->numb;
                    cout<<" ="<<rright->numb<<'\n';
                    tmp.erase(tmp.end()-2);
                }
                else
                    cout<<"Error in calculate exp" <<'\n';
                    break;
                }
        }


    }
    cout.setf(ios_base::fixed);
    cout<< rright->numb<<'\n';
    rnotation.clear();
}

