#include <stdio.h>
double Powing ( int n )
{
	int i=0;
	int exp=n;
	double base=10;
	double sol=1;
	if ( 0 > n )
	{
		exp=-n;
		base=0.1;
	}
	for( i=0 ; i<exp ; i++ )
	{
		sol*=base;
	}
	return sol;
}
int main (  )
{
 	int n=0;
	scanf("%d", &n);
	printf( "%f" , Powing(n) );
	return 0;	
}
