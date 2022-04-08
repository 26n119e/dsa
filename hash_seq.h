#include <stdio.h>
#include <stdlib.h>

#ifndef _HASH_SEQ_H
#define _HASH_SEQ_H

#define HASH_SEQ_MIN_TABLE_SIZE 10000

struct hash_seq_list_node;
typedef struct hash_seq_list_node *hash_seq_position;
struct hash_seq_table;
typedef struct hash_seq_table *p_hash_seq_table;

p_hash_seq_table hash_seq_initialize(int table_size);
void hash_seq_destroy_(p_hash_seq_table h); // TODO
hash_seq_position hash_seq_find(int key, p_hash_seq_table h);
void hash_seq_insert(int key, p_hash_seq_table h);
int hash_seq_retrieve(hash_seq_position p); // TODO
int hash_seq_next_prime(int x);             // TODO
int hash_seq_hash(int key, int table_size); // TODO

struct hash_seq_list_node
{
        int element;
        hash_seq_position next;
};

typedef hash_seq_position hash_seq_list;

struct hash_seq_table
{
        int table_size;
        hash_seq_list *the_lists;
};

p_hash_seq_table hash_seq_initialize(int table_size)
{
        p_hash_seq_table h;
        int i;

        if (table_size < HASH_SEQ_MIN_TABLE_SIZE)
        {
                perror("Table size too small.");
                return NULL;
        }

        h = (p_hash_seq_table)malloc(sizeof(struct hash_seq_table));
        if (h == NULL)
        {
                perror("Out of space.");
                return NULL;
        }

        h->table_size = hash_seq_next_prime(table_size);
        h->the_lists = (hash_seq_list *)malloc(sizeof(hash_seq_list));
        if (h->the_lists == NULL)
        {
                perror("Out of space.");
                free(h);
                return NULL;
        }

        for (i = 0; i < h->table_size; i++)
        {
                h->the_lists[i] = (struct hash_seq_list_node *)malloc(sizeof(struct hash_seq_list_node));
                if (h->the_lists[i] == NULL)
                {
                        perror("Out of space.");
                        free(h->the_lists);
                        free(h);
                        return NULL;
                }
                else
                        h->the_lists[i]->next = NULL;
        }

        return h;
}

hash_seq_position hash_seq_find(int key, p_hash_seq_table h)
{
        hash_seq_position p;
        hash_seq_list l;

        l = h->the_lists[hash_seq_hash(key, h->table_size)];
        p = l->next;

        while (p != NULL && p->element != key)
                p = p->next;

        return p;
}

void hash_seq_insert(int key, p_hash_seq_table h)
{
        hash_seq_position pos, new_cell;
        hash_seq_list l;
        pos = hash_seq_find(key, h);
        if (pos == NULL)
        {
                new_cell = (struct hash_seq_list_node *)malloc(sizeof(struct hash_seq_list_node));
                if (new_cell == NULL)
                {
                        perror("Out of space.");
                        return;
                }
                else
                {
                        l = h->the_lists[hash_seq_hash(key, h->table_size)];
                        new_cell->next = l->next;
                        new_cell->element = key;
                        l->next = new_cell;
                }
        }
}
#endif