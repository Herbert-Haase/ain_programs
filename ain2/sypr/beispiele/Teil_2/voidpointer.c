/*
 * voidpointer.c
 *
 * Beispiel-Programm Zeiger-Variable
 *
 * Autor: H.Drachenfels
 * Erstellt am: 17.11.2010
 */

#include <stdio.h>

int main()
{
    float n = 1;
    void *vp = &n;
    int *ip = (int*) vp;

    printf("%x\n", *ip);

    return 0;
}

