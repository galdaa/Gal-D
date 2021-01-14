/*********************************************************
DESCRIPTION: Implementation of Atoi, Itoa for any bases.
	Checking function & macro of Little/Big Endian system.
	Prints the commons letters in two from 3 strings.
	Using: macro, enum.
Author: Gal Dahan
Reviewer: Yuval Ben Ari
**********************************************************/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc, free, atoi, itoa*/
#include <string.h>/*%s, strcpy*/

/*ex1*/
/*convert string number in base10 to int*/
static int AtoiB10(const char *str);

/*convert int number in base10 to string*/
static char *ItoaB10(const int value, char *str);

/*revers string- help for itoa*/
static char *ReverseStr(char *str);

/*convert string number from any base to int*/
static int Atoi(const char *str, const int base);

/*convert int number from any base to string*/
static char *Itoa(const int value, char *str, const int base);

/*run test string on my atoi and original and compare*/
static void TestAtoi(char *str);

/*send test exampels on atoi to TestAtoi*/
static void ExamplesToAtoi(void);

/*run and print ex's 1-4 tests*/
static void ExesTest(void);


/*ex2*/
/*prints the commons letters int first 2 arrays str1,str2 
	but not in str3, O(n), prints the same char only once*/
static void TwoCommon(char *str1, char *str2, char *str3);

/*ex3*/
static void IsLittleEndian(void);

/*ex4*/
#define IS_Little_ENDIAN (*(int *)"1\0\0\0\0\0\0\0" == '1')

int main(void)
{
	ExesTest();
	
	return 0;
}

static void ExesTest(void)
{
	char str[256];
	
	printf("======ex1======\n");
	printf("%d\n", AtoiB10("-364.5"));
	ItoaB10(-67532, str);
	printf("%s\n", str);
	
	printf("%d\n", Atoi("A", 16));
	Itoa(-112586, str, 16);
	printf("%s\n", str);
	
	ExamplesToAtoi();
	
	printf("\n======ex2======\n");
	TwoCommon("abcdefg","bdfghyu","bpplk");
	
	printf("\n======ex3======\n");
	/*by function*/
	IsLittleEndian();
	
	printf("\n======ex4======\n");
	/*by macro*/
	if(IS_Little_ENDIAN)
	{
		printf("Little endian\n");
	}
	else
	{
		printf("Big endian\n");
	}
	
	
}

/*converts the string argument to an integer in 10 base*/
static int AtoiB10(const char *str)
{
	int num = 0;
	int i = 0;
	int sign = 1;
	
	while(' ' == str[i])
	{
		++i;
	}
	
	if('-' == str[i])
	{
		sign = -1;
		++i;
	}
	else if('+' == str[i])
	{
		++i;
	}
	
	while(('0' <= str[i]) && ('9' >= str[i]))
	{
		num *= 10;
		num += ((int) str[i] - (int) '0');
		++i;
	}
	
	return num * sign;
}

#define DIGITS_IN_INT 10
 
/*converts the int argument to a string in 10 base*/
static char *ItoaB10(const int value, char * str)
{
	int i = 0;
	int sign = 1;
	int copy = value;
	
	if (0 > value)
	{
		copy *= -1;
		sign = -1;
	}

	while (0 < copy)
	{
		str[i] = (char) ('0' + (copy % 10));
		copy /= 10;
		++i;
	}
	
	if (-1 == sign)
	{
		str[i] = '-';
		++i;
	}
	
	str[i] = '\0';
	ReverseStr(str);
		
	return str;
}

/*The choice of 36 is convenient in that the digits 
can be represented using the numerals 0–9 and the letters A–Z*/

/*converts the string argument to an integer in any base up to 36 (0-9 a-z)*/
static int Atoi(const char *str, const int base)
{
	int num = 0;
	int i = 0;
	int sign = 1;
	
	while(' ' == str[i])
	{
		++i;
	}
	
	if('-' == str[i])
	{
		sign = -1;
		++i;
	}
	else if('+' == str[i])
	{
		++i;
	}
	
	while ((('0' <= str[i]) && ('0' + base >= str[i]))
		|| ((10 < base) && 
		('A' <= str[i]) && ('A' + (base - 10) >= str[i])))
	{
		num *= base;
		
		if('9' >= str[i])
		{
			num += ((int) str[i] - (int) '0');
		}
		else
		{
			num += (10 + (int) str[i] - (int) 'A');
		}
		
		++i;
	}
	
	return num * sign;
}

