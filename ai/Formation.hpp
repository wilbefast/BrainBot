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
  virtual void deployMembers(GameObject* first_member) const = 0;
};

#endif // FORMATION_HPP_INCLUDED
