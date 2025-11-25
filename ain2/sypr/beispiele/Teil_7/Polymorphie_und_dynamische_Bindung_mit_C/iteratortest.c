/*
 * iteratortest.c
 *
 * Beispielprogramm Systemprogrammierung:
 * Polymorphie und dynamische Bindung mit C
 *
 * Autor: H.Drachenfels
 * Erstellt am: 13.3.2012
 */


#include <stdio.h>
#include "array_iterator.h"

int main()
{
    int a[4] = {3421, 3442, 3635, 3814};
    iterator *i = new_array_iterator(4, a);
    if (!i) return 1;

    while (iterator_hasnext(i))
    {
        int n = iterator_next(i);
        printf("%d\n", n);
    }

    iterator_destruct(i);
    return 0;
}

