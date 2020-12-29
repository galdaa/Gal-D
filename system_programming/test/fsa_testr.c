/******************************************************************************
 * Description:                                                               *
 * Author: Ronny                                                              *
 *                                                                            *
 * Infinity Labs - OL97                                                       *
 ******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <string.h> /* strlen */
#include <stdio.h>/*printf*/
#include "tests.h"
#include "fsa.h"

/*************************** Function Declarations ****************************/
void Tests(void);

int main()
{
    Tests();
    PASS;
    return 0;
}

/******************************** Functions ***********************************/

void Tests(void)
{
    char *str = "Hello World!";
    size_t n = FSASuggestSize(strlen(str), sizeof(char));
    size_t i = 0;
    void *pool = malloc(n);
    void *allocs[12];
    fsa_t *fsa = FSAInit(pool, strlen(str), sizeof(char));
    
    TEST("Suggest", n, 104);
    TEST("CountFree", FSACountFree(fsa), 12);
    for (; 12 > i; ++i)
    {
        allocs[i] = FSAAlloc(fsa);
    }
    TEST("CountFree", FSACountFree(fsa), 0);
    TEST("Full", FSAAlloc(fsa), NULL);

    for (i = 0; 12 > i; ++i)
    {
        FSAFree(fsa, allocs[i]);
    }
    TEST("CountFree", FSACountFree(fsa), 12);
    
    free(pool);
}
