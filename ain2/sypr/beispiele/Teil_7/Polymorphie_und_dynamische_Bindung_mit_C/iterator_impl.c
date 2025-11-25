/*
 * iterator_impl.c
 *
 * Beispielprogramm Systemprogrammierung:
 * Polymorphie und dynamische Bindung mit C
 *
 * Autor: H.Drachenfels
 * Erstellt am: 13.3.2012
 */


#include "iterator_impl.h"

void iterator_destruct(const iterator * const p)
{
    p->interface_p->destruct(p->object_p);
}

int iterator_hasnext(const iterator * const p)
{
    return p->interface_p->hasnext(p->object_p);
}

int iterator_next(const iterator * const p)
{
    return p->interface_p->next(p->object_p);
}

