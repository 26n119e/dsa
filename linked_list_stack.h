#include <stdio.h>
#include <stdlib.h>

#ifndef _LINKED_LIST_STACK_H
#define _LINKED_LIST_STACK_H

struct linked_list_stack_node;
typedef struct linked_list_stack_node *p_linked_list_stack_node;
typedef p_linked_list_stack_node linked_list_stack;

int linked_list_stack_is_empty(linked_list_stack s);
linked_list_stack linked_list_stack_create(void);
void linked_list_stack_dispose(linked_list_stack s); // TODO
void linked_list_stack_make_empty(linked_list_stack s);
void linked_list_stack_push(int x, linked_list_stack s);
int linked_list_stack_top(linked_list_stack s); // TODO
void linked_list_stack_pop(linked_list_stack s);

struct linked_list_stack_node
{
        int element;
        p_linked_list_stack_node next;
};

int linked_list_stack_is_empty(linked_list_stack s)
{
        return s->next == NULL;
}

void linked_list_stack_make_empty(linked_list_stack s)
{
        if (s == NULL)
        {
                perror("Must use linked_list_stack_create first.");
                return;
        }
        else
                while (!linked_list_stack_is_empty(s))
                        linked_list_stack_pop(s);
}

linked_list_stack linked_list_stack_create(void)
{
        linked_list_stack s = (linked_list_stack)malloc(sizeof(struct linked_list_stack_node));
        if (s == NULL)
        {
                perror("Out of space.");
                return NULL;
        }
        s->next = NULL;
        linked_list_stack_make_empty(s);
        return s;
}

void linked_list_stack_push(int x, linked_list_stack s)
{
        p_linked_list_stack_node tmp_cell;
        tmp_cell = (p_linked_list_stack_node)malloc(sizeof(struct linked_list_stack_node));
        if (tmp_cell == NULL)
        {
                perror("Out of space.");
                return;
        }
        else
        {
                tmp_cell->element = x;
                tmp_cell->next = s->next;
                s->next = tmp_cell;
        }
}

void linked_list_stack_pop(linked_list_stack s)
{
        p_linked_list_stack_node first_cell;
        if (linked_list_stack_is_empty(s))
        {
                perror("Empty stack.");
                return;
        }
        else
        {
                first_cell = s->next;
                s->next = s->next->next;
                free(first_cell);
        }
}

#endif