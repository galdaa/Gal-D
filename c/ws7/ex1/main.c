#include <assert.h>/*for asserts*/
#include <stdio.h>    /* for printf,size_t type */
#include <string.h>   /* for compare string functions: strlen, strcpy, strchr, ... */
#include <strings.h>  /* required for the strcasecmp function */
#include <stdlib.h>   /* for the malloc, free functions */
#include <ctype.h>    /* for the tolower function */
#include "str.h"
/*****************************************
 DESCRIPTION:implemet string functions.
 Athor: Gal Dahan
*****************************************/
int main()
{
	char str1[20]= "abababgggab";
	char str2[20]= "ab";
	char str3[20]= "a";
	char str4[20]= "b";
	char *str_dup1 = NULL;
	char *str_dup2 = NULL;
	int num = 2;

	/*StrCpy*/
	printf("\n\n===== Exercise string =====\n\n");
	printf("\n\n===== Exercise StrCpy =====\n\n");
	strcpy(str3, str1);
	strcpy(str4, str2);
	printf("str1:%s str2:%s\n", str1, str2);
	StrCpy(str2, str1);
	printf("after my StrCpy(str2, str1)\nstr1:%s str2:%s\n", str1, str2);
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	strcpy(str2, str1);
	printf("after strcpy(str2, str1)\nstr1:%s str2:%s\n", str1, str2);
	
	/*StrNCpy*/
	printf("\n\n===== Exercise StrNCpy =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("str1:%s str2:%s\n", str1, str2);
	StrNCpy(str2, str1, num);
	printf("after my StrNCpy(str2, str1, %d)\nstr1:%s str2:%s\n",
		num, str1, str2);
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	strncpy(str2, str1, num);
	printf("after strncpy(str2, str1, %d)\nstr1:%s str2:%s\n",
		num, str1, str2);

	/*StrCaseCmp*/
	printf("\n\n===== Exercise StrCaseCmp =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("str1:%s str2:%s\n", str1, str2);
	printf("after my StrCaseCmp(str2, str1):\n %d\n",
		StrCaseCmp(str2, str1));
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	printf("after strcasecmp(str2, str1):\n %d\n",
		strcasecmp(str2, str1));
	
	/*StrChr*/
	printf("\n\n===== Exercise StrChr =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	num = 'e';
	printf("str1:%s str2:%s\n", str1, str2);
	printf("after my StrChr(str2, %d):\n%s\n", num, StrChr(str2, num));
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	printf("after strchr(str2, %d):\n%s\n", num, strchr(str2, num));
	
	/*StrDup*/
	printf("\n\n===== Exercise StrDup =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	str_dup1 = StrDup(str2);
	printf("str1:%s str2:%s\n", str1, str2);
	printf("after my StrDup(str2)\nstr2:%s recive:%s\n",
		str2, str_dup1);
	strcpy(str1, str3);
	strcpy(str2, str4);
	str_dup2 = StrDup(str2);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	printf("after strdup(str2(str2)\nstr2:%s recive:%s\n",
		str2, str_dup2);	
	
	/*StrCat*/
	printf("\n\n===== Exercise StrCat =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	num = 2;
	printf("str1:%s str2:%s\n", str1, str2);
	StrCat(str2, str1);
	printf("after my StrCat(str2, str1)\nstr1:%s str2:%s\n", str1, str2);
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	strcat(str2, str1);
	printf("after strcat(str2, str1)\nstr1:%s str2:%s\n", str1, str2);
	
	/*StrNCat*/
	printf("\n\n===== Exercise StrNCat =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("str1:%s str2:%s\n", str1, str2);
	StrNCat(str2, str1, num);
	printf("after my StrNCat(str2, str1, %d)\nstr1:%s str2:%s\n",
		num, str1, str2);
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	strncat(str2, str1, num);
	printf("after strncat(str2, str1, %d)\nstr1:%s str2:%s\n",
		num, str1, str2);
	
	/*StrStr*/
	printf("\n\n===== Exercise StrStr =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("str1:%s str2:%s\n", str1, str2);
	printf("after my StrStr(str2, str1)\nstr1:%s str2:%s recive:%s\n",
		str1, str2, StrStr(str2, str1));
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	printf("after strstr(str2, str1)\nstr1:%s str2:%s recive:%s\n",
		str1, str2, strstr(str2, str1));
	
	/*StrSpn*/
	printf("\n\n===== Exercise StrSpn =====\n\n");
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("str1:%s str2:%s\n", str1, str2);
	StrSpn(str2, str1);
	printf("after my StrSpn(str2, str1)\n%d\n", (int) StrSpn(str2, str1));
	strcpy(str1, str3);
	strcpy(str2, str4);
	printf("\nstr1:%s str2:%s\n", str1, str2);
	printf("after strspn(str2, str1)\n%d\n", (int) strspn(str2, str1));
	
	free(str_dup1);
	free(str_dup2);
	
	return 0;	
}

