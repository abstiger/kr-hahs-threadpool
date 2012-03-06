#include "kr_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static char *str[]={ "first", "second", "third", "fourth"};

int main(int argc, char *argv[]) 
{
    int rc = 0;
    kr_queue_t *q = NULL;
    char *pop = NULL;
    
    rc = kr_queue_init(&q, 3);
    assert(rc == 0);
    printf("q=[%p]\n", q);
    assert(q);

    rc = kr_queue_push(q, str[0]);
    assert(rc == 0);
    rc = kr_queue_push(q, str[1]);
    assert(rc == 0);
    rc = kr_queue_push(q, str[2]);
    assert(rc == 0);
    rc = kr_queue_push(q, str[3]);
    assert(rc == -1);
    
    while(!kr_queue_is_empty(q))
    {
        pop = (char *)kr_queue_pop(q);
        assert(pop);
    }    
    
    rc = kr_queue_push(q, str[3]);
    assert(rc == 0);
    
    kr_queue_fini(q);

    printf("Success!\n");
    
    return 0;
}
