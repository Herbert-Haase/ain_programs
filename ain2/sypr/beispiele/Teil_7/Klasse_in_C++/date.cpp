//
// date.cpp
//
// Beispiel-Programm Klasse
//
// Autor: H.Drachenfels
// erstellt am: 20.6.2014
//

#include "date.h"

#include <ctime> // std::time ...
#include <stdexcept> // std::invalid_argument
#include <iostream> // std::cout
#include <iomanip> // std::setw, std::setfill

// eigentlich: Date::Date(Date * const this)
Date::Date()
{
    // aktuelles System-Datum holen
    std::time_t t = std::time(0);
    std::tm *p = std::localtime(&t);

    this->day = p->tm_mday;
    this->month = p->tm_mon + 1;
    this->year = p->tm_year + 1900;
}


// eigentlich: Date::Date(Date * const this, int d, int m, int y)
Date::Date(int d, int m, int y)
: day(d), month(m), year(y) // Initialisierungsliste
{
    if (d < 1 || d > 31 || m < 1 || m > 12)
    {
        throw std::invalid_argument("Falsches Datum");
    }
}

// eigentlich: Date::Date(Date * const this, const Date &d)
Date::Date(const Date &d)
: day(d.day), month(d.month), year(d.year) // Initialisierungsliste
{
    // diese Implementierung wuerde der Compiler auch automatisch erzeugen
}


// eigentlich: Date::~Date(Date * const this)
Date::~Date()
{
    // diese Implementierung wuerde der Compiler auch automatisch erzeugen
}


// eigentlich: Date& Date::operator=(Date * const this, const Date &d)
Date& Date::operator=(const Date &d)
{
    // diese Implementierung wuerde der Compiler auch automatisch erzeugen
    if (this != &d) // keine Selbstzuweisung?
    {
        this->day = d.day;
        this->month = d.month;
        this->year = d.year;
    }

    return *this;
}


// eigentlich: void Date::print(const Date * const this)
void Date::print() const
{
    std::cout << this->year
              << '-' << std::setw(2) << std::setfill('0') << this->month
              << '-' << std::setw(2) << std::setfill('0') << this->day;
}

