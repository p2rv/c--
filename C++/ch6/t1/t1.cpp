#include <iostream>
#include <string.h>

int str_len(const char *s);
int  main()
{
	char a[]="dsf12341dfjg";
	//a[0]='6';
	char const *b=a;
	int i=0;
	while(*b!='1')
	{
		b++;
		i++;
	}
	std::cout<<i<<" "<<a[i]<<'\n';
	
	return 0;
}

int str_len(const char *s)
{
	int i=0;
	while(*s)
	{
		//std::cout<<*s<<'\n';
		//*s='Z';
		s++;
		i++;
	}
	return i;
}