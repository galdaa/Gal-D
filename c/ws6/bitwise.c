/**************************************************
DESCRIPTION: funcions using Bitwise Operations.
	Using: Bitwise Operations.
Athor: Gal Dahan
Reviewer: Avital Mordechaev
***************************************************/

#include <stdio.h>/*for printf*/

long Pow2(const unsigned int x, const unsigned int y);/*return x*(2^y)*/ 
int IsPow2(const unsigned int n);/*return 1 if n is pow of 2*/
int IsPow2Loop(const unsigned int n);/*return 1 if n is pow of 2*/
unsigned int AddOne(unsigned int n);

/*print the number that have 3 bits on*/
void Print3(const unsigned int *arr,const int size);
unsigned int ByteMirrorLoop(unsigned int num);
unsigned int ByteMirrorLut(unsigned int num);
unsigned int ReversByte(unsigned int num);
unsigned int ReversNibble(unsigned int num);
unsigned int Revers2bits(unsigned int num);
unsigned int CheckBits2and6(unsigned int num);
unsigned int CheckBits2or6(unsigned int num);
unsigned int Swap3and5bits(unsigned int num);

/*return the most close mul' of 16 from down*/ 
unsigned int Get16(unsigned int num);
void swap(int *a, int *b);
int CountSetBits(int num);
int CountSetBits2(int num);
void PrintFloat(float f);

int main()
{
	unsigned int array[] = {3, 7, 9, 12, 1};
	int array_size = 5;
	int in1 = 0;
	int in2 = 0;
	unsigned int us_in1 = 0;
	unsigned int us_in2 = 0;
	float f = 0;
	
	printf("Enter two numbers for pow2\n");
	scanf("%u",&us_in1);
	scanf("%u",&us_in2);
	printf("Pow2(%u,%u) = %ld\n", us_in1, us_in2, Pow2(us_in1,us_in2));
	
	printf("\nEnter a number for IsPow2\n");
	scanf("%d",&in1);
	printf("IsPow2(%d) = %d\n", in1, IsPow2(in1));
	printf("IsPow2Loop(%d) = %d\n", in1, IsPow2Loop(in1));
	
	printf("\nEnter a number for add 1\n");
	scanf("%d",&in1);
	printf("AddOne(%d) %d\n", in1, AddOne(in1));
	
	printf("\nPrints the number with 3 bits on from the array:\n");
	Print3(array, array_size);
	
	printf("\nEnter a number for Byte Mirror\n");
	scanf("%u",&us_in1);
	printf("ReversByte(%d) %u\n", us_in1, ReversByte(us_in1));
	printf("ByteMirrorLoop(%d) %u\n", us_in1, ByteMirrorLoop(us_in1));
	
	printf("\nEnter a number for Check Bits 2,6\n");
	scanf("%u",&us_in1);
	printf("CheckBits2and6 %d\n", CheckBits2and6(us_in1));
	printf("CheckBits2or6 %d \n", CheckBits2or6(us_in1));
	
	printf("\nEnter a number for Swap 3 and 5 bits\n");
	scanf("%u",&us_in1);
	printf("Swap3and5bits(%u) = %u \n", us_in1, Swap3and5bits(us_in1));
	
	printf("\nEnter a number for Get16\n");
	scanf("%u",&us_in1);
	printf("Get16(%u) %u \n", us_in1, Get16(us_in1));
	
	printf("Enter two numbers for swap\n");
	scanf("%d",&in1);
	scanf("%d",&in2);
	printf("swap:%d %d >> ", in1, in2);
	swap(&in1, &in2);
	printf("%d %d \n", in1, in2);
	
	printf("\nEnter a number for Count Set Bits\n");
	scanf("%d",&in1);
	printf("CountSetBits(%d) = %d\n", in1, CountSetBits(in1));
	printf("CountSetBits2(%d) = %d\n", in1, CountSetBits2(in1));
	
	printf("\nEnter a float number for Print Bits\n");
	scanf("%f",&f);
	PrintFloat((float)f);
	
	return 0;
}

long Pow2(const unsigned int x, const unsigned int y)
{
	return (long) (x << y);/*every shift left = *2 */
}

/*check if only one bit is on- if yes that mean the number is pow of 2*/
int IsPow2(const unsigned int n)
{
	if(n & (n-1))
	{
		return 0;
	}
	return 1;
}

/*count the number of on bits- if 1 is mean it is pow of 2*/
int IsPow2Loop(const unsigned int n)
{
	unsigned int copy = n;
	int num_of_bits = 0;
	
	while(0 < copy) 
	{
		if((unsigned int)1 == ((unsigned int) 1 & copy))
		{
			++num_of_bits;
		}
		
		copy = copy >> 1;
	}
	
	if(1 == num_of_bits) 
	{
		return 1;
	}
	
	return 0;
}

