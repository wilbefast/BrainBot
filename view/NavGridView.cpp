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

#include "../view/NavGridView.hpp"

#include "../engine/io/GraphicsManager.hpp"
#include "../engine/opengl.h"
#include "../engine/graphics/Colour.hpp"

//! ----------------------------------------------------------------------------
//! GLOBAL VARIABLES
//! ----------------------------------------------------------------------------

static Texture *texture = NULL;

static fV3  left(-1,0,0), right(1,0,0), up(0,0,-1), forward(0,1,0), back(0,-1,0);

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

NavGridView::NavGridView(NavGrid * grid_) : grid(grid_)
{
}

NavGridView::~NavGridView()
{
}

//! ----------------------------------------------------------------------------
//! DRAW
//! ----------------------------------------------------------------------------

void NavGridView::draw()
{
  //! get texture handle if not already done
  if(texture == NULL)
   texture = GraphicsManager::getInstance()->get_texture("city");

  /*
  //! draw roads and buildings separetly to avoid too much binding/unbinding
  draw_all_buildings();
  draw_all_roads();
  */
  draw_all();
}

//! ----------------------------------------------------------------------------
//! DRAW BUILDINGS
//! ----------------------------------------------------------------------------

inline void draw_building(fV3 position, fV3 const& size)
{
  glColor3f(1, 0, 0);
  //! left face
  glNormal3fv(left.front());

    /*
    4
    | \
    |   2
    3 / |
      \ |
        1
    */

  // 1. front bottom left
  position.y += size.y;
    glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(position.front());

  // 2. front top left
  position.z -= size.z;
    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(position.front());

  // 3. back bottom left
  position.y -= size.y;
  position.z += size.z;
    glTexCoord2f(0.5f, 1.0f);
    glVertex3fv(position.front());

  // 4. back top left
  position.z -= size.z;
    glTexCoord2f(0.5f, 0.0f);
    glVertex3fv(position.front());

  glColor3f(0, 1, 0);
  //! back face
  glNormal3fv(back.front());
  /*
    (*2)--4
     |  \ |
    (1)---3
  */

  // 3. back bottom right
  position.x += size.x;
  position.z += size.z;
    glTexCoord2f(0.5f, 0.0f);
    glVertex3fv(position.front());

  // 4. back top right
  position.z -= size.z;
    glTexCoord2f(0.5f, 1.0f);
    glVertex3fv(position.front());


  glColor3f(0, 0, 1);

  //! top face
  glNormal3fv(up.front());
  /*
       2---(*1)
      / \   /
     /   \ /
    4-----3
  */

  // -- break previous strip --
  glTexCoord2f(1.0f, 0.0f);
  glVertex3fv(position.front());

  // 2. back top left
  position.x -= size.x;
    glTexCoord2f(0.5f, 0.0f);
    glVertex3fv(position.front());

  // 3. front top right
  position.x += size.x;
  position.y += size.y;
    glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(position.front());

  // 4. front top left
  position.x -= size.x;
    glTexCoord2f(0.5f, 1.0f);
    glVertex3fv(position.front());


  glColor3f(1, 0, 1);
  //! front face
  glNormal3fv(forward.front());
  /* NB - texture is upside-down for this face!
     (*2)-(1)
     |  \  |
     4-----3
  */

  // 3. front bottom right
  position.z += size.z;
  position.x += size.x;
    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(position.front());

  // 4. front bottom left
  position.x -= size.x;
    glTexCoord2f(0.5f, 0.0f);
    glVertex3fv(position.front());

  glColor3f(1, 1, 1);
  //! right face
  glNormal3fv(right.front());
  /*
       (*1)
      /  |
     2 \ |
     |   3
     |  /
      4
  */

  // -- break previous strip --
  position.x += size.x;
  position.y -= size.y;
  position.z -= size.z;
    glTexCoord2f(1.0f, 0.0f);
    glVertex3fv(position.front());

  // 2. front top right
  position.y += size.y;
    glTexCoord2f(0.5f, 0.0f);
    glVertex3fv(position.front());

  // 3. back bottom right
  position.y -= size.y;
  position.z += size.z;
    glTexCoord2f(1.0f, 1.0f);
    glVertex3fv(position.front());

  // 4. front bottom right
  position.y += size.y;
    glTexCoord2f(0.5f, 1.0f);
    glVertex3fv(position.front());
}

//! ----------------------------------------------------------------------------
//! DRAW ROADS
//! ----------------------------------------------------------------------------

inline void draw_road(fV3 position, fV3 const& size)
{
  /*
        1---3
        | / |
        2---4
  */

  // top left
  glColor3f(1, 1, 1);
    glTexCoord2f(0.01f, 0.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front());

  // bottom left
  glColor3f(0, 1, 1);
  position.y += size.y;
    glTexCoord2f(0.01f, 1.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front());

  // top right
    glColor3f(1, 0, 1);
  position.y -= size.y;
  position.x += size.x;
    glTexCoord2f(0.49f, 0.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front());

  // bottom right
  position.y += size.y;
    glTexCoord2f(0.49f, 1.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front());
}

//! ----------------------------------------------------------------------------
//! DRAW EVERYTHING
//! ----------------------------------------------------------------------------

void NavGridView::draw_all()
{
  static uV2 grid_pos;
  static fV3 vertex_pos;
  //! activate the texture BEFORE glBegin
  glBindTexture(GL_TEXTURE_2D, texture->getHandle());
  glBegin(GL_TRIANGLE_STRIP);
  for(grid_pos.y = 0; grid_pos.y <  grid->n_cells.y; grid_pos.y++)
  {
    for(grid_pos.x = 0; grid_pos.x < grid->n_cells.x; grid_pos.x++)
    {
      vertex_pos = grid->gridPosToVertex(grid_pos);

      // check that the cell is a building or a road

      if(grid->isObstacle(grid_pos))
        // draw a building
        draw_building(vertex_pos, grid->gridPosToSize(grid_pos));
      else
        // draw a road
        draw_road(vertex_pos, grid->gridPosToSize(grid_pos));
    }
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
}
