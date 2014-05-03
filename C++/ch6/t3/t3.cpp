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
void get_token();

int main()
{
	get_token();
	return 0;
}


void get_token()
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
				std::cout<<ch<<'\n';
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
