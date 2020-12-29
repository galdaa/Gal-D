/*******************************************************
DESCRIPTION: emplement macros of function and size of,
	using stract to hold deffernt element with 
	function on one type array.	
	Using: macro, pointer arithmetic, struct,
	 static, function's pointer, type cast.
Athor: Gal Dahan
Reviewer: Yuval Krytzer
********************************************************/

#include <stdio.h>    /* for printf,size_t type */
#include <string.h>   /* for compare string functions: strlen, strcpy*/
#include <strings.h>  /* for strcpy*/
#include <stdlib.h>   /* for the malloc, free functions */

/*ex2*/
/*calculate max of 2 and 2 var's using macro*/
#define MAX2(a, b) ((a > b) ? (a) : (b))
#define MAX3(a, b, c)  MAX2(((a) > (b) ? (a) : (b)), (c))

/*ex3*/
/*pointer arithmetic : the next addres - the addres*/
#define SIZEOF_VAR(var) ((size_t)(&(var) + 1) - (size_t)(&(var))) 

/*ex4*/
/*callaulate sizeof type:
	when the type point on 0 and we look for the next place*/
#define SIZEOF_TYPE(t) (((t*)0) + 1)

void UserInterface();

/*user functions for all type: add-int, print, clear*/
void IntAdd(void *num1, int num2);
void FloatAdd(void *num1, int num2);
void StrAdd(void *src, int num);

void IntPrint(void *num);
void FloatPrint(void *num);
void StrPrint(void *src);

void IntClean(void *num);
void FloatClean(void *num);
void StrClean(void *src);

typedef struct 
{
	void *var;
	void (*add)(void*, int);
	void (*print)(void*);
	void (*clean)(void*);
} new_type;
	
int main()
{ 	
	int num = 3;
	/*ex1*/
	UserInterface();
	/*ex 2-4*/
	printf("MAX2 \n%d\n",MAX2(7, 1));
	printf("MAX3 %d\n",MAX3(3, 1, 4));
	printf("SIZEOF_VAR %ld\n", (size_t) SIZEOF_VAR(num));
	printf("SIZEOF_TYPE char %ld\n", (size_t) SIZEOF_TYPE(char));
	printf("SIZEOF_TYPE  new_type %ld\n", (size_t) SIZEOF_TYPE(new_type));
		
	return 0;
}

void UserInterface()
{
	int num1 = 1;
	float f_num = 5.5;
	int num2 = 2;
	char *str1 = NULL;
	char str2[20]= "Hello";
	new_type arr[4];
	
	str1 = (char *) malloc(strlen(str2) + 1);
		
	if (NULL == str1)
	{
		printf("malloc string failed\n");
		return;
	}
	
	/*user interface:*/
	strcpy(str1, str2);
	num1 = 9;

	/*int*/
	arr[0].var = &num1;
	arr[0].add = &IntAdd;
	arr[0].print = &IntPrint;
	arr[0].print(arr[0].var);
	arr[0].add((arr[0].var), num1);
	arr[0].print(arr[0].var);
	arr[0].clean = IntClean;
	arr[0].clean(arr[0].var);
	/*float*/
	arr[1].var = &f_num;
	arr[1].add = &FloatAdd;
	arr[1].add((arr[1].var), num2);
	arr[1].print = &FloatPrint;
	arr[1].print(arr[1].var);
	arr[1].clean = &FloatClean;
	arr[1].clean(arr[1].var);
	/*string*/
	arr[2].var = &str1;
	arr[2].add = &StrAdd;
	arr[2].add((arr[2].var), num1);
	arr[2].print = &StrPrint;
	arr[2].print(arr[2].var);
	arr[2].clean = &StrClean;/*str3 free by StrClean call*/
	arr[2].clean(arr[2].var);
}


/*type cast + dereferance*/
void IntAdd(void *num1, int num2)
{
	*((int*) num1) += num2; 
}

void FloatAdd(void *num1, int num2)
{
	*((float*) num1) += num2;
}

/*converts int to string and copy to static string ,
	creates new copy of string with malloc and add 
	there the convert string, free the old string 
	pointer and redirect him to the copy*/ 
void StrAdd(void *src, int num)
{
	char *dest = NULL;
	static char str2[16];
	sprintf(str2, "%d", num);/*makes the int string*/
	/*alloc space for the old str =(*((char **)src)) + new*/
	dest = (char *) malloc(strlen(*((char **)src)) + strlen (str2) + 1);
	
	if (NULL == dest)
	{
		printf("add string failed\n");
		return;
	}
	
	strcpy(dest, *((char **)src));/*copy old*/
	free(*((char **)src));/*free the old string*/
	strcpy(dest + strlen(dest), str2);/*append new*/
	*((char **)src) = dest;
}

void IntPrint(void *num)
{
	printf("%d \n", *((int*) num));
}

void FloatPrint(void *num)
{
	printf("%f \n", *((float*) num));
}

void StrPrint(void *src)
{
	printf("%s \n", *((char **)src));
}

void IntClean(void *num)
{
	(void) num;
}

void FloatClean(void *num)
{
	(void) num;
}

void StrClean(void* src)
{
	free(*((char **)src));
}


