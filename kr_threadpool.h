#ifndef __KR_THREADPOOL_H__
#define __KR_THREADPOOL_H__

#include <pthread.h>
#include "kr_queue.h"

typedef int (*WorkerFunc)(void *arg);

typedef enum {
    TP_INITIALIZED = '0', 
    TP_SETED, 
    TP_RUNNING,
    TP_SUSPEND,
    TP_FINALIZED
}TP_STATUS;

typedef struct _kr_threadpool_t 
{
    kr_queue_t          *queue;    /*task queue*/
    WorkerFunc          workerfunc;/*function to with the task*/
    unsigned int        nthreads;  /*thread number of this pool*/
    pthread_t           *threads;  /*an array stores all threads*/
    pthread_mutex_t     mutex;     /*mutex of this threadpool*/
    pthread_cond_t      cond;      /*manager tells workers got a new item!*/
    TP_STATUS           status;    /*status of this threadpool*/
} kr_threadpool_t;


/*create a threadpool with <n> threads and <func> thread process function*/
kr_threadpool_t *kr_threadpool_create(unsigned int n, WorkerFunc func);

/*run all of the threads*/
int kr_threadpool_run(kr_threadpool_t *tp);

/*add a task to the queue, main thread invoke this function*/
int kr_threadpool_add_task(kr_threadpool_t *tp, void *task);

/*get a task from the queue, workerthreads invoke this function*/
void *kr_threadpool_get_task(kr_threadpool_t *tp);

/*destroy this threadpool*/
void kr_threadpool_destroy(kr_threadpool_t *tp);

#endif /*__KR_THREADPOOL_H__*/
