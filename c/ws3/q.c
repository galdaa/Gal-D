#include <stddef.h>
#include <stdio.h>
#include <string.h>
int main()
{
char str[]="welcome";
int arr[10]={0};
	printf("str:%d\n", (int)sizeof(str));
	printf("strlen:%d\n", (int)strlen(str));
	printf("arr:%d\n", (int)sizeof(arr));
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
