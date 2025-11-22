/*
 * while-schleife.c
 *
 * Liest beliebig viele Zahlen ein und gibt deren Summe aus
 *
 * Autor: H.Drachenfels
 * erstellt am: 15.2.2011
 */

#include <stdio.h>

int main()
{
    int sum = 0;
    int n;
	
    printf("Zahlen eingeben (Ende mit Strg-d): ");
    while (scanf("%d", &n) == 1)
    {
        sum += n;
    }

    printf("Summe: %d\n", sum);

    return 0;
}

