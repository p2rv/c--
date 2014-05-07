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
int GetOprPriority(Token_value opr);
bool Exchange(std::vector<char>* opr, char const cur);

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
			case PLUS:case MINUS:case DIV:case MUL:case ASSIGN:
				opr.push_back(ch);
				order.push_back(OPR);
				break;
			case END:
				int a,b,c;
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
				}
				num.clear();
				nam.clear();
				opr.clear();
				order.clear();
				ConvertToRPN(&opr,&num,&nam,&order);
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
				}
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
bool Exchange(std::vector<char>* opr, char const cur)
{
	char ch=opr->back();
	opr->pop_back();
	if(opr->size()>0 && GetOprPriority(cur)>=GetOprPriority(*opr[opr->size()-1]))
		Exchange(opr,cur);
	else
		opr->push_back(cur);
	opr->push_back(ch);
	return 1;
}
bool ConvertToRPN(std::vector<char>* opr,std::vector<int>* num,std::vector<std::string>* nam,std::vector<Token_type>* order)
{
	std::vector<char> tmp_opr;
	std::vector<int>  tmp_num;
	std::vector<std::string> tmp_nam;
	std::vector<Token_type> tmp_order;

	for(int i=0;i<*order.size();++i)
	{
		switch(*order[i])
		{
			case NAM:
				tmp_nam.push_back(*nam[a]);
				++a;
				break;
			case NUM:
				tmp_num.push_back(*nam[b]);
				++b;
				break;
			case OPR:
				if(tmp_opr.size())
				{
					char cur_opr=*opr[c];
					switch(cur_opr)
					{
						case '=':
							return false;
							break;
						default:
							if(GetOprPriority(cur_opr)>=GetOprPriority(tmp_opr[tmp_opr.size()-1]))
							{	
								
								Exchange(&tmp_opr,cur_opr);
							}
							else
								tmp_opr.push_back(cur_opr);
							break;
					}
				}
				else
					tmp_opr.push_back(*opr[c]);
				++c;
				break;
		}
	}
	opr=&tmp_opr;
	num=&tmp_num;
	nam=&tmp_nam;
	order=&order;

	return true;
}