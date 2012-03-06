#include "kr_threadpool.h"
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int worker(void * task) 
{
    fprintf(stdout, "worker [%lu] processing task[%s] \n", \
            pthread_self(), (char *)task);
    fflush(stdout);
    //sleep(1);
    return 0;
}

static char *task[]={ "task0", "task1", "task2", "task3", "task4", 
                            "task5", "task6", "task7", "task8", "task9",
                            "task10", "task11", "task12", "task13", "task14", 
                            "task15", "task16", "task17", "task18", "task19"};

int main(void) 
{
    int rc = 0;
    
    kr_threadpool_t *tpool = kr_threadpool_create(5, worker);
    assert(tpool != NULL);
    
    rc = kr_threadpool_run(tpool);
    assert(rc == 0);
    
    int i = 0;
    for (i=0; i<20; i++) {
        kr_threadpool_add_task(tpool, task[i]);
    }
    
    while(!kr_queue_is_empty(tpool->queue)) {
        sleep(1);
    }
    
    kr_threadpool_destroy(tpool);
    
    printf("Success!\n");
    return 0;
}

