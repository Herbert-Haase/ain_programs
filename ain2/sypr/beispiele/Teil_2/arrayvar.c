/*
 * arrayvar.c
 *
 * Beispiel-Programm Feld-Variable
 *
 * Autor: H.Drachenfels
 * Erstellt am: 3.2.2012
 */

#include <stdio.h>

int main()
{
    int a[] = {3421, 3442, 3635, 3814};
    const int n = (int) (sizeof a / sizeof (int));
    int i;
  
    /*------------------------------------ print array values and addresses */
    printf("a = %p\n", (void*) a);

    for (i = 0; i < n; ++i)
    {
      printf("%d: %p %d\n", i, (void*) &a[i], a[i]);
    }

    /*---------------------------------------------------- print array size */
    printf("sizeof a = %lu\n", (unsigned long) sizeof a);

    return 0;
}

