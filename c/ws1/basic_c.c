/* *******************************
DESCRIPTION: 
	Implemets of:
		Print by asci.
		Calculate 10^n.
		Flip digits.
		Swap.

Athor: Gal Dahan
*********************************/

#include <stdio.h> /* for printf */

void PrintHello();
double PowTen (int n);
int Flip (int n);
void Swap(int *a ,int *b);

/* Prints  "Hello word!" by asci in hex */
void PrintHello()
{
	unsigned char hello_str[] = 
	{0x22, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 
		0x6F, 0x72, 0x6C, 0x64, 0x21, 0x22};
	
	printf("%s\n", hello_str);
	
}

/* Calculate 10^n */
double PowTen(int n)
{
	int i = 0;
	int exp = n;
	double base = 10;
	double sol = 1;
	
	if ( 0 > n )
	{
		exp = -n;
		base = 0.1;
	}
	
	for(i = 0; i < exp; ++i)
	{
		sol *= base;
	}
	
	return sol;
}

/* Flips digits of input number */
int Flip (int n)
{
	int sol = 0; 
	
	if (10 > n)
		return n;
		
	while (10 <= n)
	{
		sol += n%10;
		n /= 10;
		sol *= 10;
	}
	
	sol+=n;
	
	return sol;	
}

/* Swap values of 2 variables */
void Swap(int *a ,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


