/******************************************
DESCRIPTION: Print size of deference types.
Athor: Gal Dahan
Reviewer: Arie Charfnadel
*******************************************/
#include <stddef.h>
#include <stdio.h>
int main()
{
	printf("size of char:%d\n", (int)sizeof(char));
	printf("size of unsigned char:%d\n", (int)sizeof(unsigned char));
	printf("size of signed char:%d\n", (int)sizeof(signed char));
	printf("size of int:%d\n", (int)sizeof(int));
	printf("size of unsigned int:%d\n", (int)sizeof(unsigned int));
	printf("size of short:%d\n", (int)sizeof(short));
	printf("size of unsigned short :%d\n", (int)sizeof(unsigned short));
	printf("size of long:%d\n", (int)sizeof(long));
	printf("size of long long:%d\n", (int)sizeof(long long));
	printf("size of unsigned long:%d\n", (int)sizeof(unsigned long));
	printf("size of unsigned long long:%d\n", (int)sizeof(unsigned long long));
	printf("size of float:%d\n", (int)sizeof(float));
	printf("size of double:%d\n", (int)sizeof(double)); 
	printf("size of lon double:%d\n", (int)sizeof(long double));
	printf("size of wchar_t:%d\n", (int)sizeof(wchar_t));
	printf("size of size_t:%d\n", (int)sizeof(size_t));
	
return 0;
}
