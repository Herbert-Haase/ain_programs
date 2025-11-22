/*
 * for-schleife.c
 *
 * Gibt alle Elemente eines Felds aus
 *
 * Autor: H.Drachenfels
 * erstellt am: 3.2.2012
 */

#include <stdio.h>

int main()
{
    int an_array[] = {3082, 3101, 3275, 3436};
    const int array_size = (int) (sizeof an_array / sizeof *an_array);
    int i;

    for (i = 0; i < array_size; ++i)
    {
        printf("%d\n", an_array[i]);
    }

    return 0;
}

