#include <stdio.h>
#include <stdlib.h>
#ifndef _ARRAY_STACK_H
#define _ARRAY_STACK_H

struct array_stack_record;
typedef struct array_stack_record *array_stack;

int array_stack_is_empty(array_stack s);
int array_stack_is_full(array_stack s);     // TODO
array_stack array_stack_create(int max_elements);
void array_stack_dispose(array_stack s);
void array_stack_make_empty(array_stack s);
void array_stack_push(int x, array_stack s);
int array_stack_top(array_stack s);
void array_stack_pop(array_stack s);
int array_stack_top_and_pop(array_stack s);       // TODO

#define ARRAY_STACK_EMPTY_TO_S -1
#define ARRAY_STACK_MIN_STACK_SIZE 5

struct array_stack_record
{
        int capacity;
        int top_of_stack;
        int *array;
};

array_stack array_stack_create(int max_elements)
{
        array_stack s;
        if (max_elements < ARRAY_STACK_MIN_STACK_SIZE)
        {
                perror("Stack size is too small");
                return NULL;
        }

        s = (array_stack)malloc(sizeof(struct array_stack_record));
        if (s == NULL)
        {
                perror("Out of space.");
                return NULL;
        }
        s->array = (int *)malloc(sizeof(int) * max_elements);
        if (s->array == NULL)
        {
                perror("Out of space.");
                return NULL;
        }
        s->capacity = max_elements;
        array_stack_make_empty(s);
        return s;
}

void array_stack_dispose_stack(array_stack s)
{
        if (s != NULL) {
                free(s->array);
                free(s);
        }
}

int array_stack_is_empty(array_stack s)
{
        return s->top_of_stack = ARRAY_STACK_EMPTY_TO_S;
}

void array_stack_make_empty(array_stack s)
{
        s->top_of_stack = ARRAY_STACK_EMPTY_TO_S;
}

void array_stack_push(int x, array_stack s)
{
        if (array_stack_is_full(s))
        {
                perror("Full stack.");
                return;
        }
        else
                s->array[++s->top_of_stack] = x;
}

int array_stack_top(array_stack s)
{
        if (!array_stack_is_empty(s)) return s->array[s->top_of_stack];
        perror("Empty stack.");
        return 0;
}

void array_stack_pop(array_stack s) 
{
        if (array_stack_is_empty(s))
        {
                perror("Empty stack.");
                return;
        }
        else
                s->top_of_stack--;
}

#endif