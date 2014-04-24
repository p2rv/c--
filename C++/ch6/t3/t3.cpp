#include <iostream>
#include <ctype.h>
#include <string>

enum Token_value
{
	NAME,NUMB,END,OPER
};
Token_value get_token_type(char const ch);
void get_token();
int tmp_num;
std::string tmp_str;
int main()
{

	tmp_num=0;
	tmp_str="";
	
	get_token();

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
void get_token()
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
			tmp_str=str;
			std::cout<<str<<'\n';
			get_token();
		break;
		case NUMB:
			std::cin.putback(ch);
			std::cin>>num;
			tmp_num=num;
			std::cout<<num<<'\n';
			get_token();
		break;
		case END:
			std::cin.putback(ch);
			std::cout<<'\n';
			get_token();
		break;
	}

}