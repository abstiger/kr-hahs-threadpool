#include "kr_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int kr_queue_init(kr_queue_t **q, unsigned int hwm) 
{
    /*alloc queue memory*/
    *q = (kr_queue_t *)calloc(1, sizeof(kr_queue_t));
    if(*q == NULL) {
        fprintf(stderr, "calloc kr_queue_t error!\n");
        return -1;
    }

    /*list initial*/
    INIT_LIST_HEAD(&(*q)->head);
    (*q)->len = 0; 
    (*q)->hwm = hwm;
        
    return 0;
}

int kr_queue_push(kr_queue_t *q, void *data)
{
    assert(q);
    
    /*check current queue length*/
    if (q->len >= q->hwm) {
        fprintf(stderr, "queue length [%u] >= high watermark[%u]\n", \
                q->len, q->hwm);
        return -1;
    }
  
    /*create new node*/
    kr_queue_node_t *node = \
        (kr_queue_node_t *)calloc(1, sizeof(kr_queue_node_t));
    if(node == NULL) {
        fprintf(stderr, "calloc kr_queue_node_t error!\n");
        return -1;
    }
    node->data = data;
    INIT_LIST_HEAD(&node->list);
    
printf("push data[%s][%p]\n", (char *)node->data, node->data);
    
    /*add this node to queue's tail*/
    kr_list_add_tail(&node->list, &q->head);
    
    /*add queue's current length*/
    ++q->len;
    
    return 0;
}


void *kr_queue_pop(kr_queue_t *q) 
{
    assert(q);
    
    /*check queue's length*/
    if (q->len <= 0) {
        fprintf(stderr, "queue is empty!\n");
        return NULL;
    }
    
    /*get the queue's head then deleted*/
    kr_queue_node_t *node = NULL;
    node = kr_list_first_entry(&q->head, kr_queue_node_t, list);
    if (node == NULL) {
        fprintf(stderr, "pop queue head error!\n");
        return NULL;
    }
    
printf("pop data[%s][%p]\n", (char *)node->data, node->data);

    /*free node*/
    void *data = node->data;
    kr_list_del(&node->list);
    free(node);
    
    /*subtract queue's current length*/
    --q->len;
    
    return data;
}


int kr_queue_is_empty(kr_queue_t *q)
{
    return kr_list_empty(&q->head);
}


void kr_queue_fini(kr_queue_t *q)
{
    kr_queue_node_t *delnode, *p;
    /* must be safe */
    kr_list_for_each_entry_safe(delnode, p, &q->head, list)
    {
        kr_list_del(&delnode->list);
        free(delnode);
    }
    
    free(q);
}
