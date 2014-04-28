#include <iostream>
#include <ctype.h>
#include <string>
#include <map>

enum Token_value
{
	NAME,NUMB,END,ASSIGN,MUL,DIV,PLUS,MINUS,SPACE
};

Token_value get_token_type(char const ch);
void get_token();
bool wait_numb(char const ch,int &numb);
bool wait_name(char const ch,int &name);
bool wait_oper(char const ch,int &oper);

int main()
{
	get_token();
	return 0;
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

void get_token()
{
	char ch='';
	int num=-1; //-1 uses for test result
	double res=0;
	std::string str="";
	Token_value prev,cur=SPACE;
	std::map<std::string,int> values;

    while(str!="end")
    {
		std::cin.get(ch);
		cur=get_token_type(ch);
		switch(cur)
		{
			case NAME:
				std::cin.putback(ch);
				std::cin>>str;
				std::cout<<str<<'\n';
			break;
			case NUMB:
				std::cin.putback(ch);
				std::cin>>num;
				std::cout<<num<<'\n';
			break;
			case END:
				if(opr==ASSIGN || opr==SPACE && str!="")
					values[str]=num;
				if(opt==ASSIGN || opr==SPACE && str=="")
					std::cout<<'\t'<<num;

				break;
			default:
				opr=get_token_type(ch);
				std::cout<<(int)ch<<'\n';\
			break;
		}
    }

}
bool wait_numb(char const ch,int &numb)
{
	if(get_token_type(ch)!=NUMB)
		return false;
	std::cin.putback(ch);
	std::cin>>numb;
	return true;
}
bool wait_name(char const ch,int &name)
{
	if(get_token_type(ch)!=NAME)
		return false;
	std::cin.putback(ch);
	std::cin>>name;
	return true;	
}
bool wait_oper(char const ch,int &oper)
{
	Token_value cur=get_token(ch);
	if(cur==MUL||cur==DIV||cur==PLUS||cur==MINUS)
	{
		oper=cur;
		return true;
	}
	else
		return false;
}