//
// datetest.cpp
//
// Beispiel-Programm Klasse
//
// Autor: H.Drachenfels
// erstellt am: 28.7.2011
//

#include "date.h"
#include <iostream>
#include <stdexcept>

int main()
{
    try
    {
        Date d1;
        /*
        * hier vom Compiler eingefuegt:
        *   Default-Konstruktor-Aufruf Date::Date(&d1);
        */

        Date d2(1, 9, 2000);
        /*
        * hier vom Compiler eingefuegt:
        *   Konstruktor-Aufruf Date::Date(&d2, 1, 9, 2000);
        */

        Date d3 = d1;
        /*
        * hier vom Compiler eingefuegt:
        *   Copy-Konstruktor-Aufruf Date::Date(&d3, d1);
        */

        d3 = d2;    // eigentlich: Date::operator=(&d1, d2);
        d3.print(); // eigentlich: Date::print(&d3);

        /*
        * hier vom Compiler eingefuegt:
        *   Destruktor-Aufruf Date::~Date(&d3);
        *   Destruktor-Aufruf Date::~Date(&d2);
        *   Destruktor-Aufruf Date::~Date(&d1); 
        */
    }
    catch (std::invalid_argument& x)
    {
        std::cerr << x.what() << std::endl;
    }
}