unsigned int AddOne(unsigned int n)
{
	unsigned int add = 1;
	unsigned int sol = n;
	
	/*flip the first right bit which his value is 1 as +1 
		until first 0 found*/
	while(sol & add)
	{
		sol = sol ^ add;
		add = add << 1; /*try add to next place*/
	}

	sol = sol ^ add; /*flip the first 0 bit*/
	return sol;
	
}

/*count in loop the nuber in array with 3 bit on and prints them*/
void Print3(const unsigned int *arr,const int size)
{
	int i = 0;
	unsigned int copy = arr[i];
	int num_of_bits = 0;
	
	for(i = 0; i < size; ++i)
	{
		num_of_bits = 0;
		copy = arr[i];
		
		while(0 < copy) 
		{
			/*if the right bit is 1 cout +1*/
			if(1 & copy)
			{
				++num_of_bits;
			}
			
			copy = copy >> 1;
		}
		
		if(3 == num_of_bits)
		{
			printf("%d\n",arr[i]);
		}
	}
}

/*swap the mirror bits by loop with "pointers" to left and right*/
unsigned int ByteMirrorLoop(unsigned int num)
{
	unsigned int start = 1;
	unsigned int end = 1 << 7;
	unsigned int copy = num;
	unsigned int start_on = 0;
	unsigned int end_on = 0;
	
	while(start < end)
	{
		start_on = start & copy;/* > 0 if right bit on*/
		end_on = end & copy;/* > 0 if left bit on*/
		
		if(0 < (unsigned int) start_on)
		{
			copy = copy | end;/*on left*/
		}
		else
		{

			copy = copy & (~end);/*off left*/
		}
		
		if(0 < (unsigned int) end_on)
		{
			copy = copy | start;
		}
		else
		{
			copy = copy & (~start);
		}
		
		end = end >> 1;
		start = start << 1;
	}
	return copy; 
} 

unsigned int ByteMirrorLut(unsigned int num)
{
	unsigned int a = 0;
	unsigned int b = 0;
	unsigned int c = 0;
	unsigned int d = 0;
	unsigned int sol = 0;
	/*sizeof(unsigned int)=4bytes*/
	a = ReversByte((num>>(3*8)) & 255);
	b = ReversByte((num>>(2*8)) & 255);/*255 = full byte*/
	c = ReversByte((num>>(1*8)) & 255);
	d = ReversByte(num & 255);
	sol = (d << (3*8)) | (c << (2*8)) | (b << 8) | a;
	
	return sol;
}

unsigned int ReversByte(unsigned int num)
{
	unsigned int a = num >> 4;
	unsigned int b = num & 15;
	
	return (ReversNibble(b) << 4) | ReversNibble(a);
}

unsigned int ReversNibble(unsigned int num)
{
	unsigned int a = num >> 2;
	unsigned int b = num & 3;
	
	return (Revers2bits(b) << 2) | Revers2bits(a);
}

unsigned int Revers2bits(unsigned int num)
{
	unsigned int a = num >> 1;
	unsigned int b = num & 1;
	
	return (b << 1) | a;
}

unsigned int CheckBits2and6(unsigned int num)
{
	return ((num & 32) >> 5) & ((num & 2) >> 1);
}

unsigned int CheckBits2or6(unsigned int num)
{
	return ((num & 32) >> 5) | ((num & 2) >> 1);
}

unsigned int Swap3and5bits(unsigned int num)
{
	unsigned int copy = (65535 - 16 - 4) & num;/*turn 0f the 5,3 bits*/
	unsigned int third_bit = 4 & num;
	unsigned int fifth_bit = 16 & num;
	return copy | (third_bit << 2) | (fifth_bit >> 2);
}

unsigned int Get16(unsigned int num)
{
	if(0 == (~15 & num))
	{
		return 0;/*erroer value*/
	}
	
	return (~15 & num);/*remove the reminder of 16*/
}

void swap(int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;/*a^b^b=a*/
	*a = *a ^ *b;/*a^b^a=b*/
}

int CountSetBits(int num)
{
	int count = 0;
	int copy = num;
	
	while(0 < copy)
	{
		if(1 == (1 & copy))
		{
			++count;
		}
		
		copy = copy >> 1;
	}
	
	return count;
}

int CountSetBits2(int num)
{   
	int copy = num;	
	copy = copy - ((copy >> 1) & 0x55555555);
	copy = (copy & 0x33333333) + ((copy >> 2) & 0x33333333);
	return (((copy + (copy >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
	
}

void PrintFloat(float f)
{
	int *ptr = (int *)&f;
	int i = 0;

	while((int) (sizeof(float) * 8) > i)
	{
	
		if(0 == (int) (*ptr & 1))
		{
			printf("0");
		}
		else
		{
			printf("1");
		}
		
		++i;		
		*ptr >>= 1;
	}
	
	printf("\n");
}

