//
// htwg_string.h
//
// Stark vereinfachte String-Klasse.
//
// Autor: H.Drachenfels
// Erstellt am: 24.6.2014
//

#ifndef HTWG_STRING_H
#define HTWG_STRING_H

#include <cstdlib> // size_t

namespace htwg
{
    class  string
    {
    public:
        // Konstruktoren und Destruktor
        string();
        string(const char* s);
        string(const string& str);
        ~string();

        // Zuweisungen
        string& operator=(const string& str);
        string& operator+=(const string& str);

        // Vergleich(e)
        bool operator<(const string& str) const;
 
        // Datenabfragen
        const char* c_str() const;
        std::size_t length() const;

    private:
        std::size_t n;
        char *s;
    };
}

#endif

