#include <stdio.h>
void Swaping ( int *a , int *b )
{
	int temp;
	temp= *a;
	*a= *b;
	*b= temp;
}
int main (  )
{
 	int  a = 0 ,b = 0;
	scanf("%d", &a);
	scanf("%d", &b);
	Swaping(&a,&b);
	printf( "firsrt: %d second: %d" , a , b );
	return 0;	
}
