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

#include "GameObject.hpp"

#include "../engine/io/MeshManager.hpp"
#include "../engine/math/opengl_matrix.hpp"

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

GameObject::GameObject(fV3 position, const char* mesh_name) :
bbox(fV4(10, 10, 10)) //! FIXME
{
  // translate and scale the transform matrix
  transform.toIdentity();
  addTranslation(transform, position);
  addRotation(transform, 90);


  // get the mesh based on the identifier
  mesh = MeshManager::getInstance()->get_mesh(mesh_name);
}


GameObject::~GameObject()
{
}


//! ----------------------------------------------------------------------------
//! ACCESSORS
//! ----------------------------------------------------------------------------

bool GameObject::isColliding(GameObject& other) const
{
  //! FIXME
  return false;
}


//! ----------------------------------------------------------------------------
//! RENDER
//! ----------------------------------------------------------------------------

void GameObject::draw() const
{
  glPushMatrix();
    applyTransform(transform);
    mesh->draw();
  glPopMatrix();
}
