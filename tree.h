#include <stdio.h>
#include <stdlib.h>

#ifndef _TREE_H
#define _TREE_H

struct tree_node;
typedef struct tree_node *tree_position;
typedef struct tree_node *tree_search_tree;

tree_search_tree tree_make_empty(tree_search_tree t);
tree_position tree_find(int x, tree_search_tree t);
tree_position tree_find_min(tree_search_tree t);
tree_position tree_find_max(tree_search_tree t);
tree_search_tree tree_insert(int x, tree_search_tree t);
tree_search_tree tree_delete(int x, tree_search_tree t);
int tree_retrieve(tree_position p); // TODO

struct tree_node
{
        int element;
        tree_search_tree left;
        tree_search_tree right;
};

tree_search_tree make_empty_tree(tree_search_tree t)
{
        if (t != NULL)
        {
                tree_make_empty(t->left);
                tree_make_empty(t->right);
                free(t);
        }
        return NULL;
}

tree_position tree_find(int x, tree_search_tree t)
{
        if (t == NULL)
                return NULL;
        if (x < t->element)
                return tree_find(x, t->left);
        else if (x > t->element)
                return tree_find(x, t->right);
        else
                return t;
}

tree_position tree_find_min(tree_search_tree t)
{
        if (t == NULL)
                return NULL;
        else if (t->left == NULL)
                return t;
        else
                return tree_find_min(t->left);
}

tree_position tree_find_max(tree_search_tree t)
{
        if (t != NULL)
        {
                while (t->right != NULL)
                        t = t->right;
        }
        return t;
}

tree_search_tree tree_insert(int x, tree_search_tree t)
{
        if (t == NULL)
        {
                t = (struct tree_node *)malloc(sizeof(struct tree_node));
                if (t == NULL)
                {
                        perror("out of space.");
                        return NULL;
                }
                else
                {
                        t->element = x;
                        t->left = NULL;
                        t->right = NULL;
                }
        }
        else if (x < t->element)
                t->left = tree_insert(x, t->left);
        else if (x > t->element)
                t->right = tree_insert(x, t->right);
        return t;
}

tree_search_tree tree_delete(int x, tree_search_tree t)
{
        tree_position tmp_cell;

        if (t == NULL)
        {
                perror("element not found");
        }
        else if (x < t->element)
                t->left = tree_delete(x, t->left);
        else if (x > t->element)
                t->right = tree_delete(x, t->left);
        else if (t->left && t->right)
        {
                tmp_cell = tree_find_min(t->right);
                t->element = tmp_cell->element;
                t->right = tree_delete(t->element, t->right);
        }
        else
        {
                tmp_cell = t;
                if (t->left == NULL)
                        t = t->right;
                else if (t->right == NULL)
                        t = t->left;
                free(tmp_cell);
        }

        return t;
}

#endif