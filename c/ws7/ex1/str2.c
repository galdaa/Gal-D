#include <assert.h>/*for asserts*/
#include <stdio.h>    /* for printf,size_t type */
#include <string.h>   /* for compare string functions: strlen, strcpy, strchr, ... */
#include <strings.h>  /* required for the strcasecmp function */
#include <stdlib.h>   /* for the malloc, free functions */
#include <ctype.h>    /* for the tolower function */
#include "str.h"
/*compare two string with no sensitive to capital letters
	return the difference in int*/
int StrCaseCmp(const char *s1, const char *s2)
{
	int i = 0;
	int cmp = 0;
	assert(NULL != s1);
	assert(NULL != s2);

        while ('\0' != *(s1 + i))
	{
		cmp = tolower((int) *(s1 + i)) - tolower((int) *(s2 + i));
		
		if (0 != cmp)
		{
			return cmp;
		}
		
		++i;
	}
	
	return cmp;
}

/*find char in string and return index char* to there*/
char *StrChr(const char *str, int c)
{
	int i = 0;
	char* ptr = NULL;
	assert(NULL != str);
	
	for (i = 0; i < (int) StrLen(str); i++)
	{
	
		if ( *(str + i) == c )
		{
			ptr = (char *) (str + i); 
		}
			
	}
	
	return ptr;
}

