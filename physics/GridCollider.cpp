/*
Copyright (C) 2012 William James Dyce

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


#include "GridCollider.hpp"


//! ----------------------------------------------------------------------------
//! FUNCTIONS
//! ----------------------------------------------------------------------------

bool blocked(float x, float y, float size, NavGrid* grid)
{
  float hsize = size / 2;

  if(x < hsize
 || y < hsize
 || x >= (int)grid->n_cells.x * NavCell::size.x - hsize
 || y >= (int)grid->n_cells.y * NavCell::size.y - hsize)
    return true;
  else
  {
    uV2 grid_pos = grid->vertexToGridPos(fV2(x-hsize, y-hsize));
      if(grid->getCell(grid_pos).obstacle) return true;

    grid_pos = grid->vertexToGridPos(fV2(x-hsize, y+hsize));
      if(grid->getCell(grid_pos).obstacle) return true;

    grid_pos = grid->vertexToGridPos(fV2(x+hsize, y-hsize));
      if(grid->getCell(grid_pos).obstacle) return true;

    grid_pos = grid->vertexToGridPos(fV2(x+hsize, y+hsize));
      if(grid->getCell(grid_pos).obstacle) return true;

    return false;
  }
}


//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

GridCollider::GridCollider(size_t size_, NavGrid *grid_,
                           PhysicalProperties physics_) :
size(size_),
speed(),
grid(grid_),
physics(physics_)
{

}

//! ----------------------------------------------------------------------------
//! IMPLEMENTS -- COLLISIONMASK
//! ----------------------------------------------------------------------------

int GridCollider::update(fV3& position, float t_delta)
{
  ///smooth to collision
  int xvar = SIGN(speed.x);
  int yvar = SIGN(speed.y);

  if(blocked(position.x + speed.x, position.y, size, grid))
  {
    //snap to collision position
    while(!blocked(position.x + xvar, position.y, size, grid))
        position.x += xvar;
    speed.x = 0;
  }
  if(blocked(position.x, position.y + speed.y, size, grid))
  {
    //snap to collision position
    while(!blocked(position.x, position.y + yvar, size, grid))
      position.y += yvar;
    speed.y = 0;
  }
  if(blocked(position.x + speed.x, position.y + speed.y, size, grid))
  {
    //snap to collision position
    while(!blocked(position.x, position.y + yvar, size, grid))
    {
      position.x += xvar;
      position.y += yvar;
    }
    speed.x = speed.y = 0;
  }

  //! update position
  position += speed;

  //! apply friction
  speed *= physics.friction;

  //! apply terminal velocity
  if(ABS(speed.x) < 0.01f)
    speed.x = 0;
  if(ABS(speed.y) < 0.01f)
    speed.y = 0;

  //! don't destroy the object
  return 0;
}

void GridCollider::push(fV3 const& direction)
{
  speed += direction * physics.acceleration;
}
