#include <string.h> /*for string,%s*/
#include <stdio.h> /*for print & input*/
#include <string.h>   /* for compare string functions: strlen, strcpy, strchr, ... */
#include <stdlib.h>

#define MAX 100
#define COMMANDS 4

void Append();/*add input string to file end*/
void Remove();/*remove input file*/
void Count();/*print the lines number of input file*/
void Exit();/*exit from program running*/
void StartAdd();/*add input string to file start*/

/*compare between two strings
	-return the differnce*/
int CmpStr(char *str1, char *str2);

/*compare between firsts chars of two strings 
	-return the differnce*/
int CmpC(char *c1, char *c2);

int main()
{
	int i = 0;
	char str[MAX];// = NULL;
	FILE *file_name = NULL;
	
	struct chain
	{
		char *str; 
		int (*cmp)(char*, char*);
		void (*operation)();
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
	
	printf("Enter a command\n");
	fgets(str, MAX, stdin);
	
	for(i = 0; i < COMMANDS; ++i)
	{//printf("%s vs %s %d", choice[i].str, str, choice[i].cmp(choice[i].str, str));
		
		if(0 == (int) choice[i].cmp(choice[i].str, str))
		{
			choice[i].operation();printf("sds");
		}
	}
	
	Append();
	
	return 0;
}

void Append()
{
	int i = 0;
	char str[MAX];
	FILE *file_name = NULL;
	
	printf("Enter a file name for append\n");
	fgets(str, MAX, stdin);	
	file_name = fopen(str, "a+");
	
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

}

void Remove()
{
	int i = 0;
	char file_name[MAX];
	printf("Enter a file name\n");
	fgets(file_name, MAX, stdin);	
	
	if (0 == remove(file_name))
	{ 
        	printf("Deleted successfully"); 
        }
   	else
   	{
      		printf("Unable to delete the file");
      	} 
  
}

void Count()
{
	int i = 0;
	int lines_num = 0;
	int curr_char;
	char str[MAX];
	FILE *file_name = NULL;
	printf("Enter a file name\n");
	fgets(str, MAX, stdin);	
	file_name = fopen(str, "a+");
	/*start add, start add,
	int rename(const char *old, const char *new);,
	remove*/
	if( NULL == file_name)
	{
		printf("Open file error\n");
		return;
	}
	
	curr_char = fgetc(file_name);
	
	while(-1 != curr_char)
	{
		curr_char = fgetc(file_name);
		
		if('\n' == curr_char)
		{
			++lines_num;
		}
		
	}
		
	printf("Numbers of line in this file are:%d\n",lines_num);
	
	if( -1 == fclose(file_name))
	{
		printf("Close file error\n");
	}
		
}

void Exit()
{
	exit(0);
}

void StartAdd()
{
/*shuld create new file add there and copy*/
	int i = 0;
	int lines_num = 0;
	int curr_char;
	char str[MAX];
	FILE *file_name = NULL;
	printf("Enter a file name\n");
	fgets(str, MAX, stdin);	
	file_name = fopen(str, "a+");
	
	if( NULL == file_name)
	{
		printf("Open file error\n");
		return;
	}
	
	curr_char = fgetc(file_name);
	
	while(-1 != curr_char)
	{
		curr_char = fgetc(file_name);
		
		if('\n' == curr_char)
		{
			++lines_num;
		}
		
	}
	
}

int CmpStr(char *str1, char *str2)
{
	return strcmp(str1, str2);
}

int CmpC(char *c1, char *c2)
{
	return c1[0] - c2[0];
}

