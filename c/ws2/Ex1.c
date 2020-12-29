#include <stdio.h>
#include <assert.h>


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

int IfPalindrome(char *str)
{
	int size = StrLen(str);
	int i = 0;
	while (i < (int) size/2)
	{
		if (*(str + i) != *(str + size - i - 1))
			return 0;
			
		i++;
	}
	return 1;
}

int main()
{
	char* str = "f11f";
	printf("out is:%d\n", IfPalindrome(str));
	return 0;
}
