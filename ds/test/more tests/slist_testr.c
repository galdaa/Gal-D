/*****************************************************************************
 * Description: Tests for linked list implementation                         *
 * Author: Ronny                                                             *
 *                                                                           *
 * Infinity Labs - OL97                                                      *
 *****************************************************************************/

#include <stdio.h>  /* printf */
#include <string.h> /* strlen */
#include "slist.h"

/* function declarations */
static void PrintResult(int result);
void TestEverything(void);
static int FindExclamation(const void *one, const void *other);
static int FindSpace(const void *one, const void *other);
static int PrintChars(void *data, void *params);

int main()
{
    TestEverything();
    
    return 0;
}

/* HELPER print test results */
static void PrintResult(int result)
{
    printf("%s\n", result ? "FAILURE" : "SUCCESS");
}

/* test multiple occasions, with multiple result prints */
void TestEverything(void)
{
    int r = 0;
    char a = 'a', f = 'a', t = '!', s = ' ';
    int num = 123;
    char *str = "Hello World!";
    char *runner = str;
    sllist_iter_t itr = NULL;
    sllist_t *lst = SLLCreate();
    
    /* create */
    printf("Creation:    ");
    PrintResult(NULL == lst);
    
    /* push 3 */
    printf("Pushing:     ");
    if ((itr = SLLPushBack(lst, &num)))
        if ((itr = SLLPushBack(lst, &f)))
            if ((itr = SLLPushBack(lst, str)))
                r = 0;
            else
                r = 1;
        else
            r = 1;
    else
        r = 1;
    PrintResult(r);
    
    /* pop 3, then check size */
    printf("Pop/Empty:   ");
    SLLPopBack(lst);
    SLLPopBack(lst);
    SLLPopBack(lst);
    PrintResult(!SLLIsEmpty(lst));
    
    /* big push */
    for (; *runner; ++runner)
    {
        itr = SLLPushBack(lst, runner);
    }
    
    /* check size */
    printf("Size:        ");
    PrintResult(!(strlen(str) == SLLSize(lst)));
    
    /* get 1 data */
    printf("Get one:     ");
    if ('H' == *(char *)SLLGetData(SLLBegin(lst)))
        PrintResult(!('!' == *(char *)SLLGetData(itr)));
    
    /* find and compare node */
    printf("Same/Find:   ");
    itr = SLLFind(lst, &t, &FindExclamation);
    PrintResult(!SLLIsSameIter(SLLNext(itr), SLLEnd(lst)));
    
    /* remove and check for correct removal */
    printf("Remove/For:\n");
    SLLRemove(lst, itr);
    itr = SLLFind(lst, &s, &FindSpace);
    SLLRemove(lst, itr);
    SLLForEach(lst,
                  SLLBegin(lst),
                  SLLEnd(lst),
                  &PrintChars,
                  NULL);
    printf("\nHelloWorld <<< THIS SHOULD APPEAR ABOVE\n");
    
    /* insret and check for correct insertion */
    printf("Insert:      ");
    SLLInsertBefore(lst, SLLBegin(lst), &a);
    SLLSetData(SLLNext(SLLBegin(lst)), &a);
    PrintResult(!(11 == SLLSize(lst)));
    SLLForEach(lst,
              SLLBegin(lst),
              SLLEnd(lst),
              &PrintChars,
              NULL);
    printf("\naaelloWorld <<< THIS SHOULD APPEAR ABOVE\n");
    
    /* destroy list */
    SLLDestroy(lst);
    printf("Destruction: ");
    PrintResult(0);
}

/* HELPER find exclamation point */
static int FindExclamation(const void *one, const void *other)
{
    return !(*(char *)one == *(char *)other);
}

/* HELPER find a space node */
static int FindSpace(const void *one, const void *other)
{
    return !(*(char *)one == *(char *)other);
}

/* HELPER print characters function */
static int PrintChars(void *data, void *params)
{
    if (NULL == data)
    {
        return 1;
    }
    (void)params;
    printf("%c", *(char *)data);
    return 0;
}
