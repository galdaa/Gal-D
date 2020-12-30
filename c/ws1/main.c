/* *******************************
DESCRIPTION: 
	Test of:
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

int main ()
{
	/* Test */
	int input=0 , second_input=0;
	/*Ex4*/
	PrintHello();
	/*Ex5*/
	printf( "Enter number for 10^number\n");
	scanf("%d", &input);
	printf( "Powing 10 by %d = %f \n" , input , PowTen(input) );
	/*Ex6*/
	printf( "Enter number for flip\n");
	scanf("%d", &input);
	printf( "The flip number is: %d \n", Flip(input));
	/*Ex7*/
	printf( "Enter numbers for swap:\n");
	printf( "Enter first number\n");
	scanf("%d", &input);
	printf( "Enter scond number\n");
	scanf("%d", &second_input);
	Swap( &input , &second_input) ;
	printf( "The first number is: %d and the second is: %d \n", input , second_input );
	return 0;
}
