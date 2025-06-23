#ifndef FACHNOTEN_LISTE_H
#define FACHNOTEN_LISTE_H

#include "fachnote.h"

typedef void (*delfun)(fachnote *);

class fachnoten_liste final {
private:
  delfun delf;
  class element;
  element *head;

public:
  explicit fachnoten_liste(delfun);
  ~fachnoten_liste();
  // Entity-Klasse ohne Kopier- und Move-Semantik
  fachnoten_liste(const fachnoten_liste &) = delete;
  fachnoten_liste &operator=(const fachnoten_liste &) = delete;
  fachnoten_liste(fachnoten_liste &&) = delete;
  fachnoten_liste &operator=(fachnoten_liste &&) = delete;

  fachnoten_liste &insert(fachnote *n);

  class iterator final {
  private:
    element *current;
    explicit iterator(element *);

  public:
    bool operator!=(const iterator &) const;
    fachnote *&operator*() const;
    iterator &operator++();

    friend class fachnoten_liste;
  };

  iterator begin();
  iterator end();
};

#endif
