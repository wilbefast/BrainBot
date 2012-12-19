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

#ifndef GRIDCOLLIDER_HPP_INCLUDED
#define GRIDCOLLIDER_HPP_INCLUDED

#include "CollisionMask.hpp"

class GridCollider : public CollisionMask
{
  //! ATTRIBUTES
private:
  size_t size;
  fV3 speed;

  //! METHODS
public:
  // constructors, destructors
  GridCollider(size_t size);

  // implements -- CollisionMask
  void update(fV3& position);
  void push(fV3 const& direction);
};

#endif // GRIDCOLLIDER_HPP_INCLUDED
