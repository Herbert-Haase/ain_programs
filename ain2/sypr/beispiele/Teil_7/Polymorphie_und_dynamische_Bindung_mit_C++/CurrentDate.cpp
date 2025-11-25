//
// CurrentDate.cpp
//
// CurrentDate liefert das aktuelle Datum
//
// Autor: H.Drachenfels
// erstellt am: 20.6.2013
//

#include "CurrentDate.h"
#include <ctime>

void CurrentDate::get(int *d, int *m, int *y) const
{
    // aktuelles System-Datum holen
    std::time_t t = std::time(0);
    std::tm *p = std::localtime(&t);

    *d = p->tm_mday;
    *m = p->tm_mon + 1;
    *y = p->tm_year + 1900;
}

