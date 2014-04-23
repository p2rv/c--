#include <iostream>
#include <ctype.h>
#include <string>


int main()
{

	char ch;
	std::string str;
	std::cin.get(ch);
	if(isalpha(ch))
	{
		std::cin.putback(ch);
		std::cin>>str;
	}

	std::cout<<str<<'\n';

	return 0;
}