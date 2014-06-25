#include <iostream>
#include <ctype.h>
#include <string>
#include <map>
#include <vector>

enum Token_value
{
	NAME,NUMB,END,ASSIGN,MUL,DIV,PLUS,MINUS,SPACE
};
enum Token_type
{
	NAM,NUM,OPR
};

Token_value get_token_type(char const ch);
void GetToken();
bool ConvertToRPN(std::vector<char>* opr,std::vector<int>* num,std::vector<std::string>* nam,std::vector<Token_type>* order);
int GetOprPriority(char opr);
double Calculate(std::vector<char>* opr,std::vector<int>* num,std::vector<std::string>* nam,std::vector<Token_type>* order);

int main()
{
	GetToken();
	return 0;
}
void GetToken()
{
	char ch;
	std::vector<char> opr;
	std::vector<int> num;
	std::vector<std::string> nam;
	std::vector<Token_type> order;
	std::map<std::string,int> values;
	std::string tmp_nam;
	int tmp_num;
	char tmp_opr;
	Token_type tmp_type;

    while(1)
    {
    	std::cin.get(ch);
		switch(get_token_type(ch))
		{
			case NAME:
				std::cin.putback(ch);
				std::cin>>tmp_nam;
				nam.push_back(tmp_nam);
				order.push_back(NAM);
				values[tmp_nam]=0;
			break;
			case NUMB:
				std::cin.putback(ch);
				std::cin>>tmp_num;
				num.push_back(tmp_num);
				order.push_back(NUM);
			break;
			case PLUS:case MINUS:case DIV:case MUL:
				opr.push_back(ch);
				order.push_back(OPR);
				break;
			case ASSIGN:
				if (nam.size()==order.size()==1)
				{
					opr.push_back(ch);
					order.push_back(OPR);
				}
				else
				{
					std::cin.ignore(10000, '\n');
					std::cout<<"Fail";
					num.clear();
					nam.clear();
					opr.clear();
					order.clear();
				}
				break;
			case END:
				if(ConvertToRPN(&opr,&num,&nam,&order))
				{
					/*int a,b,c;
					a=b=c=0;
					for(int i=0;i<order.size();++i)
					{
						switch(order[i])
					{
						case NAM:
							std::cout<<nam[a]<<' ';
							++a;
							break;
						case NUM:
							std::cout<<num[b]<<' ';
							++b;
							break;
						case OPR:
							std::cout<<opr[c]<<' ';
							++c;
							break;
					}
					}*/
					std::cout<<Calculate(&opr,&num,&nam,&order);
				}
				else
					std::cout<<"Error in calculate expretion";
				num.clear();
				nam.clear();
				opr.clear();
				order.clear();
				std::cout<<'\n';
			break;
		}
    }
}

Token_value get_token_type(char const ch)
{
	if(isalpha(ch))
		return NAME;
	if(isdigit(ch))
		return NUMB;
	switch(ch)
	{
		case '=': 
			return ASSIGN;
		case '*':
			return MUL;
		case '/':
			return DIV;
		case '+':
			return PLUS;
		case '-':
			return MINUS;
		case ' ':
			return SPACE;
		case '\n':
			return END;
		default:
			return SPACE;	
	}
}

double Calculate(std::vector<char>* opr,std::vector<int>* num,std::vector<std::string>* nam,std::vector<Token_type>* order)
{
	double result;
	double lvalue,rvalue;
	int a,b,c,d;
	a=b=c=d=0;
	
	while(order->size())
	{
		
		int aa,bb,cc;
					aa=bb=cc=0;
					for(int i=0;i<order->size();++i)
					{
						switch((*order)[i])
					{
						case NAM:
							std::cout<<(*nam)[aa]<<' ';
							++aa;
							break;
						case NUM:
							std::cout<<(*num)[bb]<<' ';
							++bb;
							break;
						case OPR:
							std::cout<<(*opr)[cc]<<' ';
							++cc;
							break;
					}
					}
					std::cout<<'\n';

		switch((*order)[a])
		{
			
			case NUM:

				lvalue=rvalue;
				rvalue=(*num)[b];
				++a;
				++b;
			break;
			case OPR:
				switch((*opr)[0])
				{
					case '+':
						result=lvalue+rvalue; 
					break;
					case '-':
						result=lvalue-rvalue;
					break;
					case '*':
						result=lvalue * rvalue;
					break;
					case '/':
						result=lvalue/rvalue;
					break;
				}
				if(b-1>0)  
				{
					--b;
					--a;
					num->erase(num->begin()+b);
					opr->erase(opr->begin());
					order->erase(order->begin()+b,order->begin()+b+1); 
					(*num)[b-1]=result;
					if(b-1>0)
					{
						rvalue=(*num)[b-1];
						lvalue=(*num)[b-2];
					}
					if(b-1==0)
					{
						lvalue=result;
					}

				}
				else
					return result;
			break;
		}
	}
	//result=(*num)[0];
	return result;
}

 bool ConvertToRPN(std::vector<char>* opr,std::vector<int>* num,std::vector<std::string>* nam,std::vector<Token_type>* order)
 {
 	std::vector<char> tmp_opr,buffer;
 	std::vector<int>  tmp_num;
 	std::vector<std::string> tmp_nam;
 	std::vector<Token_type> tmp_order;

 	int a,b,c;
 	a=b=c=0;

 	for(int i=0;i<order->size();++i)
 	{
 		switch((*order)[i])
 		{
 			case NAM:
 				tmp_nam.push_back((*nam)[a]);
 				tmp_order.push_back(NAM);
 				++a;
 				break;
 			case NUM:
 				tmp_num.push_back((*num)[b]);
 				tmp_order.push_back(NUM);
 				++b;
 				break;
 			case OPR:
 				if(buffer.size())
 				{
 					char cur_opr=(*opr)[c];
 					if(GetOprPriority(cur_opr)<GetOprPriority(buffer[buffer.size()-1]))
					{
						while(buffer.size()>0)
						{
							char top=buffer.back();
							tmp_opr.push_back(top);
							tmp_order.push_back(OPR);
							buffer.pop_back();
						}
						buffer.push_back(cur_opr);
					}
					else
	 					buffer.push_back(cur_opr);
 				}
 				else
 					buffer.push_back((*opr)[c]);
 				++c;
 				break;
 		}
 	}
 	while(buffer.size()>0)
	{
		char top=buffer.back();
		tmp_opr.push_back(top);
		tmp_order.push_back(OPR);
		buffer.pop_back();
	}
 	/*a=b=c=0;
				for(int i=0;i<tmp_order.size();++i)
				{
					switch(tmp_order[i])
					{
						case NAM:
							std::cout<<tmp_nam[a]<<' ';
							++a;
							break;
						case NUM:
							std::cout<<tmp_num[b]<<' ';
							++b;
							break;
						case OPR:
							std::cout<<tmp_opr[c]<<' ';
							++c;
							break;
					}
				}
*/
	opr->clear();
	num->clear();
	nam->clear();
	order->clear();
 	opr->swap(tmp_opr);
 	num->swap(tmp_num);
 	nam->swap(tmp_nam);
 	order->swap(tmp_order);

 	return 1;
 }
 int GetOprPriority(char opr)
 {
 	switch(opr)
 	{
 		case '=': return 0;
 		case '+': case '-': return 1;
 		case '*': case '/': return 2;
 	}
 	return -1;
 }