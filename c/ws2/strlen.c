/* *******************************
DESCRIPTION: 
	Implemets of strlen.
Athor: Gal Dahan
*********************************/

#include <stdlib.h> /* for size_t */

size_t StrLen(const char *str)
{
	size_t len = 0;
	
	assert(NULL != str);
	
	while ('\0' != *(str + len))
	{
		len++;
	}
	
	return len;
}
