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

#include "Mesh3DView.hpp"

#include "../engine/io/MeshManager.hpp"
#include "../engine/math/opengl_matrix.hpp"

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

Mesh3DView::Mesh3DView(fV3 position_, const char* mesh_name) :
transform(),
mesh(NULL),
position(position_)
{
  // translate and scale the transform matrix
  transform.toIdentity();
  addTranslation(transform, position);

  // get the mesh based on the identifier
  mesh = MeshManager::getInstance()->get_mesh(mesh_name);
}


Mesh3DView::~Mesh3DView()
{
  //! DON'T free the mesh (it may be shared), MeshManager does this for us!
}

//! ----------------------------------------------------------------------------
//! RENDER
//! ----------------------------------------------------------------------------

void Mesh3DView::draw() const
{
  glPushMatrix();
    applyTransform(transform);
    mesh->draw();
  glPopMatrix();
}

//! ----------------------------------------------------------------------------
//! SPATIAL POSITION
//! ----------------------------------------------------------------------------

void Mesh3DView::setPosition(fV3 position)
{
  transform.toIdentity();
  addTranslation(transform, position);
}

void Mesh3DView::setRotationX(float degrees)
{
  transform.toIdentity();
  addTranslation(transform, position);
  addRotationX(transform, degrees);
}

void Mesh3DView::setRotationY(float degrees)
{
  transform.toIdentity();
  addTranslation(transform, position);
  addRotationY(transform, degrees);
}

void Mesh3DView::setRotationZ(float degrees)
{
  transform.toIdentity();
  addTranslation(transform, position);
  addRotationZ(transform, degrees);
}
