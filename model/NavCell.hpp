#ifndef NAVCELL_H_INCLUDED
#define NAVCELL_H_INCLUDED

#include "../engine/math/V3.hpp"

class NavCell
{
  //! CONSTANTS
public:
  static const fV3 size;

  //! ATTRIBUTES
public:
  unsigned int cost;
  bool obstacle;

  //! METHODS
public:
  NavCell(bool obstacle_ = false, unsigned int cost_ = 0);
  virtual ~NavCell();
};

#endif // NAVCELL_H_INCLUDED
