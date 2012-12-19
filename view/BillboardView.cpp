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

#include "BillboardView.hpp"

#include "../engine/io/GraphicsManager.hpp"

#include "../engine/math/M44.hpp"
#include "../engine/math/opengl_matrix.hpp"

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

BillboardView::BillboardView(fV3 position_, size_t size_, const char* texture_name) :
texture(NULL),
position(position_),
size(size_)
{
  // get the mesh based on the identifier
  texture = GraphicsManager::getInstance()->get_texture(texture_name);
}


BillboardView::~BillboardView()
{
  //! DON'T free the texture (it may be shared), GraphicsManager does this for us!
}

//! ----------------------------------------------------------------------------
//! RENDER
//! ----------------------------------------------------------------------------

void BillboardView::draw() const
{
  // get referential that is facing the camera
  M44<GLfloat> const* mv = getGLMatrix(GL_MODELVIEW_MATRIX);
  V4<GLfloat> ox = mv->row(0), oy = mv->row(1);

  // calculate corner positions
  float half_size = size/2;
  V4<GLfloat> position4(position.x, position.y, position.z, 1),
              p1 = position4 - ox*half_size + oy*half_size,
              p2 = position4 + ox*half_size + oy*half_size,
              p3 = position4 + ox*half_size - oy*half_size,
              p4 = position4 - ox*half_size - oy*half_size;

  // draw a quad facing the camera
  glColor3f(1.0f, 1.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture->getHandle());
  glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);
    glVertex3fv(p1.front());
    glTexCoord2f(0, 1);
    glVertex3fv(p4.front());
    glTexCoord2f(1, 1);
    glVertex3fv(p3.front());
    glTexCoord2f(1, 0);
    glVertex3fv(p2.front());
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
}

//! ----------------------------------------------------------------------------
//! SPATIAL POSITION
//! ----------------------------------------------------------------------------

void BillboardView::setPosition(fV3 position_)
{
  position = position_;
}
