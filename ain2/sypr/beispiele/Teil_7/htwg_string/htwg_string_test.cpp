//
// htwg_string_test.cpp
//
// Beispiel-Anwendung fuer die stark vereinfachte String-Klasse
// (siehe zum Vergleich Beispiel-Anwendung von str-Funktionen in Teil 5)
//
// Autor: H.Drachenfels
// Erstellt am: 19.01.2012
//

#include <iostream>
#include "htwg_string.h"

int main()
{
    htwg::string s0; // leerer String
    std::cout << s0.length() << '\n';  // gibt 0 aus

    htwg::string s1("Hallo");
    std::size_t len = s1.length();
    std::cout << len << '\n';  // gibt 5 aus

    htwg::string s2 = s1;
    std::cout << s2.c_str() << '\n';  // gibt Hallo aus

    s2 += s1;
    std::cout << s2.c_str() << '\n';  // gibt HalloHallo aus

    s2 = s1;
    if (!(s1 < s2) && !(s2 < s1)) std::cout << "ok\n";
    htwg::string s3 = "Hello";
    if (s2 < s3) std::cout << "ok\n";
    if (!(s3 < s2)) std::cout << "ok\n";
}

