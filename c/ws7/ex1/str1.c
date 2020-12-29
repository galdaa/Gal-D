#include <assert.h>/*for asserts*/
#include <stdio.h>    /* for printf,size_t type */
#include <string.h>   /* for compare string functions: strlen, strcpy, strchr, ... */
#include <strings.h>  /* required for the strcasecmp function */
#include <stdlib.h>   /* for the malloc, free functions */
#include <ctype.h>    /* for the tolower function */
#include "str.h"
/*****************************************
 DESCRIPTION:implemet string functions.
 Athor: Gal Dahan
*****************************************/
/*return the lenght of string*/
size_t StrLen(const char *str)
{
	size_t len = 0;
	assert(NULL != str);
	
	while ('\0' != *(str + len))
	{
		++len;
	}
	
	return len;
}

/*compare two string and return the difference in int*/
int StrCmp(const char *str1, const char *str2)
{
	int i = 0;
	assert(NULL != str1);
	assert(NULL != str2);
	
	while (('\0' != *(str1 + i)) && (*(str1 + i) == *(str2 + i)))
	{
		++i;
	}
	
	return str1[i] - str2[i];
}

/*copy src to dest*/
char *StrCpy(char *dest, const char *src)
{
	size_t size =  StrLen(src);
	StrNCpy(dest, src, size);
	*(dest + size) = '\0';		
	return dest;
}

/*copy n chars from src to dest*/
char *StrNCpy(char *dest, const char *src, size_t n)
{
	size_t i;
	assert(NULL != dest);
	assert(NULL != src);
	
	for (i = 0; (i < n) && (*(src + i) != '\0'); i++)
	{
		*(dest + i) = *(src + i);
	}
	
	/*Fill the rest of dest with '\0'*/ 
	while (i < n)
	{
   		*(dest + i) = '\0';
   		++i;
   	}

	return dest;
}

