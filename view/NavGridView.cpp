
#include "../view/NavGridView.hpp"

#include "../engine/opengl.h"

namespace Troopy {
namespace Navigation {

NavGridView::NavGridView(NavGrid * navGrid_) : navGrid(navGrid_) {
}

NavGridView::~NavGridView() {
}

void NavGridView::render() {
  float cell_size = navGrid->getCellSize();
  static fV3 vertex;

  for(unsigned int x = 0; x < navGrid->getSize().x; x++) {
    for(unsigned int y = 0; y < navGrid->getSize().y; y++) {

      int obstructed = (navGrid->getCell(uV2(x, y)).getProperty() == OBSTACLE);
      vertex = navGrid->getAbsoluteCellPosition(uV2(x, y));

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
        vertex.y -= cell_size;
      glEnd();

      // Outline the tiles
      vertex.z++;
      glColor3f(1.0f, 1.0f, 1.0f);
      glBegin(GL_LINE_LOOP);
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
