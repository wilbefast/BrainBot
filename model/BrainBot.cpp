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

//! ----------------------------------------------------------------------------
//! FUNCTIONS
//! ----------------------------------------------------------------------------

void BrainBot::load_assets()
{
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

void BrainBot::render()
{
  glPushMatrix();
    glTranslatef(position.x, position.y, -50);
    glScalef(4, 4, 4);
    m->draw();
  glPopMatrix();
}
