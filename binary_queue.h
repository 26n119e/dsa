#include <stdio.h>
#include <stdlib.h>

#ifndef _BINARY_QUEUE_H
#define _BINARY_QUEQU_H
#define BINARY_QUEUE_MAX_TREES_SIZE 100
typedef struct binary_queue_node *binary_queue_bin_tree;
typedef struct binary_queue_collection *binary_queue;

binary_queue_bin_tree binary_queue_combine_trees(binary_queue_bin_tree t1, binary_queue_bin_tree t2);
binary_queue binary_queue_merge(binary_queue h1, binary_queue h2);
int binary_queue_delete_min(binary_queue h);
int binary_queue_is_empty(binary_queue h); // TODO
binary_queue binary_queue_initialize(); // TODO

struct binary_queue_node
{

        int element;
        binary_queue_bin_tree left_child;
        binary_queue_bin_tree next_sibling;
};

struct binary_queue_collection
{
        int current_size;
        binary_queue_bin_tree the_trees[BINARY_QUEUE_MAX_TREES_SIZE];
};

binary_queue_bin_tree binary_queue_combine_trees(binary_queue_bin_tree t1, binary_queue_bin_tree t2)
{
        if (t1->element > t2->element) return binary_queue_combine_trees(t2, t1);
        t2->next_sibling = t1->left_child;
        t1->left_child = t2;
        return t1;
}

binary_queue binary_queue_merge(binary_queue h1, binary_queue h2)
{
        binary_queue_bin_tree t1, t2, carry = NULL;
        int i, j;

        if (h1->current_size + h2->current_size > BINARY_QUEUE_MAX_TREES_SIZE)
        {
                perror("Merge would exceed capacity.");
                return NULL;
        }

        h1->current_size += h2->current_size;
        for (i = 0, j = 1; j <= h1->current_size; i++, j *= 2)
        {
                t1 = h1->the_trees[i];

                switch (!t1 + 2 * !!t2 + 4 * !!carry)
                {
                        case 0:
                        case 1:
                                break;
                        case 2:
                                h1->the_trees[i] = t2;
                                h2->the_trees[i] = NULL;
                                break;
                        case 3:
                                carry = binary_queue_combine_trees(t1, t2);
                                h1->the_trees[i] = h2->the_trees[i] = NULL;
                                break;
                        case 4:
                                h1->the_trees[i] = carry;
                                carry = NULL;
                                break;
                        case 5:
                                carry = binary_queue_combine_trees(t1, carry);
                                h1->the_trees[i] = NULL;
                                break;
                        case 6:
                                carry = binary_queue_combine_trees(t2, carry);
                                h2->the_trees[i] = NULL;
                                break;
                        case 7:
                                h1->the_trees[i] = carry;
                                carry = binary_queue_combine_trees(t1, t2);
                                h2->the_trees[i] = NULL;
                                break;
                }
        }
        return h1;
}

int binary_queue_delete_min(binary_queue h)
{
        int i, j, min_tree, min_item;
        binary_queue deleted_queue;
        binary_queue_bin_tree deleted_tree, old_root;

        if (binary_queue_is_empty(h))
        {
                perror("Empty binomial queue.");
                return -1;
        }

        for (i = 0; i < BINARY_QUEUE_MAX_TREES_SIZE; i++)
        {
                if (h->the_trees[i] && h->the_trees[i]->element < min_item)
                {
                        min_item = h->the_trees[i]->element;
                        min_tree = i;
                }
        }

        deleted_tree = h->the_trees[min_tree];
        old_root = deleted_tree;
        deleted_tree = deleted_tree->left_child;
        free(old_root);

        deleted_queue = binary_queue_initialize();
        deleted_queue->current_size = (1 << min_tree) - 1;
        for (j = min_tree - 1; j >= 0; j--)
        {
                deleted_queue->the_trees[j] = deleted_tree;
                deleted_tree = deleted_tree->next_sibling;
                deleted_queue->the_trees[j]->next_sibling = NULL;
        }
        
        h->the_trees[min_tree] = NULL;
        h->current_size -= deleted_queue->current_size + 1;
        binary_queue_merge(h, deleted_queue);
        return min_item;
}

#endif