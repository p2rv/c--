#include <iostream>
#include <ctype.h>

int atoi(const char* st)
{
	int val=0;
	int sign=1;
	if (*st=='-')
	{
		sign=-1;
		st++;
	}
	while( isdigit(*st))
	{
			val=val*10 + (int)(*st-'0');
			st++;
	}
	return val*sign;
}
int main()
{
	const char* st="--185";
	std::cout<<atoi(st);
	return 0;
}