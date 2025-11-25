//
// FixedDate.cpp
//
// FixedDate liefert ein festes Datum
//
// Autor: H.Drachenfels
// erstellt am: 20.6.2013
//

#include "FixedDate.h"
#include <stdexcept>

FixedDate::FixedDate(int d, int m, int y)
: day(d), month(m), year(y)
{
    if (d < 1 || d > 31 || m < 1 || m > 12)
    {
        throw std::invalid_argument("Falsches Datum");
    }
}

void FixedDate::get(int *d, int *m, int *y) const
{
    *d = day;
    *m = month;
    *y = year;
}

