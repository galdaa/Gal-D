/* *************************************************
DESCRIPTION: 
	
	Test of:
		Copy int array,
		
		Swap functions: 
			Int by poiners. 
			Values by size_t pointers.
			Pointers by size_t **.
		
		PrintAdresses exe.

Athor: Gal Dahan
***************************************************/

#include <stdio.h>	/* printf */
#include <stdlib.h> 	/* for size_t */

int CopyArray(int *arr1, int size1, int *arr2, int size2);
void PrintAdresses ();
void SwapSizeT (size_t *a, size_t *b);
void SwapSizeTPointers (size_t **a, size_t **b);
void SwapInt (int *a, int *b);

int main()
{
	int i = 0;
	int size1, size2;
	int *arr1, *arr2;
	size_t input1, input2;
	size_t *ptr1, *ptr2;
	void *void_ptr1, *void_ptr2;
	size_t *d_ptr;
	size1 = 0;
	size2 = 0;
	arr1 = NULL; 
	arr2 = NULL;
	input1 = 0;
	input2 = 0;
	ptr1 = &input1;
	ptr2 = &input2;
	void_ptr1 = NULL;
	void_ptr2 = NULL;
	d_ptr= (size_t *) malloc(sizeof(size_t));
	
	/* Ex2 */
	printf("\n\n===== Exercise 2 =====\n\n");
	printf("Copy array:\nEner array size \n");
	scanf("%d", &size1);
	printf("Enter valus\n");
	size2 = size1;
	arr1=(int *) malloc (sizeof (int) * size1);
	arr2=(int *) malloc (sizeof (int) * size2);
	
	for (i =0 ; i < size1 ; i++)
		scanf("%d", &arr1[i]);
	
	CopyArray (arr1, size1, arr2, size2);
	printf("The copy array is:\n");
	
	for (i =0 ; i < size1 ; i++)
		printf("%d ", arr2[i]);
	
	printf("\n");
		
	/* Ex3  */
	printf("\n\n===== Exercise 3 =====\n\n");
	PrintAdresses ();
	
	/* Ex4 */
	printf("\n\n===== Exercise 4 =====\n\n");
	printf("Enter two size_t values:\n");
	scanf("%zu", &input1);
	scanf("%zu", &input2);
	printf("\nvalues Before swap:1- %zu 2- %zu\n", input1, input2);
	SwapSizeT(&input1 , &input2);
	printf("values After swap: 1- %zu 2- %zu\n", input1, input2);
	void_ptr1 = &input1;
	void_ptr2 = &input2;
	printf("\nFor local poiners:");
	printf("\nThe adresses before swap pointers:\n1-%p 2-%p\n",
		 void_ptr1, void_ptr2 );
	SwapSizeTPointers(&ptr1, &ptr2);
	void_ptr1 = ptr1;
	void_ptr2 = ptr2;
	printf("\n***The adresses after swap pointers:***\n1-%p 2-%p\n",
		 void_ptr1, void_ptr2 );
	SwapSizeT( (size_t*) &ptr1, (size_t*) &ptr2 );
	void_ptr1 = ptr1;
	void_ptr2 = ptr2;
	printf("\nThe adresses after swap pointers by using swap two size_t:");
	printf("\n1-%p 2-%p\n", void_ptr1 , void_ptr2 );
	SwapInt((int*) (&ptr1), (int*) (&ptr2));
	void_ptr1 = ptr1;
	void_ptr2 = ptr2;
	printf("\nThe adresses after swap pointers by using swap two int:");
	printf("\n1-%p 2-%p\n", void_ptr1, void_ptr2 );
	

	printf("\n***For non-local poiners:***");
	void_ptr1 = ptr1;
	void_ptr2 = d_ptr;
	printf("\nThe adresses before swap pointers:\n1-%p 2-%p\n",
		 void_ptr1, void_ptr2 );
	SwapSizeTPointers(&ptr1, &d_ptr);
	void_ptr1 = ptr1;
	void_ptr2 = d_ptr;
	printf("\nThe adresses after swap pointers:\n1-%p 2-%p\n",
		 void_ptr1, void_ptr2 );
	SwapSizeT( (size_t*) &ptr1, (size_t*) &d_ptr );
	void_ptr1 = ptr1;
	void_ptr2 = d_ptr;
	printf("\nThe adresses after swap pointers by using swap two size_t:");
	printf("\n1-%p 2-%p\n", void_ptr1, void_ptr2 );
	SwapInt((int*) (&ptr1), (int*) (&d_ptr));
	void_ptr1 = ptr1;
	void_ptr2 = d_ptr;
	printf("\nThe adresses after swap pointers by using swap two int:");
	printf("\n1-%p 2-%p\n", void_ptr1, void_ptr2 );

	
	free(arr1);
	free(arr2);
	free(d_ptr);
	
	return 0;
}
