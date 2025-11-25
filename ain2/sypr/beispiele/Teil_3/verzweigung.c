/*
 * verzweigung.c
 *
 * Liesst zwei Zahlen ein und gibt das Maximum aus
 *
 * Autor: H.Drachenfels
 * Erstellt am: 15.2.2011
 */

#include <stdio.h>

int main()
{
    int m, n;

    printf("Zwei Zahlen eingeben: ");

    if  (scanf("%d%d", &m, &n) < 2)
    {
        fprintf(stderr, "Eingabefehler !\n");
    }
    else if (m > n)
    {
        printf("Maximum: %d\n", m);
    }
    else
    {
        printf("Maximum: %d\n", n);
    }

    return 0;
}

