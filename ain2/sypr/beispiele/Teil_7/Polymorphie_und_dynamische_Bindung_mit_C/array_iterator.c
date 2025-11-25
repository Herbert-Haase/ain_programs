/*
 * array_iterator.c
 *
 * Beispielprogramm Systemprogrammierung:
 * Polymorphie und dynamische Bindung mit C
 *
 * Autor: H.Drachenfels
 * Erstellt am: 13.6.2013
 */

#include "array_iterator.h"
#include "iterator_impl.h"
#include <stdlib.h>

struct object
{
    iterator iterator_impl;
    int n;
    int *a;
    int i;
};

typedef struct object array_iterator;

static void destruct(array_iterator * const this_p);
static int hasnext(array_iterator * const this_p);
static int next(array_iterator * const this_p);

static struct iterator_interface array_iterator_interface = {
    destruct, hasnext, next
};

iterator *new_array_iterator(int n, int a[])
{
    array_iterator *this_p = (array_iterator*) malloc(sizeof (array_iterator));
    if (! this_p) return NULL;

    this_p->iterator_impl.interface_p = &array_iterator_interface;
    this_p->iterator_impl.object_p = this_p;

    this_p->n = n;
    this_p->a = a;
    this_p->i = 0;

    return &this_p->iterator_impl;
}

static void destruct(array_iterator * const this_p)
{
    free(this_p);
}

static int hasnext(array_iterator * const this_p)
{
    return this_p->i < this_p->n;
}

static int next(array_iterator * const this_p)
{
    return this_p->a[this_p->i++];
}

