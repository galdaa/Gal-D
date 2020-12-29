/*****************************************************************************
 * Description: Black box tests for Priority Queue Implementation            *
 * Author: Ronny                                                             *
 *                                                                           *
 * Infinity Labs - OL97                                                      *
 *****************************************************************************/

#include <string.h> /* strcmp */
#include "tests.h"
#include "priority_queue.h"

/* Structure Definition */
typedef struct item
{
    int priority;
    char *name;
} item;

/* Function Declerations */
void Tests(void);
static int PriorityFunction(const void *one, const void *other);   
static int CompareName(const void *data, const void *to_erase); 

int main()
{
    Tests();
    PASS;
    return 0;
}

/* main testing function */
void Tests(void)
{
    item item_array[15];
    char items[15][10] = {"baloney", "eyewash", "piddle",  "fluddle", "bouba",
                          "kiki",    "grok",    "wocky",   "chortle", "galumph",
                          "foobar",  "kuzdra",  "sniglet", "wug",     "tove"};
    int priorities[15] = {0 ,3 ,2 ,6 ,3,
                          1, 3, 2, 0, 5,
                          0, 2, 1, 6, -1};
    size_t i = 0;
    pq_t *que = PQCreate(PriorityFunction);
    
    /* initiate 15 items */
    for (; 15 > i; ++i)
    {
        item_array[i].priority = priorities[i];
        item_array[i].name = items[i];
    }
    
    TEST("Create", (NULL == que), 0);
    TEST("New List is Empty", PQIsEmpty(que), 1);
    TEST("Size of New List is 0", PQSize(que), 0);
    
    /* initiate queue with 15 items */
    for (i = 0; 15 > i; ++i)
    {
        TEST("Enqueue", PQEnqueue(que, item_array + i), 0);
    }
    
    TEST("Top Insert", strcmp(((item *)PQPeek(que))->name, "tove"), 0);
    TEST("Insert Size", PQSize(que), 15);
    TEST("Erase",
         strcmp(((item *)PQErase(que, CompareName, "wocky"))->name, "wocky"),
         0);
    TEST("Erase",
         strcmp(((item *)PQErase(que, CompareName, "bouba"))->name, "bouba"),
         0);
    TEST("Erase Nonexistant",
         (NULL == PQErase(que, CompareName, "larkin")),
         1);
    TEST("Dequeue",
         strcmp(((item *)PQDequeue(que))->name, "tove"), 0);
    TEST("Size", PQSize(que), 12);
    
    PQClear(que);
    TEST("Size After Clear", PQSize(que), 0);
    TEST("Cleared Queue is Empty", PQIsEmpty(que), 1);
    
    PQDestroy(que);
}

/* HELPER - function to serve as cmp_func when creating new queue */
static int PriorityFunction(const void *one, const void *other)
{
    /*
     * both one and other are pointers to struct item types
     * comparison is sonde such that if:
     * one.priority < other.priority
     * than one would be positioned before other
     */
     return ((item *)one)->priority - ((item *)other)->priority;
}

/* HELPER - function for to be used as is_match for erasing members */
static int CompareName(const void *data, const void *to_erase)
{
    /*
     * data is being held by current node
     * to_erase is a constant value to which we are comparing
     */
    return !strcmp(((item *)data)->name, (char *)to_erase);
}

/* ʕ •ᴥ•ʔ */
