/***********************************************
DESCRIPTION:
Athor: Gal Dahan
Reviewer: Yifat Baruch
************************************************/

#include <string.h> /*for string,%s*/
#include <stdio.h> /*for print & input*/
#include <string.h>   /* for compare string functions: strlen, strcpy, strchr, ... */
#include <stdlib.h>

#define MAX 100
#define COMMANDS 4

int Append(char *file_name, char* str);/*add input string to file end*/
int Remove(char *file_name, char* str);/*remove input file*/
int Count(char *file_name, char* str);/*print the lines number of input file*/
int Exit(char *file_name, char* str);/*exit from program running*/
int StartAdd(char *file_name, char* str);/*add input string to file start*/

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
		int (*operation)(char*, char*);
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
		{/*printf("%s vs %s %d", choice[i].str, str, 					choice[i].cmp(choice[i].str, str));*/
			
			if(0 == (int) choice[i].cmp(choice[i].str, input))
			{
				choice[i].operation(file_name, input);
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

int Append(char *file_name, char* str)
{
	FILE *file = NULL;	
	file = fopen(file_name, "a+");
	
	if( NULL == file)
	{
		printf("Open file error\n");
	}
		
	fputs(str, file);
	
	if( -1 == fclose(file))
	{
		printf("Close file error\n");
	}
	
	return 0;
}

int Remove(char *file_name, char* str)
{
	(void)str;/*not used*/	
	
	if (0 == remove(file_name))
	{ 
        	printf("Deleted successfully\n"); 
        }
   	else
   	{
      		printf("Unable to delete the file\n");
      	} 
  	
  	return 0;
}

int Count(char *file_name, char* str)
{
	int lines_num = 0;
	int curr_char;
	FILE *file = NULL;
	(void)str;/*not used*/
	file = fopen(file_name, "a+");

	if( NULL == file)
	{
		printf("Open file error\n");
		return -1;
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
	}
	
	return lines_num;	
}

int Exit(char *file_name, char* str)
{
	(void)file_name;/*not used*/
    	(void)str;/*not used*/
	exit(0);
	return 0;
}

/*shuld create a new file add there the str
	and copy the old file and rename for 
		file name and remove the copy*/	
int StartAdd(char *file_name, char* str)
{
	char *copy_name = "Copy.txt";
	char curr_line[MAX];
	FILE *file = NULL;	
	FILE *copy_file = NULL;

	file = fopen(file_name, "a+");
	
	if( NULL == file)
	{
		printf("Open file error\n");
	}
	
	copy_file = fopen(copy_name, "a+");
	
	if( NULL == copy_file)
	{
		printf("Create copy file error\n");
		return -1;
	}
	
	/*start add, start add,
		int rename(const char *old, const char *new);,
			remove*/
	fputs(str + 1, copy_file);
	
	while(NULL != fgets(curr_line, MAX, file))
	{
		fputs(curr_line, copy_file);
	}
	
	if( -1 == fclose(file))
	{
		printf("Close file error\n");
	}
	
	if( -1 == fclose(copy_file))
	{
		printf("Close file error\n");
	}
	
	rename(copy_name, file_name);
	Remove(copy_name, NULL);
	return 0;
}

int CmpStr(char *str1, char *str2)
{
	return strcmp(str1, str2);
}

int CmpC(char *c1, char *c2)
{
	return c1[0] - c2[0];
}

