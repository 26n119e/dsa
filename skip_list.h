#include <stdio.h>
#include <stdlib.h>

#ifndef _SKIP_LIST_H
#define _SKIP_LIST_H
struct skip_list_node;
typedef struct skip_list_node *skip_list;
typedef struct skip_list_node *skip_list_position;

struct skip_list_node
{
        int element;
        skip_list right;
        skip_list down;
};

static skip_list_position BOTTOM = NULL;
static skip_list_position TAIL = NULL;

skip_list skip_list_initialize(void);
skip_list_position skip_list_find(int item, skip_list l);
skip_list skip_list_insert(int item, skip_list l);

skip_list skip_list_initialize(void)
{
        skip_list l;

        if (BOTTOM == NULL)
        {
                BOTTOM = (struct skip_list_node *)malloc(sizeof(struct skip_list_node));
                if (BOTTOM == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
                BOTTOM->right = BOTTOM->down = BOTTOM;

                TAIL = (struct skip_list_node *)malloc(sizeof(struct skip_list_node));
                if (TAIL == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
                TAIL->element = 0; // Infinity
                TAIL->right = TAIL;
        }

        l = (struct skip_list_node *)malloc(sizeof(struct skip_list_node));
        if (l == NULL)
        {
                perror("Out of space.");
                return NULL;
        }
        l->element = 0; // Infinity
        l->right = TAIL;
        l->down = BOTTOM;
        return l;
}

skip_list_position skip_list_find(int item, skip_list l)
{
        skip_list_position current = l;
        BOTTOM->element = item;

        while (item != current->element)
        {
                if (item < current->element)
                        current = current->down;
                else
                        current = current->right;
        }
        return current;
}

skip_list skip_list_insert(int item, skip_list l)
{
        skip_list_position current = l;
        skip_list_position new_node;

        BOTTOM->element = item;
        while (current != BOTTOM)
        {
                while (item > current->element)
                        current = current->right;

                if (current->element > current->down->right->right->element)
                {
                        new_node = (struct skip_list_node *)malloc(sizeof(struct skip_list_node));
                        if (new_node == NULL)
                        {
                                perror("Out of space.");
                                return NULL;
                        }
                        new_node->right = current->right;
                        new_node->down = current->down->right->right;
                        current->right = new_node;
                        new_node->element = current->element;
                        current->element = current->down->right->element;
                }
                else
                        current = current->down;
        }

        if (l->right != TAIL)
        {
                new_node = (struct skip_list_node *)malloc(sizeof(struct skip_list_node));
                if (new_node == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
                new_node->down = l;
                new_node->right = TAIL;
                new_node->element = 0; // Infinity
                l = new_node;
        }
        return l;
}
#endif