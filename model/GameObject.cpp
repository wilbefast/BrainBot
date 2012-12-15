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


#include "../engine/io/GraphicsManager.hpp"
#include "../engine/io/MeshManager.hpp"
#include "../engine/math/opengl_matrix.hpp"

//! ----------------------------------------------------------------------------
//! GLOBAL VARIABLES
//! ----------------------------------------------------------------------------
static Texture* t = NULL;

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

GameObject::GameObject(fV3 position, const char* mesh_name)
{
  if(t == NULL)
    t = GraphicsManager::getInstance()->get_texture("alien_bot2");

  // translate and scale the transform matrix
  transform.toIdentity();
  addTranslation(transform, position);
  addRotationX(transform, 90);

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
  /*glPushMatrix();
    applyTransform(transform);
    mesh->draw();
  glPopMatrix();*/



  M44<GLfloat> const* mv = getGLMatrix(GL_MODELVIEW_MATRIX);

  V4<GLfloat> ox = mv->row(0), oy = mv->row(1);


  float half_size = 16.0f;

  V4<GLfloat> p1 = transform[3] - ox*half_size + oy*half_size,
              p2 = transform[3] + ox*half_size + oy*half_size,
              p3 = transform[3] + ox*half_size - oy*half_size,
              p4 = transform[3] - ox*half_size - oy*half_size;

  glColor3f(1.0f, 1.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, t->getHandle());
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
