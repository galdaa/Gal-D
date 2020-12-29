#include <stdio.h>    /* for printf */
#include <string.h>   /* for %s , strcpy*/
#include <strings.h>  /* required for the strcasecmp function */
#include <stdlib.h>   /* for the malloc, free functions */
#include "lib.h"

int main()
{
	char *str1;
	char *str2 = "Hello Word there is a lot of chars in this string!!!";
	char *str3 = "Bye Bye";
	str1 = (char *) malloc(strlen (str2) + 1);
	strcpy(str1, str2);
	Memset(str1, '$', 17);
	printf("%s\n", str1);
	Memcpy(str1, str3, 3);
	printf("%s\n", str1);
	Memmove(str1, str3, 7);
	printf("%s\n", str1);
	Memmove(str1, str2, 25);
	printf("%s\n", str1);
	
	free(str1);
	
	return 0;
}
