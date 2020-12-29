#include <assert.h>/*for asserts*/
#include <stdio.h>    /* for printf,size_t type */
#include <string.h>   /* for compare string functions: strlen, strcpy, strchr, ... */
#include <strings.h>  /* required for the strcasecmp function */
#include <stdlib.h>   /* for the malloc, free functions */
#include <ctype.h>    /* for the tolower function */

#include "str.h"
/*creats new string with the same value and return pointer to there*/
char *StrDup(const char *src)
{
	/*Space for length plus nul*/
	char *dst = NULL; 
	assert(NULL != src);
	dst = (char *) malloc(StrLen (src) + 1);
	
	/*No memory*/
    	if (NULL == dst) 
    	{
    		return NULL; 
    	}         
    		
    	StrCpy(dst, src);
   	return dst;  
}


char *StrCat(char *dest, const char *src)
{
	StrCpy(dest + StrLen(dest), src);
	return dest;
}

char *StrNCat(char *dest, const char *src, size_t n)
{
	size_t size =  StrLen(dest);
	StrNCpy(dest + size, src, n);
	*(dest + size + n) = '\0';
	return dest;
}

