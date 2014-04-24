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
	int num=0;
	std::string str="";
	Token_value opr=SPACE;
	std::map<std::string,int> values;

    while(str!="end")
    {
		std::cin.get(ch);
		switch(get_token_type(ch))
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
				
				break;
			default:
				opr=get_token_type(ch);
				std::cout<<(int)ch<<'\n';\
			break;
		}
    }

}
