/*********************************************************
ESCRIPTION: Implementation function of BitArraySetAllTest.
Athor: Gal Dahan
Reviewer:
**********************************************************/
#include <stdio.h>/*printf*/
#include <string.h>/*strcmp*/
#include "bit_array.h"

static void BitArraySetAllTest(void);
static void BitArrayResetAllTest(void);
static void BitArrayToStringTest(void);
static void BitArraySetOnTest(void);
static void BitArraySetOffTest(void);
static void BitArraySetBitTest(void);
static void BitArrayGetValTest(void);
static void BitArrayFlipTest(void);
static void BitArrayMirrorTest(void);
static void BitArrayCountOnTest(void);
static void BitArrayCountOffTest(void);
static void BitArrayRotateRightTest(void);
static void BitArrayRotateLeftTest(void);

#define FULL_WORD 0xFFFFFFFFFFFFFFFF

int main(void)
{
	BitArraySetAllTest();
	BitArrayResetAllTest();
	BitArrayToStringTest();
	BitArraySetOnTest();
	BitArraySetOffTest();
	BitArraySetBitTest();
	BitArrayGetValTest();
	BitArrayFlipTest();
	BitArrayMirrorTest();
	BitArrayCountOnTest();
	BitArrayCountOffTest();
	BitArrayRotateRightTest();
	BitArrayRotateLeftTest();
	
	return 0;
}

static void BitArraySetAllTest(void)
{ 
	bit_array_t cmp_num = FULL_WORD;
	bit_array_t check_num = 0;
	
	if (cmp_num == BitArraySetAll(check_num))
	{ 
		printf("BitArraySetAllTest SUCCESS\n");
	}
	else
	{
		printf("BitArraySetAllTest FAILED\n");
	}
		
}

static void BitArrayResetAllTest(void)
{ 
	bit_array_t cmp_num = 0;
	bit_array_t check_num = FULL_WORD;
	
	if (cmp_num == BitArrayResetAll(check_num))
	{
		printf("BitArrayResetAll SUCCESS\n");
	}
	else
	{
		printf("BitArrayResetAll FAILED\n");
	}
		
}

#define BYTE_SIZE 8
#define WORD_SIZE sizeof(bit_array_t)

static void BitArrayToStringTest(void)
{ 
	char cmp_str[(BYTE_SIZE * WORD_SIZE) + 1];
	char check_str[(BYTE_SIZE * WORD_SIZE) + 1];
	bit_array_t value = FULL_WORD;
	int i = 0;
	/*int num =0;*/
	
	for(i = 0; i < (int) (BYTE_SIZE * WORD_SIZE); ++i)
	{
		cmp_str[i] = '1';
		check_str[i] = '0';
	}
	
	cmp_str[i + 1] = '\0';
	check_str[i + 1] = '\0';
	/*printf("%s\n%s\n", cmp_str, check_str);*/
	BitArrayToString(value, check_str);
	/*num =strcmp(check_str, cmp_str);printf("%d\n",num);*/
	
	if (0 == (strcmp(check_str, cmp_str)))
	{
		printf("BitArrayToStringTest SUCCESS\n");
		/*free(check_str);?*/
	}
	else
	{
		printf("BitArrayToStringTest FAILED:\na%s\nb%s\n", cmp_str, check_str);
	}
		
}

static void BitArraySetOnTest(void)
{ 
	size_t index = 15;/*[index]*/
	bit_array_t cmp_num = 0x8000;
	bit_array_t check_num = 0;
	char check_str[BYTE_SIZE * WORD_SIZE + 1] = {'0'};
	check_num = BitArraySetOn(check_num, index);
	if (cmp_num == BitArraySetOn(check_num, index))
	{
		printf("BitArraySetOnTest SUCCESS\n");
	}
	else
	{
		printf("BitArraySetOnTest FAILED\n%s\n",BitArrayToString(check_num, check_str));
	}
		
}

