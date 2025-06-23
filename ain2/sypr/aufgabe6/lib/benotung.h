#ifndef BENOTUNG_H
#define BENOTUNG_H

class benotung final {
private:
  int note;

public:
  explicit benotung(int n);
  benotung(const benotung &) = default;
  benotung(benotung &&) = default;
  ~benotung() = default;
  benotung &operator=(const benotung &) = default;
  benotung &operator=(benotung &&) = default;

  static const benotung beste;
  static const benotung schlechteste;

  int int_value() const;
  bool ist_bestanden() const;
};
bool operator==(const benotung &n1, const benotung &n2);

#endif
