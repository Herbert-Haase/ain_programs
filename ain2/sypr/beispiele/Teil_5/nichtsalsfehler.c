/*
 * nichtsalsfehler.c
 *
 * Beispielprogramm fuer die Fehlersuche mit valgrind.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 9.1.2012
 */

#include <stdlib.h>

int main()
{
    int *p1 = (int*) malloc(sizeof (int));
    int *p2 = (int*) malloc(2 * sizeof (int));
    int *p3 = (int*) calloc(1, sizeof (int));
    int i;

    for (i = 1; i < 3; ++i)
    {
        p2[i] = 0;
    }

    *p1 = p2[0];
    *p3 = *p1 ? p2[0] : p2[1];

    free(p2);
    free(p3);
    *p3 = 0;
    free(p3);

    return 0;
}

