/*#include <stddef.h>*/
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

/*****************************************
 DESCRIPTION:implemet string functions.
 Athor: Gal Dahan
*****************************************/

int main()
{
	char str1[20]= "abababgggab";
	char str2[20]= "ab";
	char str3[20]= "a";
	char str4[20]= "b";
	char *str_dup1 = NULL;
	char *str_dup2 = NULL;
	int num = 2;

	/*StrCpy*/
	printf("\n\n===== Exercise string =====\n\n");
	printf("\n\n===== Exercise StrCpy =====\n\n");
	strcpy(str3, str1);
	strcpy(str4, str2);
	printf("str1:%s str2:%s\n", str1, str2);
	StrCpy(str2, str1);
	printf("after my StrCpy(str2, str1)\nstr1:%s str2:%s\n", str1, str2);
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	strcpy(str2, str1);
	printf("after strcpy(str2, str1)\nstr1:%s str2:%s\n", str1, str2);
	
	/*StrNCpy*/
	printf("\n\n===== Exercise StrNCpy =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("str1:%s str2:%s\n", str1, str2);
	StrNCpy(str2, str1, num);
	printf("after my StrNCpy(str2, str1, %d)\nstr1:%s str2:%s\n",
		num, str1, str2);
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	strncpy(str2, str1, num);
	printf("after strncpy(str2, str1, %d)\nstr1:%s str2:%s\n",
		num, str1, str2);

	/*StrCaseCmp*/
	printf("\n\n===== Exercise StrCaseCmp =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("str1:%s str2:%s\n", str1, str2);
	printf("after my StrCaseCmp(str2, str1):\n %d\n",
		StrCaseCmp(str2, str1));
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	printf("after strcasecmp(str2, str1):\n %d\n",
		strcasecmp(str2, str1));
	
	/*StrChr*/
	printf("\n\n===== Exercise StrChr =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	num = 'e';
	printf("str1:%s str2:%s\n", str1, str2);
	printf("after my StrChr(str2, %d):\n%s\n", num, StrChr(str2, num));
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	printf("after strchr(str2, %d):\n%s\n", num, strchr(str2, num));
	
	/*StrDup*/
	printf("\n\n===== Exercise StrDup =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	str_dup1 = StrDup(str2);
	printf("str1:%s str2:%s\n", str1, str2);
	printf("after my StrDup(str2)\nstr2:%s recive:%s\n",
		str2, str_dup1);
	strcpy(str1, str3);
	strcpy(str2, str4);
	str_dup2 = StrDup(str2);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	printf("after strdup(str2(str2)\nstr2:%s recive:%s\n",
		str2, str_dup2);	
	
	/*StrCat*/
	printf("\n\n===== Exercise StrCat =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	num = 2;
	printf("str1:%s str2:%s\n", str1, str2);
	StrCat(str2, str1);
	printf("after my StrCat(str2, str1)\nstr1:%s str2:%s\n", str1, str2);
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	strcat(str2, str1);
	printf("after strcat(str2, str1)\nstr1:%s str2:%s\n", str1, str2);
	
	/*StrNCat*/
	printf("\n\n===== Exercise StrNCat =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("str1:%s str2:%s\n", str1, str2);
	StrNCat(str2, str1, num);
	printf("after my StrNCat(str2, str1, %d)\nstr1:%s str2:%s\n",
		num, str1, str2);
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	strncat(str2, str1, num);
	printf("after strncat(str2, str1, %d)\nstr1:%s str2:%s\n",
		num, str1, str2);
	
	/*StrStr*/
	printf("\n\n===== Exercise StrStr =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("str1:%s str2:%s\n", str1, str2);
	printf("after my StrStr(str2, str1)\nstr1:%s str2:%s recive:%s\n",
		str1, str2, StrStr(str2, str1));
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	printf("after strstr(str2, str1)\nstr1:%s str2:%s recive:%s\n",
		str1, str2, strstr(str2, str1));
	
	/*StrSpn*/
	printf("\n\n===== Exercise StrSpn =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("str1:%s str2:%s\n", str1, str2);
	StrSpn(str2, str1);
	printf("after my StrSpn(str2, str1)\n%d\n", (int) StrSpn(str2, str1));
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	printf("after strspn(str2, str1)\n%d\n", (int) strspn(str2, str1));
	
	free(str_dup1);
	free(str_dup2);
	
	return 0;	
}

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

