/*
 * charliteral.c
 *
 * Beispiel-Programm Zeichen-Literale
 *
 * Autor: H.Drachenfels
 * Erstellt am: 1.10.2010
 */

#include <stdio.h>

int main()
{
    printf("%s\n", "Hallo");
    printf("%s\n", "Hal" "lo");
    printf("Hallo\n");
    printf("%c%c%c%c%c\n", 'H', 'a', 'l', 'l', 'o');
    return 0;
}

