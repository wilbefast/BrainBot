#include "BrainBot.hpp"

#include "../engine/math/wjd_math.h"
#include "../engine/math/opengl_matrix.hpp"

#include "../engine/io/GraphicsManager.hpp"
#include "../engine/io/MeshManager.hpp"


#define WALKABLE(x,y)  grid->getCell(grid->getGridPosition(uV2(x,y)))

#include <iostream>

#define SIZE 32
#define HSIZE 16


//! ----------------------------------------------------------------------------
//! GLOBAL VARIABLES
//! ----------------------------------------------------------------------------
static Mesh3D* m = NULL;
static Texture *t = NULL;

//static Colour bot_emissive(1.0f, 1.0f, 1.0f);

//! ----------------------------------------------------------------------------
//! FUNCTIONS
//! ----------------------------------------------------------------------------

void BrainBot::load_assets()
{
  t= GraphicsManager::getInstance()->get_texture("alien_bot1");
  m= MeshManager::getInstance()->get_mesh("spider");
}

bool blocked(float x, float y, NavGrid* grid)
{
  if(x < HSIZE || y < HSIZE || x >= (int)grid->n_cells.x*NavCell::size.x - HSIZE
                    || y >= (int)grid->n_cells.y*NavCell::size.y - HSIZE)
    return true;
  else
  {
    uV2 grid_pos = grid->vertexToGridPos(fV2(x-HSIZE, y-SIZE));
      if(grid->getCell(grid_pos).obstacle) return true;
    grid_pos = grid->vertexToGridPos(fV2(x-HSIZE, y+HSIZE));
      if(grid->getCell(grid_pos).obstacle) return true;
    grid_pos = grid->vertexToGridPos(fV2(x+HSIZE, y-HSIZE));
      if(grid->getCell(grid_pos).obstacle) return true;
    grid_pos = grid->vertexToGridPos(fV2(x+HSIZE, y+HSIZE));
      if(grid->getCell(grid_pos).obstacle) return true;
    return false;
  }

}

//! ----------------------------------------------------------------------------
//! CONSTRUCTOR
//! ----------------------------------------------------------------------------
BrainBot::BrainBot(fV2 position_) :
position(position_),
speed()
{

}


//! ----------------------------------------------------------------------------
//! MUTATORS
//! ----------------------------------------------------------------------------

void BrainBot::setPosition(fV2 position_)
{
  position = position_;
}

void BrainBot::move(fV2 amount, NavGrid* grid)
{
  ///smooth to collision

  speed += amount*0.4f;


  int xvar = SIGN(speed.x);
  int yvar = SIGN(speed.y);

  if(blocked(position.x + speed.x,
             position.y,
             grid))
  {
    //snap to collision position
    while(!blocked(position.x + xvar,
                   position.y,
                   grid))
        position.x += xvar;
    speed.x = 0;
  }
  if(blocked(position.x,
             position.y + speed.y,
             grid))
  {
    //snap to collision position
    while(!blocked(position.x,
                   position.y + yvar,
                   grid))
      position.y += yvar;
    speed.y = 0;
  }
  if(blocked(position.x + speed.x,
             position.y + speed.y,
             grid))
  {
    //snap to collision position
    while(!blocked(position.x, position.y + yvar, grid))
    {
      position.x += xvar;
      position.y += yvar;
    }
    speed.x = speed.y = 0;
  }

  position += speed;

  speed *= 0.9f;
  if((speed.x > 0 && speed.x < 0.01f) || (speed.x < 0 && speed.x > 0.01f))
    speed.x = 0;
  if((speed.y > 0 && speed.y < 0.01f) || (speed.y < 0 && speed.y > 0.01f))
    speed.y = 0;

}


Texture* BrainBot::get_texture()
{
  return t;
}

void BrainBot::render()
{
  glPushMatrix();

    glTranslatef(position.x, position.y, -50);
    glScalef(4, 4, 4);

    m->draw();
  glPopMatrix();

  /*M44<GLfloat> const* mv = getGLMatrix(GL_MODELVIEW_MATRIX);

  V4<GLfloat> ox = mv->row(0), oy = mv->row(1);


  float half_size = 16.0f;


  static fV4 v4_pos;
    v4_pos = fV4(position.x, position.y, 0, 1);

  V4<GLfloat> p1 = v4_pos - ox*half_size + oy*half_size,
              p2 = v4_pos + ox*half_size + oy*half_size,
              p3 = v4_pos + ox*half_size - oy*half_size,
              p4 = v4_pos - ox*half_size - oy*half_size;

  //glColor3f(1.0f, 1.0f, 1.0f);
  glMaterialfv(GL_FRONT, GL_EMISSION, bot_emissive.front());
  glBindTexture(GL_TEXTURE_2D, get_texture()->getHandle());
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
  glBindTexture(GL_TEXTURE_2D, 0);*/
}
