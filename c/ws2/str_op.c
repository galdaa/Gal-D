/*****************************************
 DESCRIPTION: Implemet string functions:
	 StrLen, StrCmp, StrCpy, StrNCpy, 
	 StrCaseCmp,StrChr, StrDup, 
	 StrCat, StrNCat, StrStr, StrSpn.
Athor: Gal Dahan
*****************************************/

#include <assert.h>   /*for asserts*/
#include <stdio.h>    /* for printf,size_t type */
#include <string.h>   /* for compare string functions: strlen, strcpy, strchr, ... */
#include <strings.h>  /* required for the strcasecmp function */
#include <stdlib.h>   /* for the malloc, free functions */
#include <ctype.h>    /* for the tolower function */

size_t StrLen(const char *str);
int StrCmp(const char *str1, const char *str2);
char *StrCpy(char *dest, const char *src);
char *StrNCpy(char *dest, const char *src, size_t n);
int StrCaseCmp(const char *s1, const char *s2);
char *StrChr(const char *str, int c);
char *StrDup(const char *src);
char *StrCat(char *dest, const char *src);
char *StrNCat(char *dest, const char *src, size_t n);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *s, const char *accept);

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

