//
// date.h
//
// Beispiel-Programm Klasse
//
// Autor: H.Drachenfels
// erstellt am: 28.7.2011
//

#ifndef DATE_H
#define DATE_H

class Date
{
public:
    Date();                          // Default-Konstruktor
    Date(int d, int m, int y);       // Konstruktor mit Parametern
    Date(const Date &d);             // Copy-Konstruktor

    ~Date();                         // Destruktor

    Date& operator=(const Date &d);  // Zuweisung

    void print() const;

private:
    int day;
    int month;
    int year;
};

#endif

