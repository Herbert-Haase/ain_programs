/*
 * name_adresse.c
 *
 * Beispiel-Programm Speichernutzung per Name oder Adresse
 *
 * Autor: H.Drachenfels
 * Erstellt am: 12.10.2012
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    {
       /* Speichernutzung per Name: */
       int a = 1;
       int b;

       b = a;

       printf("a = %d\n", a);
       printf("b = %d\n", b);
    }

    {
        /* Speichernutzung per Adresse: */
        int *a_ptr = (int*) malloc(sizeof (int));
        int *b_ptr = (int*) malloc(sizeof (int));

        if (a_ptr == NULL || b_ptr == NULL)
        {
            printf("Speicherallokierungsfehler\n");
            return 1;
        }

        *a_ptr = 1;
        *b_ptr = *a_ptr;

        printf("*%p = %d\n", (void*) a_ptr, *a_ptr);
        printf("*%p = %d\n", (void*) b_ptr, *b_ptr);

        free(a_ptr);
        free(b_ptr);
    }

    return 0;
}

