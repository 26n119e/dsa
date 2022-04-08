#include <stdio.h>
#include <stdlib.h>

#ifndef _LEFT_HEAP_H
#define _LEFT_HEAP_H

struct left_heap_tree_node;
typedef struct left_heap_tree_node *left_heap_priority_queue;

left_heap_priority_queue left_heap_initialize(void);
int left_heap_find_min(left_heap_priority_queue h);
int left_heap_is_empty(left_heap_priority_queue h);
left_heap_priority_queue left_heap_merge(left_heap_priority_queue h1, left_heap_priority_queue h2);
left_heap_priority_queue left_heap_insert1(int x, left_heap_priority_queue h);
left_heap_priority_queue left_heap_delete_min(left_heap_priority_queue h);
static left_heap_priority_queue left_heap_merge1(left_heap_priority_queue h1, left_heap_priority_queue h2);
void left_heap_swap_children(left_heap_priority_queue h);

#define left_heap_insert(x, h) (h = left_heap_insert1((x), h))

struct left_heap_tree_node
{
        int element;
        left_heap_priority_queue left;
        left_heap_priority_queue right;
        int npl;        /* Null path length */
};

static left_heap_priority_queue left_heap_merge1(left_heap_priority_queue h1, left_heap_priority_queue h2)
{
        if (h1->left == NULL)
                h1->left = h2;
        else
        {
                h1->right = left_heap_merge(h1->right, h2);
                if (h1->left->npl < h1->right->npl)
                        left_heap_swap_children(h1);
                h1->npl = h1->right->npl + 1;
        }
        return h1;
}

left_heap_priority_queue left_heap_merge(left_heap_priority_queue h1, left_heap_priority_queue h2)
{
        if (h1 == NULL) return h2;
        if (h2 == NULL) return h1;
        if (h1->element < h2->element) return left_heap_merge1(h1, h2);
        else return left_heap_merge1(h2, h1);
}

left_heap_priority_queue left_heap_insert1(int x, left_heap_priority_queue h)
{
        left_heap_priority_queue single_node;
        
        single_node = (left_heap_priority_queue)malloc(sizeof(struct left_heap_tree_node));
        if (single_node == NULL)
        {
                perror("Out of space.");
                return NULL;
        }
        else
        {
                single_node->element = x;
                single_node->npl = 0;
                single_node->left = single_node->right = NULL;
                h = left_heap_merge(single_node, h);
        }
        return h;
}

left_heap_priority_queue left_heap_delete_min(left_heap_priority_queue h)
{
        left_heap_priority_queue left_heap, right_heap;

        if (left_heap_is_empty(h))
        {
                perror("Priority queue is empty.");
                return h;
        }
        
        left_heap = h->left;
        right_heap = h->right;
        free(h);
        return left_heap_merge(left_heap, right_heap);
}

#endif