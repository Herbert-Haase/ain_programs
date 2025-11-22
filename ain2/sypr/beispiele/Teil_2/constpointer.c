/*
 * constpointer.c
 *
 * Beispiel-Programm Zeiger-Variable
 *
 * Autor: H.Drachenfels
 * Erstellt am: 26.10.2011
 */

#include <stdio.h>

int main()
{
    const int i = 0;
    const int *p = &i;

    int j = 0;
    int * const q = &j;

/* Fehler, *p konstant:
    *p = 0;
*/
    p = NULL;

    *q = 0;
/* Fehler, q konstant:
    q = NULL;
*/

    return 0;
}

