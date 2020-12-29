/*****************************************************************************
 * Description:                                                              *
 * Author: Ronny                                                             *
 *                                                                           *
 * Infinity Labs - OL97                                                      *
 *****************************************************************************/

#include <string.h> /* strlen */
#include "queue.h"
#include "tests.h"

void TestBasics(void);
void TestAppend(void);

int main()
{
    TestBasics();
    TestAppend();
    
    PASS;
    return 0;
}

void TestBasics(void)
{
    queue_t *queue = QCreate();
    char *str = "Hello World!";
    size_t n = strlen(str), i = 0;
    
    for (; n > i; ++i)
    {
        QEnqueue(queue, str + i);
    }
    TEST("Enqueue", QSize(queue), 12);
    
    for (i = 0; 4 > i; ++i)
    {
        QDequeue(queue);
    }
    TEST("Dequeue", QSize(queue), 8);
    TEST("Peek", *(char *)QPeek(queue), 'o');
    
    QDestroy(queue);
}

void TestAppend(void)
{
    queue_t *src_que = QCreate(), *dst_que = QCreate();
    char *src_str = "this is a src";
    char *dst_str = "this is a dst";
    size_t n = strlen(src_str), i = 0;
    
    for (; n > i; ++i)
    {
        QEnqueue(dst_que, dst_str + i);
        QEnqueue(src_que, src_str + i);
    }
    
    QAppend(src_que, dst_que);
    TEST("Append (dst)", QSize(dst_que), n * 2);
    TEST("Append (src)", QIsEmpty(src_que), 1);
    
    /* try to append an empty list */
    QAppend(src_que, dst_que);
    QAppend(dst_que, src_que);
    TEST("Reverse Append (dst)", QIsEmpty(dst_que), 1);
    TEST("Reverse Append (src)", QSize(src_que), n * 2);
    
    QDestroy(src_que);
    QDestroy(dst_que);
}
