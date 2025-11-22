//
// DateClient.cpp
//
// Testprogramm fuer Datumsklassen
//
// Autor: H.Drachenfels
// erstellt am: 21.6.2013
//

#include "CurrentDate.h"
#include "FixedDate.h"

#include <iostream>
#include <stdexcept>

void printDate(Date*);

int main()
{
    try
    {
        Date *d;

        d = new CurrentDate();
        printDate(d);
        delete d;

        d = new FixedDate(1, 9, 2000);
        printDate(d);
        delete d;
    }
    catch (std::invalid_argument& x)
    {
        std::cout << x.what() << '\n';
    }
}

void printDate(Date *d)
{
    int day;
    int month;
    int year;

    d->get(&day, &month, &year);
    std::cout << day << '.' << month << '.' << year << '\n';
}

