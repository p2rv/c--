#include <iostream>
#include <ctype.h>
#include <string>

enum Token_value
{
	NAME,NUMB,END,OPER
};
Token_value get_token_type(char const ch);

int main()
{

	char ch;
	int num;
	std::string str;
	std::cin.get(ch);
	switch(get_token_type(ch))
	{
		case NAME:
			std::cin.putback(ch);
			std::cin>>str;
		break;
		case NUMB:
			std::cin.putback(ch);
			std::cin>>num;
		break;
	}
	
	std::cout<<str<<'\n'<<num<<'\n';

	return 0;
}
Token_value get_token_type(char const ch)
{
	if(isalpha(ch))
		return NAME;
	if(isdigit(ch))
		return NUMB;
	else
		return END;
}