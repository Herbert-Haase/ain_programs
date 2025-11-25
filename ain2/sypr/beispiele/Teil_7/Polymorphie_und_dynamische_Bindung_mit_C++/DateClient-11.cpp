//
// DateClient-11.cpp
//
// Testprogramm fuer Datumsklassen
// Version mit C++11 std::shared_ptr<>
//
// Autor: H.Drachenfels
// erstellt am: 25.6.2015
//

#include "CurrentDate.h"
#include "FixedDate.h"

#include <iostream>
#include <memory>
#include <stdexcept>

void printDate(std::shared_ptr<Date>);

int main()
{
    try
    {
        std::shared_ptr<Date> d;

        d = std::make_shared<CurrentDate>();
        printDate(d);

        d = std::make_shared<FixedDate>(1, 9, 2000);
        printDate(d);
    }
    catch (std::invalid_argument& x)
    {
        std::cout << x.what() << '\n';
    }
}

void printDate(std::shared_ptr<Date> d)
{
    int day;
    int month;
    int year;

    d->get(&day, &month, &year);
    std::cout << day << '.' << month << '.' << year << '\n';
}

