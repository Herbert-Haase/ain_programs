#include "fachnote.h"
#include <stdexcept>

fachnote::fachnote(const std::string& s, const benotung n) : fach(s), note(n) {
  if (s.size() == 0) {
    throw std::invalid_argument("fach darf nicht die Länge 0 haben");
  }
}
