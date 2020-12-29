/*****************************************************************************
 * Description: Tests for vector worksheet                                   *
 * Author: Ronny                                                             *
 *                                                                           *
 * Infinity Labs - OL97                                                      *
 *****************************************************************************/

#include <stdio.h>
#include "vector.h"

/* function declerations */
static void PrintResult(int result);
int TestChars(void);
int TestInts(void);
int TestUnderflow(void);
int TestSwaps(void);

int main()
{
    PrintResult(TestChars());
    PrintResult(TestInts());
    PrintResult(TestUnderflow());
    PrintResult(TestSwaps());
    
    return 0;
}

/* print test result */
static void PrintResult(int result)
{
    printf("%s\n", result ? "FAILURE" : "SUCCESS");
}

/* test vector of chars */
int TestChars(void)
{
    vector_t *vector = VectorCreate(sizeof(char), 2);
    char a = 'a', b = 'b', c = 'c';
    
    printf("Testing Chars:     ");
    
    if (NULL == vector)
        return 1;
        			printf("\na\n");
    if (VectorPushBack(vector, &a) ||
        VectorPushBack(vector, &b) ||
        VectorPushBack(vector, &c))
        return 1;
    				printf("b\n");
    if (3 != VectorSize(vector))
        return 1;
    				printf("c\n");
    if (VectorPopBack(vector))
        return 1;
				printf("d\n%d\n",(int)VectorSize(vector));
    if (2 != VectorSize(vector))
        return 1;
   				 printf("e\n");
    VectorDestroy(vector);
    
    return 0;
}

/* test vector of ints */
int TestInts(void)
{
    vector_t *vector = VectorCreate(sizeof(int), 1);
    int a = 100, b = 200, c = 300;
    
    printf("Testing Ints:      ");
    
    if (NULL == vector)
        return 1;
    
    if (VectorPushBack(vector, &a))
        return 1;
    
    if (VectorReserve(vector, 4))
        return 1;
    
    if (VectorPushBack(vector, &b) || VectorPushBack(vector, &c))
        return 1;
        
    if (3 != VectorSize(vector))
        return 1;
    
    if (VectorPopBack(vector))
        return 1;

    if (2 != VectorSize(vector))
        return 1;
    
    VectorDestroy(vector);
    
    return 0;
}

/* test underflow with size_t */
int TestUnderflow(void)
{
    vector_t *vector = VectorCreate(sizeof(size_t), 1);
    size_t a = 1UL;
    
    printf("Testing Underflow: ");
    
    if (NULL == vector)
        return 1;
    
    if (VectorPushBack(vector, &a))
        return 1;
    
    if (VectorPopBack(vector))
        return 1;
    
    if (!VectorPopBack(vector))
        return 1;
    
    if (0 != VectorSize(vector))
        return 1;
    
    VectorDestroy(vector);
    
    return 0;
}

/* test value swapping */
int TestSwaps(void)
{
    vector_t *vector = VectorCreate(sizeof(int), 1);
    int a = 100;
    
    printf("Testing Swapping:  ");
    
    if (NULL == vector)
        return 1;
    
    if (VectorPushBack(vector, &a))
        return 1;
    
    if (100 != *(int *)VectorGetAccessToElementAt(vector, 0))
        return 1;
    
    *(int *)VectorGetAccessToElementAt(vector, 0) = 200;
    
    if (200 != *(int *)VectorGetAccessToElementAt(vector, 0))
        return 1;
        
    VectorDestroy(vector);
    
    return 0;
}
