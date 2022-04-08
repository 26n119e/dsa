#include <stdlib.h>
#include <stdio.h>

#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

struct linked_list_node;
typedef struct linked_list_node *P_linked_list_node;
typedef P_linked_list_node linked_list;
typedef P_linked_list_node linked_list_position;

struct linked_list_node
{
        int element;
        linked_list_position next;
};

linked_list linked_list_make_empty(linked_list l); // TODO
int linked_list_is_empty(linked_list l);
int linked_list_is_last(linked_list_position p, linked_list l);
linked_list_position linkd_list_find(int x, linked_list l);
void linked_list_delete(int x, linked_list l);
linked_list_position linked_list_find_previous(int x, linked_list l);
void linked_list_insert(int x, linked_list l, linked_list_position p);
void linked_list_delete_list(linked_list l);                      // TODO
linked_list_position linked_list_header(linked_list l);           // TODO
linked_list_position linked_list_first(linked_list l);            // TODO
linked_list_position linked_list_advance(linked_list_position p); // TODO
int linked_list_retrieve(linked_list_position p);                 // TODO

int linked_list_is_empty(linked_list l)
{
        return l->next == NULL;
}

int linked_list_is_last(linked_list_position p, linked_list l)
{
        return p->next == NULL;
}

linked_list_position linkd_list_find(int x, linked_list l)
{
        linked_list_position p;
        p = l->next;
        while (p != NULL && p->element != x)
                p = p->next;
        return p;
}

linked_list_position linked_list_find_previous(int x, linked_list l)
{
        linked_list_position p;
        p = l;

        while (p->next != NULL && p->next->element != x)
                p = p->next;
        return p;
}

void linked_list_delete(int x, linked_list l)
{
        linked_list_position p, tmp_cell;
        p = linked_list_find_previous(x, l);
        if (!linked_list_is_last(p, l))
        {
                tmp_cell = p->next;
                p->next = tmp_cell->next;
                free(tmp_cell);
        }
}

void linked_list_insert(int x, linked_list l, linked_list_position p)
{
        linked_list_position tmp_cell;

        tmp_cell = malloc(sizeof(struct linked_list_node));
        if (tmp_cell == NULL)
        {
                perror("Out of space.");
                return;
        }
        tmp_cell->element = x;
        tmp_cell->next = p->next;
        p->next = tmp_cell;
}

#endif