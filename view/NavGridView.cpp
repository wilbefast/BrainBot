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

static Texture *building_tex = NULL, *road_tex = NULL;

static fV3  left(-1,0,0), right(1,0,0), up(0,0,-1), forward(0,1,0), back(0,-1,0);

static Colour road_ambient(0.15f, 0.1f, 0.2f),
              road_diffuse(0.6f, 0.5f, 0.7f),
              road_specular(0.3f, 0.3f, 0.6f),
              road_emission(0.0f, 0.0f, 0.0f);
static float road_shine = 64;


static Colour building_ambient(0.4f, 0.2f, 0.2f),
              building_diffuse(0.8f, 0.7f, 0.7f),
              building_specular(0.0f, 0.0f, 0.0f),
              building_emission(0.0f, 0.0f, 0.0f);
static float building_shine = 128;

static Colour roof_ambient(0.4f, 0.2f, 0.2f),
              roof_diffuse(0.4f, 0.2f, 0.2f);

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
  //! get texture handles if not already done
  if(building_tex == NULL)
   building_tex = GraphicsManager::getInstance()->get_texture("concrete");
  if(road_tex == NULL)
   road_tex = GraphicsManager::getInstance()->get_texture("asphalt");

  //! draw roads and buildings separetly to avoid too much binding/unbinding
  draw_all_buildings();
  draw_all_roads();
}

//! ----------------------------------------------------------------------------
//! DRAW BUILDINGS
//! ----------------------------------------------------------------------------

inline void draw_building(fV3 position, fV3 const& size)
{
    // left face
    glTexCoord2f(0.0f, 1.0f);
    glNormal3fv(left.front());
    glVertex3fv(position.front()); // back bottom left
  position.y += size.y;
    glTexCoord2f(1.0f, 1.0f);
    glNormal3fv(left.front());
    glVertex3fv(position.front()); // front bottom left
  position.z -= size.z;
    glTexCoord2f(1.0f, 0.0f);
    glNormal3fv(left.front());
    glVertex3fv(position.front()); // front top left
  position.y -= size.y;
    glTexCoord2f(0.0f, 0.0f);
    glNormal3fv(left.front());
    glVertex3fv(position.front()); // back top left

  // back face
    glTexCoord2f(1.0f, 0.0f);
    glNormal3fv(back.front());
    glVertex3fv(position.front()); // back top left
  position.x += size.x;
    glTexCoord2f(0.0f, 0.0f);
    glNormal3fv(back.front());
    glVertex3fv(position.front()); // back top right
  position.z += size.z;
    glTexCoord2f(0.0f, 1.0f);
    glNormal3fv(back.front());
    glVertex3fv(position.front()); // back bottom right
  position.x -= size.x;
    glTexCoord2f(1.0f, 1.0f);
    glNormal3fv(back.front());
    glVertex3fv(position.front()); // back bottom left

  // right face
  position.x += size.x;
    glTexCoord2f(1.0f, 1.0f);
    glNormal3fv(right.front());
    glVertex3fv(position.front()); // back bottom right
  position.z -= size.z;
    glTexCoord2f(1.0f, 0.0f);
    glNormal3fv(right.front());
    glVertex3fv(position.front()); // back top right
  position.y += size.y;
    glTexCoord2f(0.0f, 0.0f);
    glNormal3fv(right.front());
    glVertex3fv(position.front()); // front top right
  position.z += size.z;
    glTexCoord2f(0.0f, 1.0f);
    glNormal3fv(right.front());
    glVertex3fv(position.front());  // front bottom right

  // front face
    glTexCoord2f(1.0f, 1.0f);
    glNormal3fv(forward.front());
    glVertex3fv(position.front()); // front bottom right
  position.z -= size.z;
    glTexCoord2f(1.0f, 0.0f);
    glNormal3fv(forward.front());
    glVertex3fv(position.front()); // front top right
  position.x -= size.x;
    glTexCoord2f(0.0f, 0.0f);
    glNormal3fv(forward.front());
    glVertex3fv(position.front()); // front top left
  position.z += size.z;
    glTexCoord2f(0.0f, 1.0f);
    glNormal3fv(forward.front());
    glVertex3fv(position.front()); // front bottom left

  // top face
  position.z -= size.z;
    glTexCoord2f(0.0f, 1.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front());  // front top left
  position.x += size.x;
    glTexCoord2f(1.0f, 1.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front()); // front top right
  position.y -= size.y;
    glTexCoord2f(1.0f, 0.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front()); // back top right
  position.x -= size.x;
    glTexCoord2f(0.0f, 0.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front()); // back top left
}

void NavGridView::draw_all_buildings()
{
  static uV2 grid_pos;

  //! activate the material
  glMaterialfv(GL_FRONT, GL_AMBIENT, building_ambient.front());
  glMaterialfv(GL_FRONT, GL_SPECULAR, building_specular.front());
  glMaterialfv(GL_FRONT, GL_DIFFUSE, building_diffuse.front());
  glMaterialfv(GL_FRONT, GL_EMISSION, building_emission.front());
  glMaterialfv(GL_FRONT, GL_SHININESS, &building_shine);

  //! activate the texture BEFORE glBegin
  glBindTexture(GL_TEXTURE_2D, building_tex->getHandle());
  glBegin(GL_QUADS);
  for(grid_pos.x = 0; grid_pos.x < grid->n_cells.x; grid_pos.x++)
  {
    for(grid_pos.y = 0; grid_pos.y < grid->n_cells.y; grid_pos.y++)
    {
      // check that the cell is a building
      if(!grid->isObstacle(grid_pos))
        continue;

      // draw the building
      draw_building(grid->gridPosToVertex(grid_pos), grid->gridPosToSize(grid_pos));
    }
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
}

//! ----------------------------------------------------------------------------
//! DRAW ROADS
//! ----------------------------------------------------------------------------

inline void draw_road(fV3 position, fV3 const& size)
{
    glTexCoord2f(0.0f, 0.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front());
  position.y += size.y;
    glTexCoord2f(0.0f, 1.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front());
  position.x += size.x;
    glTexCoord2f(1.0f, 1.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front());
  position.y -= size.y;
    glTexCoord2f(1.0f, 0.0f);
    glNormal3fv(up.front());
    glVertex3fv(position.front());
}

void NavGridView::draw_all_roads()
{
  static uV2 grid_pos;

  //! activate the material
  glMaterialfv(GL_FRONT, GL_AMBIENT, road_ambient.front());
  glMaterialfv(GL_FRONT, GL_SPECULAR, road_specular.front());
  glMaterialfv(GL_FRONT, GL_DIFFUSE, road_diffuse.front());
  glMaterialfv(GL_FRONT, GL_EMISSION, road_emission.front());
  glMaterialfv(GL_FRONT, GL_SHININESS, &road_shine);

  //! activate the texture BEFORE glBegin
  glBindTexture(GL_TEXTURE_2D, road_tex->getHandle());
  glBegin(GL_QUADS);
  for(grid_pos.x = 0; grid_pos.x < grid->n_cells.x; grid_pos.x++)
  {
    for(grid_pos.y = 0; grid_pos.y < grid->n_cells.y; grid_pos.y++)
    {
      // check that the cell is a road
      if(grid->isObstacle(grid_pos))
        continue;

      // draw the building
      draw_road(grid->gridPosToVertex(grid_pos), grid->gridPosToSize(grid_pos));
    }
  }
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
}



