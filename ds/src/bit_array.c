/*********************************************************
ESCRIPTION: Implementation function of Bit Array.
	using: word, bitwise operations, shift..
Athor: Gal Dahan
Reviewer:Snir Cohen
**********************************************************/
#include "bit_array.h"

#define FULL_WORD 0xFFFFFFFFFFFFFFFF
#define WORD_SIZE sizeof(size_t)

/*return full word of one's*/
bit_array_t BitArraySetAll(bit_array_t bit_array)
{
	(void)bit_array;
	return (bit_array_t) FULL_WORD;
}

/*return full word of 0*/
bit_array_t BitArrayResetAll(bit_array_t bit_array)
{
	(void)bit_array;
	return (bit_array_t) 0;
}

/*convert the number to string by mod 2 and copy from end to start*/
char *BitArrayToString(bit_array_t bit_array, char *buffer)
{
	int i = 0;
	bit_array_t copy = bit_array;
	buffer[WORD_SIZE * 8] = '\0';
	
	for(i = WORD_SIZE * 8 - 1; i >= 0; --i)
	{
		buffer[i] = '0' + (copy % 2);
		copy /= 2;
	}
	
	return buffer;
}

/*set bit on by OR 1*/
bit_array_t BitArraySetOn(bit_array_t bit_array, size_t bit_pos)
{
	return bit_array | ((bit_array_t) 1 << bit_pos);
}

/*set bit off by AND ~1*/
bit_array_t BitArraySetOff(bit_array_t bit_array, size_t bit_pos)
{
	return bit_array & ~((bit_array_t) 1 << bit_pos);
}

/*set bit on/off by using BitArraySet On/Off func'*/
bit_array_t BitArraySetBit(bit_array_t bit_array, 
					  size_t bit_pos, 
					  bit_status_t set_val)
{
	if(1 == set_val) 
	{
		return BitArraySetOn(bit_array,bit_pos);
	}
	
	return BitArraySetOff(bit_array,bit_pos);
}

/*get bit value by shift and mod 2*/
bit_status_t BitArrayGetVal(bit_array_t bit_array, size_t bit_pos)
{
	return (bit_array>>bit_pos) % 2;
}

/*flip bit by XOR 1*/
bit_array_t BitArrayFlip(bit_array_t bit_array, size_t bit_pos)
{
	return bit_array ^ ((bit_array_t) 1 << bit_pos);
}

/*mirror word by using shifts*/
bit_array_t BitArrayMirror(bit_array_t bit_array)
{
	bit_array_t copy = bit_array;
	copy = (copy & 0xFFFFFFFF00000000) >> 32| (copy & 0xFFFFFFFF)  << 32;
	copy = (copy & 0xFFFF0000FFFF0000) >> 16| (copy & 0xFFFF0000FFFF)  << 16;
	copy = (copy & 0xFF00FF00FF00FF00) >> 8 | (copy & 0xFF00FF00FF00FF)  << 8;
	copy = (copy & 0xF0F0F0F0F0F0F0F0) >> 4 | (copy & 0xF0F0F0F0F0F0F0F) << 4;
	copy = (copy & 0xCCCCCCCCCCCCCCCC) >> 2 | (copy & 0x3333333333333333) << 2;
	copy = (copy & 0xAAAAAAAAAAAAAAAA) >> 1 | (copy & 0x5555555555555555) << 1;
	
	return copy;
}

/*count bits on by x &(x -1) idea to o(bits on)*/
size_t BitArrayCountOn(bit_array_t bit_array)
{
	size_t count = 0;
	bit_array_t copy = bit_array;
	
	while(0 < copy)
	{
		++count;
		copy &= (copy -1);
	}
	
	return count;
}

/*count bits on by BitArrayCountOn*/
size_t BitArrayCountOff(bit_array_t bit_array)
{
	return BitArrayCountOn(~bit_array);
}

/*rotate right word by shift*/
bit_array_t BitArrayRotateRight(bit_array_t bit_array, size_t num_rotations)
{
	size_t rot = num_rotations % (WORD_SIZE * 8);
	bit_array_t copy = bit_array >> rot;
	copy |= bit_array << ((WORD_SIZE * 8) - rot);/*add the overlapp bits*/
	
	return copy;
}

/*rotate right word by left*/
bit_array_t BitArrayRotateLeft(bit_array_t bit_array, size_t num_rotations)
{
	size_t rot = num_rotations % (WORD_SIZE * 8);
	bit_array_t copy = bit_array << rot;
	copy |= bit_array >> ((WORD_SIZE * 8) - rot);/*add the overlapp bits*/
	
	return copy;
}

