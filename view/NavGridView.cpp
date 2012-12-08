
#include "../view/NavGridView.hpp"

#include "../engine/opengl.h"

#include <stdio.h>

namespace Troopy {
namespace Navigation {

NavGridView::NavGridView(NavGrid * navGrid_) : navGrid(navGrid_) {
}

NavGridView::~NavGridView() {
}

void NavGridView::render() {
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

}
}
