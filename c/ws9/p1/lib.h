/*copies the character c (an unsigned char) to the first n 
	characters of the string pointed to, by the argument str.*/
void *Memset(void *str, int c, size_t n);

/* copies n characters from memory area src to memory area dest.*/
void *Memcpy(void *dest, const void * src, size_t n);

/*copies n characters from str2 to str1, but for overlapping memory blocks,
	 memmove() is a safer approach than memcpy().*/
void *Memmove(void *str1, const void *str2, size_t n);
