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

#pragma once

#include "../model/ObjectAlignedBoundingBox.hpp"

#include "../engine/math/V4.hpp"
#include "../engine/math/M44.hpp"

#include "../engine/graphics/3D/Mesh3D.hpp"

namespace Troopy {
namespace Navigation {

class GameObject {


//! METHODS
public:
  GameObject(fV4 position_);
  virtual ~GameObject();
  bool isColliding(GameObject& other) const;


//! ATTRIBUTES
protected:
  fM44 transform; // position, rotation
  ObjectAlignedBoundingBox boundingBox;

public:
  Mesh3D* mesh;
};

}
}
