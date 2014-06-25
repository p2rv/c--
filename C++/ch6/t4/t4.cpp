#include <iostream>
#include <vector>

void convert(std::vector<int>  * a);
int main()
{
	std::vector<int> v;
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);
	int a;
	a=5;
	convert(&v);
	for (int i = 0; i < v.size(); ++i)
		{
			std::cout<<v[i]<<'\n';
		}	
	return 1;
}
void convert(std::vector<int>  * a)
{
	std::vector<int > v;
	v.push_back(333);
	v.push_back(222);
	v.push_back(111);

	//*a=v;
	*a->swap(v); 
}