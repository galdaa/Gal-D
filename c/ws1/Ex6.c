#include <stdio.h>

int main ( )
{
	int n = 0;
	int sol=0; 
	scanf("%d",&n);
	if ( 10 > n )
		return n;
	else
	{
		while ( 10 <= n )
		{
			sol+= n%10;
			n/=10;
			sol*=10;
		}
		sol+=n;
		printf("%d\n",sol);
	}
	return sol;
	
}
