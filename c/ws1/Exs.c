#include <stdio.h>
/* Prints " "Hello word!" " */
void PrintHello()
{
	unsigned char hello_str[]={0x22, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21, 0x22};
	printf("%s\n", hello_str);
	
}

/* calculate 10^n */
double PowTen ( int n )
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

/* Flips digits of input number */
int Flip ( int n )
{
	int sol=0; 
	if ( 10 > n )
		return n;
		
	while ( 10 <= n )
	{
		sol += n%10;
		n /= 10;
		sol *= 10;
	}
	sol+=n;
	
	return sol;	
}

/* Swap values of 2 variables */
void Swap( int *a , int *b )
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


int main ()
{
	int input=0 , second_input=0;
	//Ex4
	PrintHello();
	//Ex5
	printf( "Enter number for 10^number\n");
	scanf("%d", &input);
	printf( "Powing 10 by %d = %f \n" , input , PowTen(input) );
	//Ex6
	printf( "Enter number for flip\n");
	scanf("%d", &input);
	printf( "The flip number is: %d \n", Flip(input));
	//Ex7
	printf( "Enter numbers for swap:\n");
	printf( "Enter first number\n");
	scanf("%d", &input);
	printf( "Enter scond number\n");
	scanf("%d", &second_input);
	Swap( &input , &second_input) ;
	printf( "The first number is: %d and the second is: %d \n", input , second_input );
	return 0;
}

 

