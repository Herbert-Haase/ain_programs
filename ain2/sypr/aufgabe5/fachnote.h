#ifndef FACHNOTE_H
#define FACHNOTE_H

#include "benotung.h"
#include <string>

class fachnote final {
public:
  std::string fach;
  benotung note;

  fachnote(const std::string &, const benotung &);
  fachnote(const fachnote &f) = delete;
  fachnote &operator=(const fachnote &f) = delete;
  fachnote(fachnote &&f) = delete;
  fachnote &operator=(fachnote &&f) = delete;
  ~fachnote();
};

#endif
