//
// Date.h
//
// Schnittstelle fuer Datumsklassen
//
// Autor: H.Drachenfels
// erstellt am: 20.6.2013
//

#ifndef DATE_H
#define DATE_H

class Date
{
public:
    virtual ~Date() { }
    virtual void get(int *d, int *m, int *y) const = 0;
};

#endif

