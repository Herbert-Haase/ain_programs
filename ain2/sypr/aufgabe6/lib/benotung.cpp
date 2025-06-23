#include "benotung.h"
#include <stdexcept>
#include <string>

const benotung benotung::beste{10};
const benotung benotung::schlechteste{50};

benotung::benotung(int n) : note(n) {
  switch (n) {
  case 10:
  case 13:
  case 17:
  case 20:
  case 23:
  case 27:
  case 30:
  case 33:
  case 37:
  case 40:
  case 50:
    break;
  default:
    throw std::invalid_argument("unzulaessige Note " + std::to_string(n));
  }
}

bool operator==(const benotung &n1, const benotung &n2) {
  return &n1 == &n2 || n1.int_value() == n2.int_value();
}

int benotung::int_value() const { return this->note; }

bool benotung::ist_bestanden() const { return this->note <= 40; }
