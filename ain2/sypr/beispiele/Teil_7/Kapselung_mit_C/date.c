/*
 * date.c
 *
 * Beispielprogramm Systemprogrammierung: Kapselung mit C
 *
 * Autor: H.Drachenfels
 * Erstellt am: 13.3.2012
 */

#include "date.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct class_date
{
    int day;
    int month;
    int year;
};

date* new_current_date(void)
{
    date *this_p;
    time_t t;
    struct tm *heute;

    this_p = malloc(sizeof (date));
    if (!this_p) return NULL;

    time(&t);
    heute = localtime(&t);
    this_p->day = heute->tm_mday;
    this_p->month = heute->tm_mon + 1;
    this_p->year = heute->tm_year + 1900;

    return this_p;
}

date* new_date(int d, int m, int y)
{
    date *this_p;

    if (d < 1 || d > 31 || m < 1 || m > 12)
    {
        return NULL;
    }

    this_p = malloc(sizeof (date));
    if (!this_p) return NULL;

    this_p->day = d;
    this_p->month = m;
    this_p->year = y;

    return this_p;
}

void delete_date(date *this_p)
{
    free(this_p);
}

void print_date(date *this_p)
{
    printf("%d-%02d-%02d\n", this_p->year, this_p->month, this_p->day);
}

