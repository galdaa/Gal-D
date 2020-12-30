#include <stdio.h>/*for printf*/
#include <stdlib.h>/*for malloc,free*/
#include <string.h>/*for strlen,%s,strcmp...*/

/*************************************
DESCRIPTION: Prints the enviorment 
	variables in lower case.
Athor: Gal Dahan
Reviewer: Ronny Efronny
*************************************/

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
  	int size = 0;
  	int size_var = 0;
  	char **buff = NULL;
  	
  	while (envp[i])
  	{
    		++i;
    	}
    	
    	size = i;
	buff = (char **) malloc((size+ 1)*sizeof(char*));
	i = 0;
	
	while (i < size)
  	{
  		int j = 0;
  		
  		size_var = strlen(*(envp + i));
  		*(buff + i) = (char *) malloc((size_var+ 1)*sizeof(char));
    		strcpy(*(buff + i), *(envp + i));
    		
    		/*to lower case*/
    		for(j = 0; j < size_var; ++j)
  		{
  			*(*(buff + i) + j) = tolower(*(*(buff + i) + j));
  		}
  		
  		printf("%s\n", *(buff + i));
    		++i;
    	}
  	
	i = 0;

  	while (i < size)
  	{
  		printf("%s\n", *(buff + i));
    		++i;
    	}
    	

    	for(i = 0; i < size; ++i)
  		free(*(buff + i));
  	
  	free(buff);
  	
    	return 0;
}