#define BITS_IN_INT sizeof(int) * 8
/*converts the int argument to a string in any base up to 36*/
static char *Itoa(const int value, char * str, const int base)
{
	int i = 0;
	int sign = 1;
	int copy = value;
	
	if (0 > value)
	{
		copy *= -1;
		sign = -1;
	}

	while (0 < copy)
	{
		int rest = copy % base;
		
		if(10 > rest)
		{
			str[i] = (char) ('0' + rest);
		}
		else
		{
			str[i] = (char) ('A' + rest - 10);
		}
		
		copy /= base;
		++i;
	}
	
	if (-1 == sign)
	{
		str[i] = '-';
		++i;
	}
	
	str[i] = '\0';
	ReverseStr(str);
		
	return str;
}

/*revers string- swap between left and right values*/
static char *ReverseStr(char *str)
{
	int i = 0;
	int size = strlen(str);
	char temp = '0';
	
	for (i = 0; i < (size / 2); ++i)
	{
		temp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = temp;
	}
	
	return str;
}

static void TestAtoi(char *str)
{
	int my_atoi = 0;
	int original_atoi = 0;
	
  	my_atoi = Atoi(str, 10);
  	original_atoi = atoi(str);
  	printf("My Atoi: %d Original atoi: %d\n", my_atoi, original_atoi);
  	
  	if (original_atoi == my_atoi)
  	{
  		printf("Equal\n");
  	}
  	else
  	{
  		printf("Not equal\n");
  	}
  	
}

static void ExamplesToAtoi(void)
{
	char str[BITS_IN_INT/2];
	int base = 0;
	
	str[0] = 'a';
	printf("Atoi examples:\n");
   	printf("Enter a number string:\n");
  	scanf("%s", str);
  	printf("Enter a base number:\n");
  	scanf("%d", &base);
  	printf("My Atoi (%s,%d): %d \n", str, base,  Atoi(str, base));
  	printf("\nMore Examples:\n");
  	strcpy(str, "-568ABC");
  	printf("%s ",  str);
  	TestAtoi(str);
  	strcpy(str, "A345B9");
  	printf("%s ",  str);
  	TestAtoi(str);
  	strcpy(str, "  339");
  	printf("%s ",  str);
  	TestAtoi(str);
  	strcpy(str, "+15");
  	printf("%s ",  str);
  	TestAtoi(str);
  	 strcpy(str, "A4988");
  	printf("%s ",  str);
  	TestAtoi(str);
  	 strcpy(str, " +52");
  	printf("%s ",  str);
  	TestAtoi(str);
  	strcpy(str, "88 5 2");
  	printf("%s ",  str);
  	TestAtoi(str);
  	
}

/*check Endian by enter an int number seria of bits and check his value*/
static void IsLittleEndian(void)
{
	int i = 0;
	int num = 0;
	char *word = (char *) malloc(sizeof(char)*sizeof(int));
		
	if (NULL == word)
	{
		printf("malloc error\n");
		return;
	}
	
	word[0] = '1';/*first byte is '1'*/
	++i;
	
	while (i < (int) sizeof(int))
	{
		word[i] = '\0';/*next byte is 0*/
		++i;
	}
	
	num = *((int *) word);/*save the bytes in int*/

	if('1' == num)
	{
		printf("Little endian\n");
	}
	else
	{
		printf("Big endian\n");
	}
	
	free(word);
	word = NULL;
}

/*TwoCommon- prints the common letters in only str2,1 by signe 
	in tables of all chars who apper and where*/
#define NUM_OF_CHARS 127
/*in_first mean it appear in str1, to_prinst mean this 
	letter common to str1,2 dont_print mean this letter appear in str3*/
enum print_val {IN_FIRST = '1', TO_PRINT = '2', DONT_PRINT = '\0'};

static void TwoCommon(char *str1, char *str2, char *str3)
{
	char chars_table[127] = { DONT_PRINT };
	int i = 0;
	
	for(i = 0; '\0' != str1[i]; ++i)
	{
		chars_table[(int) str1[i]] = IN_FIRST;
	}
	
	for(i = 0; '\0' != str2[i]; ++i)
	{
		if(IN_FIRST == chars_table[(int) str2[i]])
		{
			chars_table[(int) str2[i]] = TO_PRINT;
		}
	}
	
	for(i = 0; '\0' != str3[i]; ++i)
	{
		chars_table[(int) str3[i]] = DONT_PRINT;
	}
	
	for(i = 0; i < NUM_OF_CHARS ; ++i)
	{
		if(TO_PRINT == chars_table[i])
		{
			printf("%c",(char) i);
		}
	}
	
	printf("\n");
}
