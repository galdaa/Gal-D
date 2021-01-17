/***************************************************
DESCRIPTION: the program prints the press 
	letter only for A T Esc using switch-case.
	Press Exp to end.
	Using: system call "stty -icanon -echo".
Athor: Gal Dahan
Reviewer: Arie Charfnadel
***************************************************/

#include <stdio.h> /* for printf*/
#include <stdlib.h>/* for system*/

#define ESC 27

int main()
{
	char c = 'a'; 
	system("stty -icanon -echo");
	scanf("%c", &c);

	while (ESC != c)
	{
		switch (c)
		{
			case 'T':	
			case 'A':
				printf("%c pressed\n", c);
				break;
			default:
				break;
		
		}
		
		scanf("%c", &c);
	}
	
	printf("Esc pressed\n");
	system("stty -icanon echo");
	
	return 0;	
}

