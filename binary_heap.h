#include <stdio.h>
#include <stdlib.h>

#ifndef _BINARY_HEAP_H
#define _BINARY_HEAP_H
#define MIN_PQ_SIZE 100 /* min priority queue size. */

struct binary_heap;
typedef struct binary_heap *binary_heap_priority_queue;

binary_heap_priority_queue binaray_heap_initialize(int max_elements);
void binary_heap_destroy(binary_heap_priority_queue h);     // TODO
void binary_heap_make_empty(binary_heap_priority_queue h);  // TODO
void binary_heap_insert(int x, binary_heap_priority_queue h);
int binary_heap_delete_min(binary_heap_priority_queue h);
int binary_heap_find_min(binary_heap_priority_queue h);     // TODO
int binary_heap_is_empty(binary_heap_priority_queue h);     // TODO
int binary_heap_is_full(binary_heap_priority_queue h);      // TODO

struct binary_heap
{
        int capacity;
        int size;
        int *elements;
};

binary_heap_priority_queue initialize(int max_elements)
{
        binary_heap_priority_queue h;

        if (max_elements < MIN_PQ_SIZE)
        {
                perror("Priority queue size is too small.");
                return NULL;
        }

        h = (binary_heap_priority_queue)malloc(sizeof(struct binary_heap));
        if (h == NULL)
        {
                perror("Out of space.");
                return NULL;
        }

        h->elements = (int *)malloc((max_elements + 1) * sizeof(int));
        if (h->elements == NULL)
        {
                perror("Out of space.");
                return NULL;
        }

        h->capacity = max_elements;
        h->size = 0;
        h->elements[0] = 0;     /* Here need modify 0 to min data. */
        
        return h;
}

void binary_heap_insert(int x, binary_heap_priority_queue h)
{
        int i;

        if (binary_heap_is_full(h))
        {
                perror("Pirority queue is full.");
                return;
        }

        for (i = ++h->size; h->elements[i / 2] > x; i /= 2)
                h->elements[i] = h->elements[i / 2];
        h->elements[i] = x;
}

int binary_heap_delete_min(binary_heap_priority_queue h)
{
        int i, child;
        int min_element, last_element;

        if (binary_heap_is_empty(h))
        {
                perror("Priority queue is empty.");
                return h->elements[0];
        }

        min_element = h->elements[1];   /* Root node */
        last_element = h->elements[h->size--];

        for (i = 1; i * 2 <= h->size; i = child)
        {
                child = i * 2;
                if (child != h->size && h->elements[child+1] < h->elements[child])
                        child++;
                
                if (last_element > h->elements[child])
                        h->elements[i] = h->elements[child];
                else
                        break;
        }

        h->elements[i] = last_element;
        return min_element;
}

#endif