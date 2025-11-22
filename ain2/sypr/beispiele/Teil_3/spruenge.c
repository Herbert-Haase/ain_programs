/*
 * spruenge.c
 *
 * Version von while-Schleife.c mit ausfuehrliche Fehlerbehandlung
 * als Beispiel fuer die Verwendung von break, continue, return.
 * Liest wie while-Schleife.c beliebig viele Zahlen ein und
 * gibt deren Summe aus.
 *
 * Autor: H.Drachenfels
 * Erstellt am: 17.4.2013
 */

#include <stdio.h>
#include <ctype.h>

int main()
{
    int sum = 0;
    int n;
	
    printf("Zahlen eingeben (Ende mit Strg-D): ");

    while (1) /* Endlos-Schleife, alternativ auch: for (;;) */
    {
        /*------------------------------------------------- Eingabe lesen */
        int i = scanf("%d", &n);

        /*--------------------------------------- Eingabefehler behandeln */
        if (i == EOF)
        {
            /* Fehlerursache: Benutzer hat Strg-D eingegeben */
            fprintf(stderr, "*** Eingabeende\n");

            break;  /* hinter die Schleife springen */
        }
        else if (i == 0)
        {
            int c;

            /* Fehlerursache: Der Benutzer hat keine Ziffern eingegeben */
            fprintf(stderr, "*** Eingabe ist keine ganze Zahl: ");

            /*  Falsche Zeichen entfernen */
            while ((c = getchar()) != EOF && !isspace(c))
            {
                putc(c, stderr);
            }

            putc('\n', stderr);

            continue;  /* zum naechsten Schleifendurchlauf springen */
        }

        /*-------------------------------------------------- aufsummieren */
        sum += n;
    }

    printf("Summe: %d\n", sum);

    return 0; /* normales Programmende */
}

