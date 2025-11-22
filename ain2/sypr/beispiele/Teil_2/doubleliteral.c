/*
 * doubleliteral.c
 *
 * Beispiel-Programm Gleitkomma-Literale
 *
 * Autor: H.Drachenfels
 * Erstellt am: 1.10.2010
 */

#include <stdio.h>

int main()
{
    printf("%g\n", (1e-30 + 1e30) - 1e30);
    printf("%g\n", 1e-30 + (1e30 - 1e30));
    printf("%g\n", 12.3456789);
    printf("%g\n", 1234567.89);
    printf("%f\n", 12.3456789);
    printf("%f\n", 1234567.89);
    printf("%e\n", 12.3456789);
    printf("%e\n", 1234567.89);
    return 0;
}

