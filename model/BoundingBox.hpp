/*
Copyright (C) 2012 William James Dyce and Guillaume Surroca

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

#ifndef BOUNDINGBOX_HPP_INCLUDED
#define BOUNDINGBOX_HPP_INCLUDED

#include "../engine/math/M44.hpp"
#include "../engine/math/V4.hpp"

class BoundingBox
{
  //! ATTRIBUTES
private:
  fM44 offset_transform;
  fV4 size;

  //! METHODS
public:
  // constructors
  BoundingBox(fV4 size_);

};

#endif // BOUNDINGBOX_HPP_INCLUDED
