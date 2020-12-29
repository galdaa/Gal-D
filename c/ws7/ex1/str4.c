#include <assert.h>/*for asserts*/
#include <stdio.h>    /* for printf,size_t type */
#include <string.h>   /* for compare string functions: strlen, strcpy, strchr, ... */
#include <strings.h>  /* required for the strcasecmp function */
#include <stdlib.h>   /* for the malloc, free functions */
#include <ctype.h>    /* for the tolower function */

#include "str.h"
/*finds the first occurrence of the substring needle 
	in the string haystack.
	The terminating null bytes ('\0') are  not compared.*/
char *StrStr(const char *haystack, const char *needle)
{
	int i = 0;
	int n_i = 0;
	int flag = 1;
	assert(NULL != haystack);
	assert(NULL != needle);
	
	/*while have enough space for needle*/	
	while ((StrLen(haystack) - i) >= StrLen(needle))
	{
		n_i = 0;
		flag = 1;
		
		while (n_i < (int) StrLen(needle))
		{
		
			if (*(haystack +i + n_i) != *(needle + n_i))
			{
				flag = 0;
			}
					
			++n_i;
		}
		
		if (1 == flag)
		{
			return (char *) (haystack +i);
		}
		
		++i;

	}
		
	return NULL;	
}

/*calculates the length of the initial
	segment of s which consists entirely of bytes in accept.*/
size_t StrSpn(const char *s, const char *accept)
{
	size_t val = 0;
	int s_i = 0;
	assert(NULL != s);
	assert(NULL != accept);
	
	while ('\0' != *(s + s_i))
	{
		
		if (NULL == StrChr(accept, *(s + s_i)))
		{
			return val;
		}
		
		++val;	
		++s_i;
	}
	
	return val;
}

