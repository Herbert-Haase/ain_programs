/*
 * intvar.c
 *
 * Beispiel-Programm int-Variable
 *
 * Autor: H.Drachenfels
 * Erstellt am: 24.3.2011
 */

#include <stdio.h>

int main()
{
    int i = 0;
    int j = 1;

    /*------------------------------------------- print variable values */
    printf("i = %d\n", i);
    printf("j = %d\n", j);

    /*---------------------------------------- print variable addresses */
    printf("&i = %p\n", (void*) &i);
    printf("&j = %p\n", (void*) &j);

    /*----------------------------------- print type and variable sizes */
    printf("sizeof (int) = %lu\n", (unsigned long) sizeof (int));
    printf("sizeof i = %lu\n", (unsigned long) sizeof i);

    return 0;
}

