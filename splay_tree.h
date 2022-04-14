#include <stdio.h>
#include <stdlib.h>

#ifndef _SPLAY_TREE_H
#define _SPLAY_TREE_H

struct splay_tree_node;
typedef struct splay_tree_node *splay_tree;
typedef struct splay_tree_node *splay_tree_position;

splay_tree splay_tree_make_empty(splay_tree t); // TODO
splay_tree splay_tree_find(splay_tree t);       // TODO
splay_tree splay_tree_find_min(splay_tree t);   // TODO
splay_tree splay_tree_find_max(splay_tree t);   // TODO
splay_tree splay_tree_initialize(void);
splay_tree splay_tree_insert(int x, splay_tree t);
splay_tree splay_tree_remove(int x, splay_tree t);
int splay_tree_retrieve(splay_tree t); // TODO
splay_tree splay_tree_splay(int item, splay_tree_position x);
splay_tree_position splay_tree_single_rotate_with_left(splay_tree_position p);  // TODO
splay_tree_position splay_tree_single_rotate_with_right(splay_tree_position p); // TODO
splay_tree_position splay_tree_double_rotate_with_left(splay_tree_position p);  // TODO
splay_tree_position splay_tree_double_rotate_with_right(splay_tree_position p); // TODO

struct splay_tree_node
{
        int element;
        splay_tree left;
        splay_tree right;
};

static splay_tree_position NULL_NODE = NULL;

splay_tree splay_tree_initialize(void)
{
        if (NULL_NODE == NULL)
        {
                NULL_NODE = (splay_tree)malloc(sizeof(struct splay_tree_node));
                if (NULL_NODE == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
        }
        return NULL_NODE;
}

splay_tree splay_tree_splay(int item, splay_tree_position x)
{
        static struct splay_tree_node header;
        splay_tree_position left_tree_max, right_tree_min;

        header.left = header.right = NULL_NODE;
        left_tree_max = right_tree_min = &header;

        while (item != x->element)
        {
                if (item < x->element)
                {
                        if (item < x->left->element)
                                x = splay_tree_single_rotate_with_left(x);
                        if (x->right == NULL_NODE)
                                break;
                        left_tree_max->right = x;
                        left_tree_max = x;
                        x = x->right;
                }
        }
        left_tree_max->right = x->left;
        right_tree_min->left = x->right;
        x->left = header.right;
        x->right = header.left;

        return x;
}

splay_tree splay_tree_insert(int item, splay_tree t)
{
        static splay_tree_position new_node = NULL;
        if (new_node == NULL)
        {
                new_node = (splay_tree_position)malloc(sizeof(struct splay_tree_node));
                if (new_node == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
        }
        new_node->element = item;

        if (t == NULL_NODE)
        {
                new_node->left = new_node->right = NULL_NODE;
                t = new_node;
        }
        else
        {
                t = splay_tree_splay(item, t);
                if (item < t->element)
                {
                        new_node->left = t->left;
                        new_node->right = t;
                        t->left = NULL_NODE;
                        t = new_node;
                }
                else if (t->element < item)
                {
                        new_node->right = t->right;
                        new_node->left = t;
                        t->right = NULL_NODE;
                        t = new_node;
                }
                else
                        return t;
        }

        new_node = NULL;
        return t;
}

splay_tree splay_tree_remove(int item, splay_tree t)
{
        splay_tree_position new_tree;

        if (t != NULL_NODE)
        {
                t = splay_tree_splay(item, t);
                if (item == t->element)
                {
                        if (t->left == NULL_NODE)
                                new_tree = t->right;
                        else
                        {
                                new_tree = t->left;
                                new_tree = splay_tree_splay(item, new_tree);
                                new_tree->right = t->right;
                        }
                        free(t);
                        t = new_tree;
                }
        }
        return t;
}

#endif