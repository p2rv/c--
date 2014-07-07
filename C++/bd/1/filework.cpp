#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;
void ReadFromDisk()
{
	string line;
	int i;
	std::vector<string> v;
	
	ifstream myFile;
	myFile.open("famnam.txt");
	if(myFile.is_open())
	{
		while(getline(myFile, line))
		{	
			v.push_back(line);
			i++;
		}
		myFile.close();
	}
	else 
		cout<<"File not found";
	
	//cout<<"время выполнения программы: "+(double)time/CLOCKS_PER_SEC;
	 	


}																																																																																																																																																																																																																												

int main()
{
	clock_t time=clock();
	/* code */
	ReadFroDmisk();
	time=clock()-time;
	printf("%f", (double)time/CLOCKS_PER_SEC);
	return 0;
}
