#ifndef __KR_QUEUE_H__
#define __KR_QUEUE_H__

#include "kr_list.h"

#define DEFAULT_HIGH_WATERMARK 100

typedef struct _kr_queue_node_t {
        void *data;
        struct kr_list_head list;
} kr_queue_node_t;

typedef struct _kr_queue_t {
    struct kr_list_head head;     /* head */
    unsigned int        len;       /*current length */
    unsigned int        hwm;       /*high water maker*/
} kr_queue_t;

/* Initialize a queue. */
int kr_queue_init(kr_queue_t **q, unsigned int hwm);

/* Add data to the tail of the queue. */
int kr_queue_push(kr_queue_t *q, void *data);

/* get data from the head of the queue. */
void *kr_queue_pop(kr_queue_t *q);

/* Returns non-zero if the queue is empty. */
int kr_queue_is_empty(kr_queue_t *q);

/* finalize the queue. */
void kr_queue_fini(kr_queue_t *q);

#endif /* __KR_QUEUE_H__ */
