#include <iostream>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "f.h"

//typedef int size_t;
int main()
{
	// int p[1000000];
	// clock_t start=clock();
	// for(int i=0;i<100;i++)
	// {
	// 	p[i]=f(i);
	// 	printf("p[%i]= %i\n",i,p[i]);
	// 	//p[i+500000]=i+500000;
	// }
	// for(int i=0;i<1000;i++)
	// {
	// 	for(int j=0;j<1000;j++)
	// 		{
				
	// 			printf("p[%i][%i]= %i\n",i,j,p[i][j]);
	// 		}
	// }
	// clock_t def=clock()-start;
	// std::cout<<def<<'\n';
	// printf ("It took me  clicks (%f seconds).\n",((float)def)/CLOCKS_PER_SEC);
	 int x=10;
	 x=30||3;
	 std::cout<<x<<'\n';
	return 0;
}

// int frequency_of_primes (int n) {
//   int i,j;
//   int freq=n-1;
//   for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
//   return freq;
// }

// int main ()
// {
//   clock_t t;
//   int f;
//   t = clock();
//   printf ("Calculating...\n");
//   f = frequency_of_primes (99999);
//   printf ("The number of primes lower than 100,000 is: %d\n",f);
//   t = clock() - t;
//   std::cout<<t;
//   printf ("It took me  clicks (%f seconds).\n",((float)t)/CLOCKS_PER_SEC);
//   return 0;
// }