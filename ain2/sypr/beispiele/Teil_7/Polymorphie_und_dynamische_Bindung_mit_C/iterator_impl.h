/*
 * iterator_impl.h
 *
 * Beispielprogramm Systemprogrammierung:
 * Polymorphie und dynamische Bindung mit C
 *
 * Autor: H.Drachenfels
 * Erstellt am: 3.1.2012
 */


#ifndef ITERATOR_IMPL_H
#define ITERATOR_IMPL_H

#include "iterator.h"

struct object;

struct iterator_interface
{
    void (* const destruct)(struct object * const this_p);
    int (* const hasnext)(struct object * const this_p);
    int (* const next)(struct object * const this_p);
};

struct iterator
{
    struct iterator_interface *interface_p;
    struct object *object_p;
};

#endif

