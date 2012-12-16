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

static Colour road_ambient(0.05f, 0.05f, 0.1f),
              road_diffuse(0.2f, 0.2f, 0.4f),
              road_specular(0.3f, 0.3f, 0.6f),
              road_emission(0.0f, 0.0f, 0.0f);
static float road_shine = 60;


static Colour building_ambient(0.4f, 0.3f, 0.3f),
              building_diffuse(0.7f, 0.6f, 0.6f),
              building_emission(0.0f, 0.0f, 0.0f),
              building_specular(0.0f, 0.0f, 0.0f);
static float building_shine = 128;

static Colour roof_ambient(0.4f, 0.2f, 0.2f),
              roof_diffuse(0.4f, 0.2f, 0.2f);

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
      vertex = navGrid->gridPosToVertex(grid_pos);

      int obstructed = (navGrid->getCell(grid_pos).obstacle) ? 1 : 0;

      // Draw the tiles
      glBegin(GL_QUADS);
        if(!obstructed)
        {
          glMaterialfv(GL_FRONT, GL_AMBIENT, road_ambient.front());
          glMaterialfv(GL_FRONT, GL_SPECULAR, road_specular.front());
          glMaterialfv(GL_FRONT, GL_DIFFUSE, road_diffuse.front());
          glMaterialfv(GL_FRONT, GL_EMISSION, road_emission.front());
          glMaterialfv(GL_FRONT, GL_SHININESS, &road_shine);
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
          static fV3  left(-1,0,0), right(1,0,0), up(0,0,-1),
                      forward(0,1,0), back(0,-1,0);


          glMaterialfv(GL_FRONT, GL_AMBIENT, building_ambient.front());
          glMaterialfv(GL_FRONT, GL_SPECULAR, building_specular.front());
          glMaterialfv(GL_FRONT, GL_DIFFUSE, building_diffuse.front());
          glMaterialfv(GL_FRONT, GL_EMISSION, building_emission.front());
          glMaterialfv(GL_FRONT, GL_SHININESS, &building_shine);
          glColor3f(0.7f, 0.7f, 0.8f);
          // left face
            glNormal3fv(left.front());
            glVertex3fv(vertex.front()); // back bottom left
          vertex.y += NavCell::size.y;
            glNormal3fv(left.front());
            glVertex3fv(vertex.front()); // front bottom left
          vertex.z -= NavCell::size.z;
            glNormal3fv(left.front());
            glVertex3fv(vertex.front()); // front top left
          vertex.y -= NavCell::size.y;
            glNormal3fv(left.front());
            glVertex3fv(vertex.front()); // back top left
          // back face
            glNormal3fv(back.front());
            glVertex3fv(vertex.front()); // back top left
          vertex.x += NavCell::size.x;
            glNormal3fv(back.front());
            glVertex3fv(vertex.front()); // back top right
          vertex.z += NavCell::size.z;
            glNormal3fv(back.front());
            glVertex3fv(vertex.front()); // back bottom right
          vertex.x -= NavCell::size.x;
            glNormal3fv(back.front());
            glVertex3fv(vertex.front()); // back bottom left
          vertex.x += NavCell::size.x;
          // right face
            glNormal3fv(right.front());
            glVertex3fv(vertex.front()); // back bottom right
          vertex.z -= NavCell::size.z;
            glNormal3fv(right.front());
            glVertex3fv(vertex.front()); // back top right
          vertex.y += NavCell::size.y;
            glNormal3fv(right.front());
            glVertex3fv(vertex.front()); // front top right
          vertex.z += NavCell::size.z;
            glNormal3fv(right.front());
            glVertex3fv(vertex.front());  // front bottom right
          // front face
            glNormal3fv(forward.front());
            glVertex3fv(vertex.front()); // front bottom right
          vertex.z -= NavCell::size.z;
            glNormal3fv(forward.front());
            glVertex3fv(vertex.front()); // front top right
          vertex.x -= NavCell::size.x;
            glNormal3fv(forward.front());
            glVertex3fv(vertex.front()); // front top left
          vertex.z += NavCell::size.z;
            glNormal3fv(forward.front());
            glVertex3fv(vertex.front()); // front bottom left
          vertex.z -= NavCell::size.z;
          // top face
            glNormal3fv(up.front());
            glVertex3fv(vertex.front());  // front bottom left
          vertex.x += NavCell::size.x;
            glNormal3fv(up.front());
            glVertex3fv(vertex.front()); // front bottom left
          vertex.y -= NavCell::size.y;
            glNormal3fv(up.front());
            glVertex3fv(vertex.front());
          vertex.x -= NavCell::size.x;
            glNormal3fv(up.front());
            glVertex3fv(vertex.front());
        }
      glEnd();
    }
  }
}
