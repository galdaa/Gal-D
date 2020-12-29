#include <stdio.h>
#include <stdlib.h>

extern char etext, edata, end;

int main() {
    printf("First address past:\n");
    printf("    program text (etext)      %10p\n", &etext);
    printf("    initialized data (edata)  %10p\n", &edata);
    printf("    uninitialized data (end)  %10p\n", &end);

    exit(EXIT_SUCCESS);
}

/*
First address past:
    program text (etext)        0x401265
    initialized data (edata)    0x404040
    uninitialized data (end)    0x404048
*/
