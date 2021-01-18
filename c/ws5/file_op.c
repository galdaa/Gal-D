/************************************************************************
DESCRIPTION: Menu of opreation on file: 
	append string, remove by "-remove", count lines by "-count",
	add string to start by "<string" and exit by "-exit".
	Using: File functions, funcions pointers, struct, enum ,arry
		and responsibility chain.
Athor: Gal Dahan
Reviewer: Yifat Baruch
*************************************************************************/

#include <string.h> 	/*for string,%s*/
#include <stdio.h> 	/*for print & input*/
#include <string.h> 	/*for compare string functions: strlen, strcpy, strchr, ...*/
#include <stdlib.h>	/*for (void)- unused values, exit, void (*ptr)(int);*/

#define MAX 100	/*max size of string input and copy*/
#define COMMANDS 4	/*num' of commands*/

/*return value for the functions*/
enum return_val 
{
	SUCCEEDED,
	OPEN_FILE_ERROR,
	CLOSE_FILE_ERROR,
	DELETE_FILE_ERROR,
	RENAME_ERROR,
	EXIT_PROGRAM
};

struct chain
{
	char *str; 
	int (*cmp)(char*, char*);
	enum return_val (*operation)(const char*, char*);
};

static void Handler(const char *file_name, const struct chain *choice);
static void Init(struct chain *choice);			/*initial commands*/
static void ErrorPrint(enum return_val value);

/* ----- operation functions ----- */
enum return_val Append(const char *file_name, char* str);	/*add input string to file end*/
enum return_val Remove(const char *file_name, char* str);	/*remove input file*/
enum return_val Count(const char *file_name, char* str);	/*print the lines number of input file*/
enum return_val Exit(const char *file_name, char* str);	/*exit from program running*/
enum return_val StartAdd(const char *file_name, char* str);	/*add input string to file start*/

/* ----- comparison functions ----- */
/*compare between two strings: return the differnce*/
int CmpStr(char *str1, char *str2);
/*compare between firsts chars of two strings: return the differnce*/
int CmpC(char *c1, char *c2);

int main(int argc, char **argv)
{
	char file_name[MAX] = {0};
	struct chain choice[COMMANDS] = {0};
	
	if (2 != argc)
	{
		printf("Worng number of arg's\nShould enter a file name\n");
	
		return 1;
	}
	
	printf("***************************************************\n"
		"When you enter a string or a command:\n"
		"String will be append to the file in new line\n"
		"Commands are:\n"
		"	Remove file by '-remove'\n"
		"	Count lines by '-count'\n"
		"	Add string to start by '<string'\n"
		"	Exit by '-exit'\n"
		"***************************************************\n");
	strcpy(file_name, argv[1]);	
	Init(choice);
	Handler(file_name, choice);		
	
	return 0;
}

static void Handler(const char *file_name, const struct chain *choice)
{
	int flag = 0;
	char input[MAX] = {0};
	enum return_val result = SUCCEEDED;
	
	do
	{
		int i = 0;
		
		flag = 0;
		printf("Enter a string or a command:\n");
		fgets(input, MAX, stdin);
		
		for(i = 0; i < COMMANDS; ++i)
		{
			
			if(0 == (int) choice[i].cmp(choice[i].str, input))
			{
				result = choice[i].operation(file_name, input);
				
				if(SUCCEEDED != result && EXIT_PROGRAM != result)
				{
					printf("Operation failed\n");
					ErrorPrint(result);
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
		
	} while(EXIT_PROGRAM != result);
}

static void ErrorPrint(enum return_val value)
{
	switch (value)
	{
		case OPEN_FILE_ERROR:
			printf("Open file error\n");
			break;	
		case CLOSE_FILE_ERROR:
			printf("Close file error\n");
			break;	
		case DELETE_FILE_ERROR:
			printf("Delete file error\n");
			break;
		case RENAME_ERROR:
			printf("Rename file error\n");
			break;
		default:
			break;
	}
}

static void Init(struct chain *choice)
{
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
}

enum return_val Append(const char *file_name, char* str)
{
	FILE *file = NULL;	
	file = fopen(file_name, "a+");
	
	if( NULL == file)
	{
		return OPEN_FILE_ERROR;
	}
		
	fputs(str, file);
	
	if( -1 == fclose(file))
	{
		return CLOSE_FILE_ERROR;
	}
	
	return SUCCEEDED;
}

enum return_val Remove(const char *file_name, char* str)
{
	(void)str;/*not used*/	
	
	if (0 == remove(file_name))
	{ 
        	return SUCCEEDED; 
        }
   	else
   	{
      		return DELETE_FILE_ERROR;
      	} 
  
}

enum return_val Count(const char *file_name, char* str)
{
	int lines_num = 0;
	int curr_char;
	FILE *file = NULL;
	(void)str;/*not used*/
	file = fopen(file_name, "a+");

	if( NULL == file)
	{
		return OPEN_FILE_ERROR;
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
	
	if(-1 == fclose(file))
	{
		return CLOSE_FILE_ERROR;
	}
	
	return SUCCEEDED;	
}

enum return_val Exit(const char *file_name, char* str)
{
	(void)file_name;/*not used*/
    	(void)str;/*not used*/
	exit(0);
	
	return EXIT_PROGRAM;
}

/*creates a new file copy, add there the str
	and copy there the old files lines and rename 
		to old file name and remove the copy*/	
enum return_val StartAdd(const char *file_name, char* str)
{
	char *copy_name = "Copy.txt";
	char curr_line[MAX] = {0};
	FILE *file = NULL;	
	FILE *copy_file = NULL;

	file = fopen(file_name, "a+");
	
	if( NULL == file)
	{
		return OPEN_FILE_ERROR;
	}
	
	copy_file = fopen(copy_name, "a+");
	
	if( NULL == copy_file)
	{
		printf("Create copy file error\n");
	
		return OPEN_FILE_ERROR;
	}
	
	fputs(str + 1, copy_file);
	
	while(NULL != fgets(curr_line, MAX, file))
	{
		fputs(curr_line, copy_file);
	}
	
	if( -1 == fclose(file))
	{
		return CLOSE_FILE_ERROR;
	}
	
	if( -1 == fclose(copy_file))
	{
		return CLOSE_FILE_ERROR;
	}

	/*run the copy file over the old file*/
	if(-1 == rename(copy_name, file_name))
	{
		return RENAME_ERROR;
	}

	return SUCCEEDED;
}

int CmpStr(char *str1, char *str2)
{
	return strcmp(str1, str2);
}

int CmpC(char *c1, char *c2)
{
	return c1[0] - c2[0];
}

