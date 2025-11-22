//
// htwg_vector_test.cpp
//
// Beispiel-Anwendung fuer die stark vereinfachte Vektor-Klasse
//
// Autor: H.Drachenfels
// Erstellt am: 19.01.2012
//

#include <iostream>
#include "htwg_vector.h"

int main()
{
    htwg::vector<int> v(2);
    v[0] = 10;
    v[1] = 20;

    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << '\n';
    }
}

