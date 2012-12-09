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

#ifndef GAMEOBJECT_HPP_INCLUDED
#define GAMEOBJECT_HPP_INCLUDED

#include "../model/BoundingBox.hpp"

#include "../engine/math/V4.hpp"
#include "../engine/math/M44.hpp"

#include "../engine/graphics/3D/Mesh3D.hpp"

#include "../engine/utils/IntrusiveLinked.hpp"

class GameObject : public IntrusiveLinked
{
//! ATTRIBUTES
protected:
  fM44 transform; // position, rotation
  BoundingBox bbox;
  Mesh3D* mesh;

//! METHODS
public:
  // constructors, destructors
  GameObject(fV4 position_, const char* mesh_name);
  virtual ~GameObject();
  // accessors
  bool isColliding(GameObject& other) const;
  // render
  void draw() const;
};

#endif // GAMEOBJECT_HPP_INCLUDED
