// funktional.cpp
#include <iostream>
#include <iomanip>
#include <functional>

namespace {
    double einlesen() {
        double d;
        std::cin >> d;
        return d;
    }

    // Funktion hoeherer Ordung: Funktion als Rueckgabewert
    std::function<double(double)> steuer_berechnung(bool ermaessigt) {
        double steuer = ermaessigt ? 1.07 : 1.19;
        return [=](double netto){ return netto * steuer; };
    }

    // Funktion hoeherer Ordung: Funktionen als Parameter
    double brutto(std::function<double()> netto, std::function<double(double)> versteuern) {
        return versteuern(netto());
    }
}

int main() {
    std::cout << std::fixed << std::setprecision(2)
              << brutto(einlesen, steuer_berechnung(true)) << '\n';
    std::cout << std::fixed << std::setprecision(2)
              << brutto(einlesen, steuer_berechnung(false)) << '\n';
}

