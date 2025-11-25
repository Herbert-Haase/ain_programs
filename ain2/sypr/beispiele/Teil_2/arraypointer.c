/*
 * arraypointer.c
 *
 * Beispiel-Programm Zeiger auf Feld (vergleiche arrayvar.c)
 *
 * Autor: H.Drachenfels
 * Erstellt am: 25.2.2015
 */

#include <stdio.h>
#include <stdlib.h> /* calloc, malloc, free, ... */
#include <stddef.h> /* NULL, size_t, ... */

int main(void)
{
    const int n = 4;
    int i;
    int *a = (int*) calloc((size_t) n, sizeof (int));
    /* oder ohne Initialisierung mit 0: int *a = malloc(n * sizeof (int)); */
    if (a == NULL)
    {
        printf("Speicherreservierung fehlgeschlagen!\n");
        return 1;
    }

    a[0] = 3421;
    a[1] = 3442;
    a[2] = 3635;
    a[3] = 3814;
  
    /*------------------------------------ print array values and addresses */
    printf("&a = %p\n", (void*) &a);
    printf("a = %p\n", (void*) a);

    for (i = 0; i < n; ++i)
    {
      printf("%d: %p %d\n", i, (void*) &a[i], a[i]);
    }

    /*---------------------------------------------------- print array size */
    printf("sizeof a = %lu\n", (unsigned long) sizeof a); /* pointer size */
    printf("%d * sizeof *a = %lu\n", n, (unsigned long) n * sizeof *a);

    free(a);
    return 0;
}

