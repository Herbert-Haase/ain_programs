//
// FixedDate.h
//
// FixedDate liefert ein festes Datum
//
// Autor: H.Drachenfels
// erstellt am: 21.6.2013
//

#ifndef FIXEDDATE_H
#define FIXEDDATE_H

#include "Date.h"

class FixedDate : public virtual Date
{
public:
    FixedDate(int d, int m, int y);
    void get(int *d, int *m, int *y) const;

private:
    const int day;
    const int month;
    const int year;
};

#endif

