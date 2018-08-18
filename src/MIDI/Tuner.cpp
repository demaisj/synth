#include <stdexcept>
#include <cmath>

#include "Tuner.hpp"

namespace MIDI {

  Tuner::Tuner(int base)
  : _base(base)
  { computeTable(); }
  Tuner::~Tuner()
  {}

  void Tuner::setBase(int base)
  {
    _base = base;
    computeTable();
  }
  int Tuner::getBase() const
  { return _base; }

  double Tuner::getFreq(int note) const
  {
    if (note < 0 || note > 127)
      throw std::runtime_error("Invalid note");

    return _table[note];
  }

  void Tuner::computeTable()
  {
    for (int i = 0; i < 127; ++i) {
       _table[i] = pow(2.0, (i - 69.0) / 12.0) * _base;
    }
  }

}