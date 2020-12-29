/***********************************************
DESCRIPTION: the program prints the press 
	letter only for A T Esc using LTU.
	Press Exp to end.
Athor: Gal Dahan
Reviewer: Arie Charfnadel
***********************************************/

#include <stdio.h> /* for printf*/
#include <stdlib.h>/* for system*/

#define ESC 27

void Apress();
void Tpress();
void Empty();

int main()
{

	char c = 'a'; 
	int i = 0;
	
	void (*funcs[256])(void) ;/*= NULL;*/
	
	for (i = 0; i < 256; i++)
		*(funcs + i) = &Empty;
		
	system("stty -icanon -echo");
	scanf("%c", &c);
	*(funcs + 'A') = &Apress;
	*(funcs + 'T') = &Tpress;
	
	while (ESC != c)
	{
		funcs[(unsigned int) c]();
		scanf("%c", &c);
	}
	
	printf("Esc pressed\n");
	system("stty -icanon echo");
	
	return 0;	
}

void Apress ()
{
	printf("A pressed\n");
}

void Tpress ()
{
	printf("T pressed\n");
}

void Empty()
{
}
