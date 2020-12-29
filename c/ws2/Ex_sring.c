#include <stdio.h>
#include <assert.h>
#include <string.h>

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

int StrCmp(const char *str1, const char *str2)
{
	int i = 0;
	assert(NULL != str1);
	assert(NULL != str2);
	
	while (('\0' != *(str1 + i)) && (*(str1 + i) == *(str2 + i)))
	{
		i++;
	}
	
	return str1[i] - str2[i];
}


int main()
{
	char *str1 = "Aacdefg";
	char *str2 = "Abcdefg";
	printf("For my StrLen(%s): %d\n", str1, (int) StrLen(str1));
	printf("For strlen(%s): %d\n", str1, (int) strlen(str1));
	printf("For my StrCmp(%s, %s):%d\n", str1, str2, StrCmp(str1, str2));	
	printf("For strcmp(%s, %s):%d\n", str1, str2, strcmp(str1, str2));	
	return 0;
}
