//
// CurrentDate.h
//
// CurrentDate liefert das aktuelle Datum
//
// Autor: H.Drachenfels
// erstellt am: 20.6.2013
//

#ifndef CURRENTDATE_H
#define CURRENTDATE_H

#include "Date.h"

class CurrentDate : public virtual Date
{
public:
    void get(int *d, int *m, int *y) const;
};

#endif

