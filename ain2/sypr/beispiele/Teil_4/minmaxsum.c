/*
 * minmaxsum.c
 *
 * Gibt die kleinere, groessere und die Summe zweier Zahlen aus.
 * Beispiel fuer die Verwendung eines Felds von Funktionszeigern.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 13.3.2012
 */

#include <stddef.h> /* NULL */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* atoi */

typedef int (*int_int_function)(int, int);

int min(int, int);
int max(int, int);
int sum(int, int);

int main(int argc, char *argv[])
{
    int m;
    int n;
    int i;

    int_int_function f[] = {min, max, sum, NULL};

    if (argc != 3)
    {
        fprintf(stderr, "Aufruf: %s Zahl Zahl\n", argv[0]);
        return 1;
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);

    for (i = 0; f[i] != NULL; ++i)
    {
        printf("%d\n", f[i](m, n));
    }

    return 0;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int sum(int a, int b)
{
    return a + b;
}

