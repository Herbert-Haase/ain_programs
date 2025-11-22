/*
 * inparam.c
 *
 * Beispiel-Programm Eingabe-Parameter
 *
 * Autor: H.Drachenfels
 * erstellt am: 13.3.2012
 */

#include <stdio.h>
#include <stddef.h>

struct date
{
    int day;
    const char *month;
    int year;
};

typedef struct date date;

void print_int(int n);
void print_string(const char *s);
void print_int_array(int size, const int a[]);
void print_date(const date *d);
void print_int_array_array(int n, const int xy[][2]);
void print_int_array_pointer(int n, int m, const int * const *xy);

int main()
{
    const int n = 10;
    const char* s = "Hallo";
    const int a[2] = {10, 11};
    const date d = {25, "Februar", 2011};
    const int aa[3][2] = {{10, 11}, {20, 21}, {30, 31}};
    const int *ap[3];
    ap[0] = aa[0];
    ap[1] = aa[1];
    ap[2] = aa[2];

    print_int(n);
    print_string(s);
    print_int_array(2, a);
    print_date(&d);
    print_int_array_array(3, aa);
    print_int_array_pointer(3, 2, ap);

    return 0;
}


void print_int(int n)
{
    printf("%d\n", n);
    n = 0; /* ok, lokale Variable */
}


void print_string(const char *s)
{
    printf("%s\n", s);
    /*s[0] = '\0'; Fehler, Zeiger auf konstante Zeichenkette */
    s = NULL; /* ok, lokale Variable */
}


void print_int_array(int size, const int a[])
{
    int i;

    for (i = 0; i < size; ++i)
    {
        printf("%d ", a[i]);
    }

    printf("\n");

    /*a[0] = 0; Fehler, Zeiger auf konstantes Feld */
    a = NULL; /* ok, lokale Variable */
}


void print_date(const date *d)
{
    printf("%d. %s %d\n", d->day, d->month, d->year);
    /*d.day = 0; Fehler, Zeiger auf konstanten Wert */
}


void print_int_array_array(int n, const int xy[][2])
{
    int i, j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < 2; ++j)
        {
            printf("%d ", xy[i][j]);
        }
    }

    printf("\n");

    /*xy[0][0] = 0; Fehler, Zeiger auf konstantes Feld */
   /* xy[0] = 0; Fehler, Zeiger auf zweidimensionales Feld */
    xy = NULL; /* ok, lokale Variable */
}


void print_int_array_pointer(int n, int m, const int * const *xy)
{
    int i, j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            printf("%d ", xy[i][j]);
        }
    }

    printf("\n");

    /*xy[0][0] = 0; Fehler, Zeiger auf konst. Zeiger auf konst. Feld */
    /*xy[0] = 0; Fehler, Zeiger auf konstanten Zeiger */
    xy = NULL; /* ok, lokale Variable */
}

