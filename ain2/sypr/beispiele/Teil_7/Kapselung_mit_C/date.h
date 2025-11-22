/*
 * date.h
 *
 * Beispielprogramm Systemprogrammierung: Kapselung mit C
 *
 * Autor: H.Drachenfels
 * Erstellt am: 13.3.2012
 */

#ifndef DATE_H
#define DATE_H

typedef struct class_date date;

date* new_current_date(void);
date* new_date(int d, int m, int y);

void delete_date(date *this_p);

void print_date(date *this_p);

#endif

