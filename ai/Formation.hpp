#ifndef FORMATION_HPP_INCLUDED
#define FORMATION_HPP_INCLUDED

#include "../engine/math/V3.hpp"

#include "../model/GameObject.hpp"

//! **ABSTRACT**
class Formation
{
  //! METHODS
public:
  // interface
  virtual void form(fV3 centre, fV3 direction, gobject_container& objs) = 0;
};

#endif // FORMATION_HPP_INCLUDED
