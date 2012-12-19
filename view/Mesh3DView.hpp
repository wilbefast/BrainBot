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

#ifndef MESH3DVIEW_HPP_INCLUDED
#define MESH3DVIEW_HPP_INCLUDED

#include "ObjectView.hpp"

#include "../engine/math/M44.hpp"
#include "../engine/graphics/3D/Mesh3D.hpp"


class Mesh3DView : public ObjectView
{
//! ATTRIBUTES
private:
  // position, rotation
  fM44 transform;
  // the mesh to draw, may be shared by multiple objects
  Mesh3D* mesh;
  // saved to regenerate matrix correctly
  fV3 position, scale;

//! METHODS
public:
  // constructors, destructors
  Mesh3DView(fV3 position, float scale_, const char* mesh_name);
  virtual ~Mesh3DView();
  // render
  void draw() const;
  // mutators
  void setPosition(fV3 position);
  void setRotationX(float degrees);
  void setRotationY(float degrees);
  void setRotationZ(float degrees);
};


#endif // MESH3DVIEW_HPP_INCLUDED
