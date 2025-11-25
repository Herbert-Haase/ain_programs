/*
 * unionvar.c
 *
 * Beispiel-Programm union-Variable
 *
 * Autor: H.Drachenfels
 * Erstellt am: 13.4.2012
 */

#include  <stdio.h>

enum int_or_string {type_int, type_string};

struct struct_with_union
{
    enum int_or_string u_type;

    union
    {
        int i;
        char *s;
    } u;
};

int main ()
{
    struct struct_with_union x;

    /*-------------------------------------------- print variable value */
    x.u_type = type_int;
    x.u.i = 1;
    printf("%d: %d\n", x.u_type, x.u.i);

    x.u_type = type_string;
    x.u.s = "Hallo";
    printf("%d: %s\n", x.u_type, x.u.s);

    /*------------------------------------------ print variable address */
    printf("&x = %p\n", (void*) &x);
    printf("&x.u_type = %p\n", (void*) &x.u_type);
    printf("&x.u = %p\n", (void*) &x.u);
    printf("&x.u.i = %p\n", (void*) &x.u.i);
    printf("&x.u.s = %p\n", (void*) &x.u.s);

    /*--------------------------------------------- print variable size */
    printf("sizeof d = %lu\n", (unsigned long) sizeof x);

    return 0;
}

