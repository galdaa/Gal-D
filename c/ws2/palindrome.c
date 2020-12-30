/* *******************************
DESCRIPTION: 
	Implemets of IfPalindrome.
Athor: Gal Dahan
*********************************/

#include <assert.h>  /* assert */
#include <stddef.h> /* size_t */

size_t StrLen(const char *str);
int IfPalindrome(char *str);

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

int IfPalindrome(char *str)
{
	size_t size = 0;
	size_t i = 0;
	
	assert(NULL != str);
	
	size = StrLen(str);
	
	while (i < size/2)
	{
		if (*(str + i) != *(str + size - i - 1))
		{
			return 0;
		}
			
		++i;
	}
	
	return 1;
}
