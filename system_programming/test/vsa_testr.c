/******************************************************************************
 * Description:                                                               *
 * Author: Ronny                                                              *
 *                                                                            *
 * Infinity Labs - OL97                                                       *
 ******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <string.h> /* strlen */
#include "tests.h"
#include "vsa.h"

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
    void *pool = malloc(5000);
    vsa_t *vsa = VSAInit(pool, 5000);
    char *str = "Hello World!";
    size_t str_size = strlen(str); 
    char *str_blocks[12];
    size_t num_size = 10;
    int num[10] = {1, 2, 3, 4, 5, 6, 8, 9, 10};
    int *num_blocks[10];
    size_t i = 0;
    void *merged = NULL;
    
    for (; str_size > i; ++i)
    {
        str_blocks[i] = (char *)VSAAlloc(vsa, sizeof(char));
        *str_blocks[i] = *(str + i);
        TEST("Allocate", (NULL != str_blocks[i]), 1);
    }
    
    for (i = 0; num_size > i; ++i)
    {
        num_blocks[i] = (int *)VSAAlloc(vsa, sizeof(int));
        *num_blocks[i] = *(num + i);
        TEST("Allocate", (NULL != num_blocks[i]), 1);
    }
    
    for (i = 0; str_size > i; ++i)
    {
        if (!(i % 3))
        {
            VSAFree(str_blocks[i]);
            str_blocks[i] = NULL;
        }
        else
        {
            TEST("Correct Value", *str_blocks[i], *(str + i));
        }
    }
    
    for (i = 0; num_size > i; ++i)
    {
        if (!(i % 2))
        {
            VSAFree(num_blocks[i]);
            num_blocks[i] = NULL;
        }
        else
        {
            TEST("Correct Value", *num_blocks[i], *(num + i));
        }
    }
    
    VSAFree(num_blocks[1]);
    VSAFree(num_blocks[3]);
    merged = VSAAlloc(vsa, 30);
    TEST("Merge", ((int *)merged < num_blocks[9]), 1);
    
   TEST("Not Enough Space", (NULL == VSAAlloc(vsa, 6000)), 1);
       
    free(pool);
}
