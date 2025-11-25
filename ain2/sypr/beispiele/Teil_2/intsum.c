/*
 * intsum.c
 *
 * Liest ganze Zahlen ein und summiert sie.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 5.10.2010
 */

#include <stdio.h>

int main()
{
    int sum = 0;
    int number;

    printf("Ganze Zahlen eingeben (Ende mit Strg-D):\n");

    while (scanf("%d", &number) > 0)
    {
        sum += number;
    }

    printf("Summe: %d\n", sum);

    return 0;
}

