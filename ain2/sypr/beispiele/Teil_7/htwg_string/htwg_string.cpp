//
// htwg_string.cpp
//
// Stark vereinfachte String-Klasse.
//
// Autor: H.Drachenfels
// Erstellt am: 24.6.2014
//

#include "htwg_string.h"
using namespace htwg;

#include <cstring>

// Konstruktoren und Destruktor
string::string()
{
    this->n = 0;
    this->s = new char[1];
    *this->s = '\0';
}

string::string(const char* s)
{
    this->n = std::strlen(s);
    this->s = new char[this->n + 1];
    std::strcpy(this->s, s);
}

string::string(const string& str)
{
    this->n = str.n;
    this->s = new char[this->n + 1];
    std::strcpy(this->s, str.s);
}

string::~string()
{
    delete[] this->s;
}

// Zuweisungen
string& string::operator=(const string& str)
{
    if (this != &str)
    {
        delete[] this->s;
        this->n = str.n;
        this->s = new char[this->n + 1];
        std::strcpy(this->s, str.s);
    }

    return *this;
}

string& string::operator+=(const string& str)
{
    std::size_t m = this->n + str.n;
    char *t = new char[m + 1];
    std::strcpy(t, this->s);
    std::strcpy(t + this->n, str.s);
    delete[] this->s;
    this->n = m;
    this->s = t;

    return *this;
}

// Vergleich(e)
bool string::operator<(const string& str) const
{
    return std::strcmp(this->s, str.s) < 0;
}
 
// Datenabfragen
const char* string::c_str() const
{
    return this->s;
}

std::size_t string::length() const
{
    return this->n;
}

