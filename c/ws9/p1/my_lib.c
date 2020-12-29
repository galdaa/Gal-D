/*********************************************************
DESCRIPTION: Implementation of Memset, Memcpy, Memmove.
	Using: pointer casts to copy full 
		word or byte consider alignment.
Athor: Gal Dahan
Reviewer: Avraham Sharon
**********************************************************/

#include <stdio.h>    /* for printf,size_t type */
#include <string.h>   /* for compare string functions: strlen, strcpy, strchr, ... */
#include <strings.h>  /* required for the strcasecmp function */
#include <stdlib.h>   /* for the malloc, free functions */
#include "lib.h"

#define WORD_SIZE sizeof(size_t)

/*copies the character c (an unsigned char) to the first n 
	characters of the string pointed to, by the argument str.
	copy word when it's useful*/
void *Memset(void *str, int c, size_t n)
{
	size_t i = 0;
	char *src_ptr = (char *) &c;
	char *dest_ptr = (char *) str;
	size_t *word_copy = (size_t *) &c;

	for(i = 0; i < WORD_SIZE ; ++i)
	{
		*((char *) word_copy + i) = *src_ptr;
	}
	
	for (i = 0; i < n; )
	{
		/*if there full word or more to copy and the dest 
			in alignment then copy full word*/
		if ((0 < ((n - i) / WORD_SIZE)) 
			&& (0 == (size_t) dest_ptr % (size_t) WORD_SIZE))
		{
			*(size_t *) dest_ptr = *word_copy;/*word copy*/
			/*next word addres*/
			dest_ptr += WORD_SIZE; 
			i += WORD_SIZE;
		}
		else
		{
			*dest_ptr = *src_ptr;/*byte copy*/
			++dest_ptr; /*next byte addres*/
			++i;
		}
		
	}
	
	return str;
}

/* copies n characters from memory area src to memory area dest.
	copy word when it's useful*/
void *Memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	char *src_ptr = (char *) src;
	char *dest_ptr = (char *) dest;
	
	for (i = 0; i < n; )
	{
		/*if there full word or more to copy and the dest in alignment then copy full word*/
		if ((0 < ((n - i) / WORD_SIZE)) && (0 == (size_t) dest_ptr % (size_t) WORD_SIZE))
		{
			*(size_t *) dest_ptr = *(size_t *) src_ptr;/*word copy*/
			dest_ptr += WORD_SIZE; /*next word addres*/
			src_ptr += WORD_SIZE;
			i += WORD_SIZE;
		}
		else
		{
			*dest_ptr = *src_ptr;/*byte copy*/
			++dest_ptr; /*next byte addres*/
			++src_ptr;
			++i;
		}
		
	}
	
	return dest;
}

/*copies n characters from str2 to str1, but for overlapping memory blocks,
	 memmove() is a safer approach than memcpy().
	 copy word when it's useful*/
void *Memmove(void *str1, const void *str2, size_t n)
{
	
	if (str1 == str2)
	{
		return str1;
	}
	
	if (!((str2 < str1) && ((size_t *) str2 + n  > (size_t *) str1)))
	{
		return Memcpy(str1, str2, n);
	}
	else/*reverse copy*/
	{
		size_t i  = 0;
		char *src_ptr = (char *) str2 + (n * WORD_SIZE);
		char *dest_ptr = (char *) str1;
		
		for (i = 0; i < n; )
		{
			/*if there full word or more to copy and the dest and
				src are in alignment then copy full word*/
			if ((0 < ((n - i) / WORD_SIZE)) 
				&& (0 == (size_t) dest_ptr % (size_t) WORD_SIZE) 
				&& (0 == (size_t) src_ptr % (size_t) WORD_SIZE))
			{
				/*word copy*/
				*(size_t*) dest_ptr = *(size_t*) src_ptr;
				/*next word addres*/
				dest_ptr += WORD_SIZE; 
				src_ptr -= WORD_SIZE;
				i += WORD_SIZE;
			}
			else
			{
				*dest_ptr = *src_ptr;/*byte copy*/
				++dest_ptr; /*next byte addres*/
				--src_ptr;
				++i;
			}
			
		}
		
		return str1;
	}
	
}
