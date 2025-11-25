/*
 * datetest.c
 *
 * Beispielprogramm Systemprogrammierung: Kapselung mit C
 *
 * Autor: H.Drachenfels
 * Erstellt am: 13.3.2012
 */

#include "date.h"

int main()
{
    date *d;

    d = new_current_date();
    if (d)
    {
        print_date(d);
        delete_date(d);
    }

    d = new_date(9, 7, 2011);
    if (d)
    {
        print_date(d);
        delete_date(d);
    }

    return 0;
}

