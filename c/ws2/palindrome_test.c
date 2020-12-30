/* *******************************
DESCRIPTION: 
	Test of IfPalindrome.
Athor: Gal Dahan
*********************************/

#include <stdio.h>

size_t StrLen(const char *str);
int IfPalindrome(char *str);

#define MAX_SIZE 50

int main()
{
	char str[MAX_SIZE] = {0};
	
	printf("Eneter a string\n");
	scanf("%s", str); 
	printf("IfPalindrome is:%d\n", IfPalindrome(str));
	
	return 0;
}
