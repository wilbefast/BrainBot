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

#include "../engine/opengl.h"

#include <stdio.h>


NavGridView::NavGridView(NavGrid * navGrid_) : navGrid(navGrid_)
{
}

NavGridView::~NavGridView()
{
}

void NavGridView::render()
 {
  float cell_size = navGrid->getCellSize();
  static uV2 grid_pos;
  for(grid_pos.x = 0; grid_pos.x < navGrid->getSize().x; grid_pos.x++) {
    for(grid_pos.y = 0; grid_pos.y < navGrid->getSize().y; grid_pos.y++) {

      static fV3 vertex;
        vertex = navGrid->getAbsoluteCellPosition(grid_pos);

      int obstructed = (navGrid->getCell(grid_pos).obstacle) ? 1 : 0;

      // Draw the tiles
      glColor3f(obstructed, 0.0f, 1.0f-obstructed);
      glBegin(GL_TRIANGLE_FAN);
        glVertex3fv(vertex.front());
        vertex.x += cell_size;
        glVertex3fv(vertex.front());
        vertex.y += cell_size;
        glVertex3fv(vertex.front());
        vertex.x -= cell_size;
        glVertex3fv(vertex.front());
      glEnd();
    }
  }
}
