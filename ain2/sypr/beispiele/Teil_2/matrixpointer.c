/*
 * matrixpointer.c
 *
 * Beispiel-Programm Matrix als Feld von Feldern.
 * Siehe zum Vergleich matrixpointerpointer.c
 *
 * Autor: H.Drachenfels
 * Erstellt am: 25.2.2015
 */

#include <stdio.h>
#include <stdlib.h>

#define M 3 /* number of columns */

int main(void)
{
    /*--------------------- allocate and initialize memory for 2x3-matrix */
    const int n = 2; /* number of lines */
    int (*matrix)[M] = (int(*)[M]) malloc(n * M * sizeof (int));
    int i;
    int j;

    if (matrix == NULL)
    {
        printf("Speicherallokierungsfehler\n");
        return 1;
    }

    matrix[0][0] = 10;
    matrix[0][1] = 11;
    matrix[0][2] = 12;
    matrix[1][0] = 20;
    matrix[1][1] = 21;
    matrix[1][2] = 22;

    /*--------------------------------- print matrix addresses and values */
    printf("&matrix = %p\n", (void*) &matrix);
    printf("matrix = %p\n", (void*) matrix);

    for (i = 0; i < n; ++i)
    {
        printf("[%d] %p: %p\n", i, (void*) &matrix[i], (void*) matrix[i]);

        for (j = 0; j < M; ++j)
        {
            printf( "  [%d] %p: %d\n", j, (void*) &matrix[i][j], matrix[i][j]);
        }
    }

    /*------------------------------------------------- print matrix size */
    printf("sizeof matrix = %lu\n", (unsigned long) sizeof matrix);
    printf("%d * sizeof *matrix = %lu\n",
           n, (unsigned long) n * sizeof *matrix);

    free(matrix);
    return 0;
}

