#ifndef FACHNOTE_H
#define FACHNOTE_H

#include "benotung.h"
#include <string>

class fachnote final {
public:
  const std::string fach;
  const benotung note;

  fachnote(const std::string& s, const benotung n);
  fachnote(const fachnote &f) = delete;
  fachnote &operator=(const fachnote &f) = delete;
  fachnote(fachnote &&f) = delete;
  fachnote &operator=(fachnote &&f) = delete;
  ~fachnote() = default;
};

#endif
