//
// io.cpp
//
// Ein-/Ausgabe mit C++.
// 
// Autor: H.Drachenfels
// Erstellt am: 21.6.2011
//

#include <iostream>

int main()
{
  std::cout << "Dezimalzahl eingeben: ";
  int zahl;
  std::cin >> zahl;
  std::cout << "Hexadezimalzahl: " << std::hex << zahl << std::endl;
}

