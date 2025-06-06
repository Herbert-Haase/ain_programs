#include "fachnote.h"
#include <stdexcept>

fachnote::fachnote(const std::string &s, const benotung &n) : fach(s), note(n) {
  if (n == benotung{0}) {
    throw std::invalid_argument("" /* + std::to_string(n)*/);
  }
}

// fachnote::~fachnote()
// {
//   delete this->note;
//   delete this->fach;
// }