static void BitArraySetOffTest(void)
{ 
	size_t index = 15;
	bit_array_t cmp_num = FULL_WORD - 0x8000;
	bit_array_t check_num = FULL_WORD;
	
	if (cmp_num == BitArraySetOff(check_num, index))
	{
		printf("BitArraySetOffTest SUCCESS\n");
	}
	else
	{
		printf("BitArraySetOffTest FAILED\n");
	}
		
}

static void BitArraySetBitTest(void)
{ 
	size_t index = 15;
	bit_array_t cmp_num = 0x8000;
	bit_array_t check_num = 0;
	
	if (cmp_num == BitArraySetBit(check_num, index, 1))
	{
		printf("BitArraySetBitTest on SUCCESS\n");
	}
	else
	{
		printf("BitArraySetBitTest on FAILED\n");
	}
	
	cmp_num = 0;
	
	if (cmp_num == BitArraySetBit(check_num, index, 0))
	{
		printf("BitArraySetBitTest off SUCCESS\n");
	}
	else
	{
		printf("BitArraySetBitTest off FAILED\n");
	}
		
}

static void BitArrayGetValTest(void)
{ 
	size_t index = 15;
	bit_status_t cmp_num = 1;
	bit_array_t check_num = 0x8000;
	
	if (cmp_num == BitArrayGetVal(check_num, index))
	{
		printf("BitArrayGetValTest SUCCESS\n");
	}
	else
	{
		printf("BitArrayGetValTest FAILED\n");
	}
	
}

static void BitArrayFlipTest(void)
{ 
	size_t index = 15;
	bit_array_t cmp_num = 0x8000;
	bit_array_t check_num = 0;
	
	if (cmp_num == BitArrayFlip(check_num, index))
	{
		printf("BitArrayFlipTest on SUCCESS\n");
	}
	else
	{
		printf("BitArrayFlipTest on FAILED\n");
	}
	
	cmp_num = 0;
	check_num = 0x8000;
	
	if (cmp_num == BitArrayFlip(check_num, index))
	{
		printf("BitArrayFlipTest off SUCCESS\n");
	}
	else
	{
		printf("BitArrayFlipTest off FAILED\n");
	}
	
}

static void BitArrayMirrorTest(void)
{ 
	bit_array_t cmp_num = 0xFFFFFFFF00000000;
	bit_array_t check_num = 0xFFFFFFFF;
	
	if (cmp_num == BitArrayMirror(check_num))
	{
		printf("BitArrayMirrorTest SUCCESS\n");
	}
	else
	{
		printf("BitArrayMirrorTest FAILED\n");
	}
	
}

static void BitArrayCountOnTest(void)
{ 
	size_t cmp_num = 4;
	bit_array_t check_num = 0x5050;
	
	if (cmp_num == BitArrayCountOn(check_num))
	{
		printf("BitArrayCountOn SUCCESS\n");
	}
	else
	{
		printf("BitArrayCountOn FAILED\n");
	}
	
}

static void BitArrayCountOffTest(void)
{ 
	size_t cmp_num = 4;
	bit_array_t check_num = FULL_WORD - 0x5050;
	
	if (cmp_num == BitArrayCountOff(check_num))
	{
		printf("BitArrayCountOff SUCCESS\n");
	}
	else
	{
		printf("BitArrayCountOff FAILED\n");
	}
	
}

static void BitArrayRotateRightTest(void)
{ 
	size_t num_rotations = 8;
	bit_status_t cmp_num = 0xF;
	bit_array_t check_num = 0xF00;
	
	if (cmp_num == BitArrayRotateRight(check_num, num_rotations))
	{
		printf("BitArrayRotateRightTest SUCCESS\n");
	}
	else
	{
		printf("BitArrayRotateRightTest FAILED\n");
	}
	
}

static void BitArrayRotateLeftTest(void)
{ 
	size_t num_rotations = 8;
	bit_status_t cmp_num = 0xF00;
	bit_array_t check_num = 0xF;
	
	if (cmp_num == BitArrayRotateLeft(check_num, num_rotations))
	{
		printf("BitArrayRotateLeftTest SUCCESS\n");
	}
	else
	{
		printf("BitArrayRotateLeftTest FAILED\n");
	}
	
}

