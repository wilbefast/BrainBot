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

#include <stdio.h>

//! ----------------------------------------------------------------------------
//! GLOBAL VARIABLES
//! ----------------------------------------------------------------------------

static Texture* window_t = NULL;

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

NavGridView::NavGridView(NavGrid * navGrid_) : navGrid(navGrid_)
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
   if(window_t == NULL)
     window_t = GraphicsManager::getInstance()->get_texture("windows");

  static uV2 grid_pos;
  for(grid_pos.x = 0; grid_pos.x < navGrid->n_cells.x; grid_pos.x++)
  {
    for(grid_pos.y = 0; grid_pos.y < navGrid->n_cells.y; grid_pos.y++)
    {
      static fV3 vertex;
      vertex = navGrid->getCellPosition(grid_pos);

      int obstructed = (navGrid->getCell(grid_pos).obstacle) ? 1 : 0;

      // Draw the tiles
      glBegin(GL_QUADS);
        if(!obstructed)
        {
          glColor3f(0.4f, 0.3f, 0.3f);
          glVertex3fv(vertex.front());
          vertex.y += NavCell::size.y;
          glVertex3fv(vertex.front());
          vertex.x += NavCell::size.x;
          glVertex3fv(vertex.front());
          vertex.y -= NavCell::size.y;
          glVertex3fv(vertex.front());
        }
        else
        {
          glColor3f(0.7f, 0.7f, 0.8f);
          // left face
          glVertex3fv(vertex.front());
          vertex.y += NavCell::size.y;
          glVertex3fv(vertex.front());
          vertex.z -= NavCell::size.z;
          glVertex3fv(vertex.front());
          vertex.y -= NavCell::size.y;
          glVertex3fv(vertex.front());
          // back face
          glVertex3fv(vertex.front());
          vertex.x += NavCell::size.x;
          glVertex3fv(vertex.front());
          vertex.z += NavCell::size.z;
          glVertex3fv(vertex.front());
          vertex.x -= NavCell::size.x;
          glVertex3fv(vertex.front());
          vertex.x += NavCell::size.x;
          // right face
          glVertex3fv(vertex.front());
          vertex.z -= NavCell::size.z;
          glVertex3fv(vertex.front());
          vertex.y += NavCell::size.y;
          glVertex3fv(vertex.front());
          vertex.z += NavCell::size.z;
          glVertex3fv(vertex.front());
          // front face
          //glBindTexture(GL_TEXTURE_2D, window_t->getHandle());
            glTexCoord2f(1,1);
            glVertex3fv(vertex.front());
          vertex.z -= NavCell::size.z;
            glTexCoord2f(1,0);
            glVertex3fv(vertex.front());
          vertex.x -= NavCell::size.x;
            glTexCoord2f(0,0);
            glVertex3fv(vertex.front());
          vertex.z += NavCell::size.z;
            glTexCoord2f(0,1);
            glVertex3fv(vertex.front());
          vertex.z -= NavCell::size.z;
          //glBindTexture(GL_TEXTURE_2D, 0);
          // top face
          glVertex3fv(vertex.front());
          vertex.x += NavCell::size.x;
          glVertex3fv(vertex.front());
          vertex.y -= NavCell::size.y;
          glVertex3fv(vertex.front());
          vertex.x -= NavCell::size.x;
          glVertex3fv(vertex.front());
        }
      glEnd();
    }
  }
}
