/*
Copyright (C) 2012 William James Dyce

This program is free software: you can redistribute it and/or modify
it under he terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef COLLISIONMASK_HPP_INCLUDED
#define COLLISIONMASK_HPP_INCLUDED

#include "../engine/math/V3.hpp"

//! **ABSTRACT**
class CollisionMask
{
  //! INTERFACE
public:
  // constructors, destructors
  virtual ~CollisionMask() { }
  // mutators
  virtual int update(fV3& position, float t_delta) = 0;
  virtual void push(fV3 const& direction) = 0;
  // accessors
  virtual float getRadius() const = 0;
};

#endif // COLLISIONMASK_HPP_INCLUDED
