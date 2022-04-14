#include <stdio.h>
#include <stdlib.h>

#ifndef _RED_BLACK_TREE_H
#define _RED_BLACK_TREE_H
typedef enum color_type
{
        red,
        black
} color_type;

struct red_black_tree_node;
typedef struct red_black_tree_node *red_black_tree;
typedef struct red_black_tree_node *red_black_tree_position;
red_black_tree_position NULL_NODE = NULL;

red_black_tree red_black_tree_initialization(void);
static red_black_tree_position red_black_tree_rotate(int item, red_black_tree_position parent);
red_black_tree_position red_black_tree_single_rotate_with_left(red_black_tree_position p);  // TODO
red_black_tree_position red_black_tree_single_rotate_with_right(red_black_tree_position p); // TODO
/* x: current node
** p: parent node
** gp: grandparent node
** ggp: grandgrandparent node ?
*/
static red_black_tree_position x, p, gp, ggp;
static void red_black_tree_handler_reorient(int item, red_black_tree t);
red_black_tree red_black_tree_insert(int item, red_black_tree t);

struct red_black_tree_node
{
        int element;
        red_black_tree left;
        red_black_tree right;
        color_type color;
};

red_black_tree red_black_tree_initialization(void)
{
        red_black_tree t;
        if (NULL_NODE == NULL)
        {
                NULL_NODE = (struct red_black_tree_node *)malloc(sizeof(struct red_black_tree_node));
                if (NULL_NODE == NULL)
                {
                        perror("Out of space.");
                        return NULL;
                }
                NULL_NODE->left = NULL_NODE->right = NULL_NODE;
                NULL_NODE->color = black;
                NULL_NODE->element = 0; // Infinity;
        }

        t = (struct red_black_tree_node *)malloc(sizeof(struct red_black_tree_node));
        if (t == NULL)
        {
                perror("Out of space.");
                return NULL;
                t->element = 0; // NegInfinity;
                t->left = t->right = NULL_NODE;
                t->color = black;
        }
        return t;
}

static red_black_tree_position red_black_tree_rotate(int item, red_black_tree_position parent)
{
        if (item < parent->element)
                return parent->left = item < parent->left->element ? red_black_tree_single_rotate_with_left(parent->left) : red_black_tree_single_rotate_with_right(parent->left);
        else
                return parent->right = item < parent->right->element ? red_black_tree_single_rotate_with_left(parent->right) : red_black_tree_single_rotate_with_right(parent->right);
}

static void red_black_tree_handler_reorient(int item, red_black_tree t)
{
        x->color = red;
        x->left->color = black;
        x->right->color = black;

        if (p->color == red)
        {
                gp->color = red;
                if (item < gp->element != (item < p->element))
                        p = red_black_tree_rotate(item, gp);
                x = red_black_tree_rotate(item, ggp);
                x->color = black;
        }
        t->right->color = black;
}

red_black_tree red_black_tree_insert(int item, red_black_tree t)
{
        x = p = gp = t;
        NULL_NODE->element = item;
        while (x->element != item)
        {
                ggp = gp;
                gp = p;
                p = x;
                if (item < x->element)
                        x = x->left;
                else
                        x = x->right;
                if (x->left->color == red && x->right->color == red)
                        ;
                red_black_tree_handler_reorient(item, t);
        }

        if (x != NULL_NODE)
                return NULL_NODE;
        x = (struct red_black_tree_node *)malloc(sizeof(struct red_black_tree_node));
        if (x == NULL)
        {
                perror("Out of space.");
                return NULL_NODE;
        }
        x->element = item;
        x->left = x->right = NULL_NODE;

        if (item < p->element)
                p->left = x;
        else
                p->right = x;

        red_black_tree_handler_reorient(item, t);

        return t;
}

#endif