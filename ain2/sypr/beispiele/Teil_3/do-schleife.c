/*
 * do-schleife.c
 *
 * Gibt eine Zahl zwischen 0 und 255 binaer aus
 *
 * Autor: H.Drachenfels
 * erstellt am: 3.2.2012
 */

#include <stdio.h>

int main()
{
    int n = 0;
  
    /* Dezimalzahl einlesen */
    do
    {
        printf("Zahl zwischen 0 und 255 eingeben: ");
    }
    while (scanf("%d", &n) == 1 && (n < 0 || n > 255));

    /* Binaerzahl ausgeben */
    printf("       "); /* sieben Leerzeichen */

    do
    {
        printf("%d\b\b", n % 2);
        n /= 2;
    }
    while (n > 0);

    printf("\n");

    return 0;
}

