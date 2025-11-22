/*
 * pointervar.c
 *
 * Beispiel-Programm Zeiger-Variable
 *
 * Autor: H.Drachenfels
 * Erstellt am: 4.11.2010
 */

#include <stdio.h>

int main()
{
    int i = 3082;
    int *p = &i;

    /*-------------------------------------------- print pointer value */
    printf("p = %p\n", (void*) p);

    /*------------------------------------------ print pointer address */
    printf("&p = %p\n", (void*) &p);

    /*--------------------------------------------- print pointer size */
    printf("sizeof p = %lu\n", (unsigned long) sizeof p);

    /*------------------------------- print dereferenced pointer value */
    printf("*p = %d\n", *p);

    return 0;
}

