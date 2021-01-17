/*************************************************
DESCRIPTION: The program prints the press 
	letter only for A T Esc using if-else.
	Press Exp to end.
	Using: system call "stty -icanon -echo".
Athor: Gal Dahan
Reviewer: Arie Charfnadel
*************************************************/

#include <stdio.h> 	/* for printf*/
#include <stdlib.h>	/* for system*/

#define ESC 27

int main()
{
	char c = 'a'; 
	
	system("stty -icanon -echo");
	scanf("%c", &c);

	while (ESC != c)
	{
		if (('T' == c) || ('A' == c))
		{
			printf("%c pressed\n", c);
		}
		
		scanf("%c", &c);
	}
	
	printf("Esc pressed\n");
	system("stty -icanon echo");
	
	return 0;	
}


