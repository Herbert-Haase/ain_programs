/*
 * stringvar.c
 *
 * Beispiel-Anwendung von str-Funktionen
 *
 * Autor: H.Drachenfels
 * Erstellt am: 25.2.2015
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> /* strxxx functions */

int main(void)
{
    char a[] = "halli";
    const char *s = "hallo";
    char *t = NULL;

    /*----------------------------- compare, copy and concatenate strings */
    if (strcmp(a, s) < 0)
    {
        t = (char*) malloc(sizeof a + strlen(s));
        if (t == NULL)
        {
            fprintf(stderr, "Kein Heap-Speicher mehr\n");
            return 1;
        }

        strcat(strcpy(t, a), s); /* or: strcpy(t, a); strcat(t, s); */
    }
    else
    {
        t = (char*) calloc(1, sizeof (char));
        if (t == NULL)
        {
            fprintf(stderr, "Kein Heap-Speicher mehr\n");
            return 1;
        }
    }

    /*--------------------------------- print string values and addresses */
    printf("a = %p %s\ns = %p %s\nt = %p %s\n",
           (void*) a, a, (void*) s, s, (void*) t, t);

    printf("sizeof a = %lu\n", (unsigned long) sizeof a);
    printf("sizeof s = %lu\n", (unsigned long) sizeof s);
    printf("sizeof t = %lu\n", (unsigned long) sizeof t);

    printf("strlen(a) = %lu\n", (unsigned long) strlen(a));
    printf("strlen(s) = %lu\n", (unsigned long) strlen(s));
    printf("strlen(t) = %lu\n", (unsigned long) strlen(t));

    s = a; /* copies the address, not the string */
    /* a = s; syntax error */

    free(t);

    return 0;
}

