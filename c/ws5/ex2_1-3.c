/************************************************************************
DESCRIPTION: menu of opreation on file: 
	append string, remove by "-remove", count lines by "-count",
	add string to start by "<string" and exit by "-exit".
	Using: File functions, funcions pointers, struct, enum and arry.
Athor: Gal Dahan
Reviewer: Yifat Baruch
*************************************************************************/

#include <string.h> /* for string,%s */
#include <stdio.h> /* for print & input */
#include <string.h> /* for compare string functions: strlen, strcpy, strchr, ... */
#include <stdlib.h>/* for (void)- unesd values, exit, void (*ptr)(int); */

#define MAX 100/*max size of string input and copy*/
#define COMMANDS 4/*num' of commands*/

enum return_val {failed = -1, succeeded = 1};/* return value for the functions */

enum return_val Append(char *file_name, char* str);/* add input string to file end */
enum return_val Remove(char *file_name, char* str);/* remove input file */
enum return_val Count(char *file_name, char* str);/* print the lines number of input file */
enum return_val Exit(char *file_name, char* str);/* exit from program running */
enum return_val StartAdd(char *file_name, char* str);/* add input string to file start */

/*compare between two strings
	-return the differnce*/
int CmpStr(char *str1, char *str2);

/*compare between firsts chars of two strings 
	-return the differnce*/
int CmpC(char *c1, char *c2);

int main()
{
	int i = 0;
	int flag = 0;
	char file_name[MAX];
	char input[MAX];
	
	struct chain
	{
		char *str; 
		int (*cmp)(char*, char*);
		enum return_val (*operation)(char*, char*);
	};
	
	struct chain choice[COMMANDS];
	
	choice[0].str = "-remove\n";
	choice[0].cmp = CmpStr;
	choice[0].operation = Remove;
	
	choice[1].str = "-count\n";
	choice[1].cmp = CmpStr;
	choice[1].operation = Count;
	
	choice[2].str = "-exit\n";
	choice[2].cmp = CmpStr;
	choice[2].operation = Exit;
	
	choice[3].str = "<";
	choice[3].cmp = CmpC;/*only for the first char*/
	choice[3].operation = StartAdd;
	
	while(1)
	{
		flag = 0;
		printf("Enter a file name\n");
		fgets(file_name, MAX, stdin);	
		printf("Enter a string or a command\n");
		fgets(input, MAX, stdin);
		
		for(i = 0; i < COMMANDS; ++i)
		{
			
			if(0 == (int) choice[i].cmp(choice[i].str, input))
			{
				if(failed == choice[i].operation(file_name, input))
				{
					printf("Operation failed\n");
				}
				else
				{
					printf("Operation succeeded\n");
				}
				flag = 1;
			}
		}
		
		if(flag == 0)
		{
			Append(file_name, input);
		}
		
	}
	return 0;
}

enum return_val Append(char *file_name, char* str)
{
	FILE *file = NULL;	
	file = fopen(file_name, "a+");
	
	if( NULL == file)
	{
		printf("Open file error\n");
		return failed;
	}
		
	fputs(str, file);
	
	if( -1 == fclose(file))
	{
		printf("Close file error\n");
		return failed;
	}
	
	return succeeded;
}

enum return_val Remove(char *file_name, char* str)
{
	(void)str;/*not used*/	
	
	if (0 == remove(file_name))
	{ 
        	printf("Deleted successfully\n");
        	return succeeded; 
        }
   	else
   	{
      		printf("Unable to delete the file\n");
      		return failed;
      	} 
  
}

enum return_val Count(char *file_name, char* str)
{
	int lines_num = 0;
	int curr_char;
	FILE *file = NULL;
	(void)str;/*not used*/
	file = fopen(file_name, "a+");

	if( NULL == file)
	{
		printf("Open file error\n");
		return failed;
	}
	
	curr_char = fgetc(file);
	
	while(-1 != curr_char)
	{
		curr_char = fgetc(file);
		
		if('\n' == curr_char)
		{
			++lines_num;
		}
		
	}
		
	printf("Numbers of line in this file are:%d\n",lines_num);
	
	if( -1 == fclose(file))
	{
		printf("Close file error\n");
		return failed;
	}
	
	return succeeded;	
}

enum return_val Exit(char *file_name, char* str)
{
	(void)file_name;/*not used*/
    	(void)str;/*not used*/
	exit(0);
	return succeeded;
}

/*creates a new file copy, add there the str
	and copy there the old files lines and rename 
		to old file name and remove the copy*/	
enum return_val StartAdd(char *file_name, char* str)
{
	char *copy_name = "Copy.txt";
	char curr_line[MAX];
	FILE *file = NULL;	
	FILE *copy_file = NULL;

	file = fopen(file_name, "a+");
	
	if( NULL == file)
	{
		printf("Open file error\n");
		return failed;
	}
	
	copy_file = fopen(copy_name, "a+");
	
	if( NULL == copy_file)
	{
		printf("Create copy file error\n");
		return failed;
	}
	
	fputs(str + 1, copy_file);
	
	while(NULL != fgets(curr_line, MAX, file))
	{
		fputs(curr_line, copy_file);
	}
	
	if( -1 == fclose(file))
	{
		printf("Close file error\n");
		return failed;
	}
	
	if( -1 == fclose(copy_file))
	{
		printf("Close file error\n");
		return failed;
	}
	
	rename(copy_name, file_name);/*run the copy file over the old file*/
	return succeeded;
}

int CmpStr(char *str1, char *str2)
{
	return strcmp(str1, str2);
}

int CmpC(char *c1, char *c2)
{
	return c1[0] - c2[0];
}

