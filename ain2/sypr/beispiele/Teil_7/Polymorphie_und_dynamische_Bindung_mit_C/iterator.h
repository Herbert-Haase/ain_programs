/*
 * iterator.h
 *
 * Beispielprogramm Systemprogrammierung:
 * Polymorphie und dynamische Bindung mit C
 *
 * Autor: H.Drachenfels
 * Erstellt am: 13.3.2012
 */


#ifndef ITERATOR_H
#define ITERATOR_H

typedef struct iterator iterator;

void iterator_destruct(const iterator * const);
int iterator_hasnext(const iterator * const);
int iterator_next(const iterator * const);

#endif

