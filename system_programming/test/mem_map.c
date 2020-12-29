#include <stdio.h>
#include <stdlib.h>
#include "mem.h"	/* API */
/*Turning ASLR OFF:
sudo  sh -c 'echo 0 > /proc/sys/kernel/randomize_va_space'
Turning ASLR ON:
sudo  sh -c 'echo 2 > /proc/sys/kernel/randomize_va_space'
*/
/*gd -no-pie mem_map.c */
int g_v;/*0x404054*/
static int s_g;/*0x40404c*/

int g_v_i = 9;/*0x404038*/
static int s_g_i = 5;/*0x40403c*/

const static int c_s_g;/*0x402004*/
const int c_g;/*0x404058*/

const static int c_s_g_i = 4;/*0x402008*/
const int c_g_i = 3;/*0x40200c*/
char *g_sl = "string";/*0x402010*/

static void StatF(void);/*0x4011dc*/
int ExtF(void);/*0x4011f3*/
void ExtF2(int i, int j, int k);/*0x40120a*/

int main/*0x401156*/( int argc/*0x7fffffffdd8c*/, char *argv[]/*0x7fffffffdd80*/, char *envp[]/*0x7fffffffdd78*/ )
{
	int *h, *h2, *h3;
	const int c_l_i = 2;/*0x7fffffffdd94*/
	int l_i = 3;/*0x7fffffffdd98*/
	int l_u;/*0x7fffffffdd9c*/
	const static int c_s_l;/*0x402040*/
	static int s_l;/*0x404050*/
	char *sl = "string";/*0x402010*/

	h = (int *) malloc(sizeof(int) * 3);/*0x4052a0*/
	h2 = (int *) malloc(sizeof(int) * 3);/*0x4052c0*/
	h3 = (int *) malloc(sizeof(int) * 3);/*0x4052e0*/
	StatF();
	ExtF();
	ExtF2(5, 4, 3);
	
	MPrint();
	printf("%d\n", MAdd(7, 3));
	
	l_u = 9;
	
	
	return 0;
}

/*
implicit:
gcc -c -Wall -Werror -fpic mem.c   	-> gcc -c -Wall -Werror -fpic ./src/mem.c ./include/mem.h -I include/
gcc -shared -o libmem.so mem.o  	-> gcc -shared -o ./lib/libmem.so mem.o
gcc -L/home/username/foo***where the lib*** -Wall -o test mem_map.c -lmem
./test					->  gcc -L/home/gal/git/system_programming/lib -Wall -o ./obj/test test/mem_map.c -I include/ -lmem
					***not recommended***
					-> LD_LIBRARY_PATH=/home/gal/git/system_programming/lib:$LD_LIBRARY_PATH
					-> export LD_LIBRARY_PATH=/home/gal/git/system_programming/lib:$LD_LIBRARY_PATH
					 
					 
					 unset LD_LIBRARY_PATH
					
					 ***rpath***
gcc -L/home/username/foo***where the lib*** -Wl,-rpath=/home/username/foo***where the lib*** -Wall -o test mem_map.c -lmem
					->  gcc -L/home/gal/git/system_programming/lib -Wl,-rpath=/home/gal/git/system_programming/lib -Wall -o runtest ./test/mem_map.c ./include/mem.h -lmem -I include/
					->./runtest
*/

static void StatF(void)
{
	printf("static func\n");
}

int ExtF(void)
{
	printf("external func\n");
}

void ExtF2(int i/*0x7fffffffdd5c*/, int j/*0x7fffffffdd58*/, int k/*0x7fffffffdd54*/)
{
	printf("external func2\n");
}
