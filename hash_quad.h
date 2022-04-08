#include <stdio.h>
#include <stdlib.h>

#ifndef _HASH_QUAD_H
#define _HASH_QUAD_H

#define HASH_QUAD_MIN_TABLE_SIZE 10000

typedef unsigned int hash_quad_position;
struct hash_quad_table;
typedef struct hash_quad_table *p_hash_quad_table;

p_hash_quad_table hash_quad_initialize(int table_size);
void hash_quad_destroy_hash(p_hash_quad_table h); // TODO
hash_quad_position hash_quad_find(int key, p_hash_quad_table h);
void hash_quad_insert(int key, p_hash_quad_table h);
p_hash_quad_table hash_quad_rehash(p_hash_quad_table h);
int hash_quad_next_prime(int x);             // TODO
int hash_quad_hash(int key, int table_size); // TODO

enum hash_quad_kind_of_entry
{
        legitimate,
        empty,
        deleted
};

struct hash_quad_entry
{
        int element;
        enum hash_quad_kind_of_entry info;
};

typedef struct hash_quad_entry hash_quad_cell;

struct hash_quad_table
{
        int table_size;
        hash_quad_cell *the_cells;
};

p_hash_quad_table hash_quad_initialize(int table_size)
{
        p_hash_quad_table h;
        int i;

        if (table_size < HASH_QUAD_MIN_TABLE_SIZE)
        {
                perror("Table size too small.");
                return NULL;
        }

        h = (p_hash_quad_table)malloc(sizeof(struct hash_quad_table));
        if (h == NULL)
        {
                perror("Out of space.");
                return NULL;
        }

        h->table_size = hash_quad_next_prime(table_size);
        h->the_cells = (hash_quad_cell *)malloc(sizeof(hash_quad_cell) * h->table_size);
        if (h->the_cells == NULL)
        {
                perror("Out of space.");
                free(h);
                return NULL;
        }

        for (i = 0; i < h->table_size; i++)
        {
                h->the_cells[i].info = empty;
        }

        return h;
}

hash_quad_position hash_quad_find(int key, p_hash_quad_table h)
{
        hash_quad_position current_pos;
        int collision_num;

        collision_num = 0;
        current_pos = hash_quad_hash(key, h->table_size);

        while (h->the_cells[current_pos].info != empty &&
               h->the_cells[current_pos].element != key)
        {
                current_pos += 2 * ++collision_num - 1;
                if (current_pos >= h->table_size)
                        current_pos -= h->table_size;
        }
        return current_pos;
}

void hash_quad_insert(int key, p_hash_quad_table h)
{
        hash_quad_position pos;

        pos = hash_quad_find(key, h);
        if (h->the_cells[pos].info != legitimate)
        {
                h->the_cells[pos].info = legitimate;
                h->the_cells[pos].element = key;
        }
}

p_hash_quad_table hash_quad_rehash(p_hash_quad_table h)
{
        int i, old_size;
        hash_quad_cell *old_cells;

        old_cells = h->the_cells;
        old_size = h->table_size;

        h = hash_quad_initialize(2 * old_size);
        for (i = 0; i < old_size; i++)
        {
                if (old_cells[i].info == legitimate)
                        hash_quad_insert(old_cells[i].element, h);
        }
        free(old_cells);
        return h;
}

#endif