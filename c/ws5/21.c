#include <string.h> /*for string,%s*/
#include <stdio.h> /*for print & input*/
#include <string.h>   /* for compare string functions: strlen, strcpy, strchr, ... */
#include <stdlib.h>

#define MAX 100

int main()
{
	char str[MAX];// = NULL;
	FILE *file_name = NULL;
	printf("Enter an option ('-addend' for append string to file)\n");
	fgets(str, MAX, stdin);
	
	
	printf("Enter a file name\n");
	fgets(str, MAX, stdin);	
	file_name = fopen(str, "a+") ;
	
	if( NULL == file_name)
	{
		printf("Open file error\n");
	}
		
	printf("Enter a string\n");
	fgets(str, MAX, stdin);
	fputs(str, file_name);
	
	if( -1 == fclose(file_name))
	{
		printf("Close file error\n");
	}
	
	return 0;
}

/*close() closes a file descriptor, so that it no longer refers to any file and may be reused.*/
