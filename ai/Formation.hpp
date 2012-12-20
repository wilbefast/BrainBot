#ifndef FORMATION_HPP_INCLUDED
#define FORMATION_HPP_INCLUDED

#include "../engine/math/V3.hpp"

//! **ABSTRACT**
class Formation
{
  //! METHODS
public:
  // interface
  virtual void setSpacing(float spacing_) = 0;
  virtual void setStrength(size_t strength_) = 0;
  virtual fV3 getOffset(fV3 direction, size_t member_i) const = 0;
};

#endif // FORMATION_HPP_INCLUDED
