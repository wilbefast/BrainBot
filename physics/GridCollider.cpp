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

bool blocked(float x, float y, size_t radius, NavGrid const* grid)
{
  if(x < radius
 || y < radius
 || x >= (int)grid->n_cells.x * NavCell::size.x - radius
 || y >= (int)grid->n_cells.y * NavCell::size.y - radius)
    return true;
  else
  {
    uV2 grid_pos = grid->vertexToGridPos(fV2(x-radius, y-radius));
      if(grid->getCell(grid_pos).obstacle) return true;

    grid_pos = grid->vertexToGridPos(fV2(x-radius, y+radius));
      if(grid->getCell(grid_pos).obstacle) return true;

    grid_pos = grid->vertexToGridPos(fV2(x+radius, y-radius));
      if(grid->getCell(grid_pos).obstacle) return true;

    grid_pos = grid->vertexToGridPos(fV2(x+radius, y+radius));
      if(grid->getCell(grid_pos).obstacle) return true;

    return false;
  }
}


//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

GridCollider::GridCollider(float size_, NavGrid const* grid_,
                           PhysicalProperties physics_) :
size(size_),
radius(size_ / 2),
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

  if(blocked(position.x + speed.x, position.y, radius, grid))
  {
    //snap to collision position
    while(!blocked(position.x + xvar, position.y, radius, grid))
        position.x += xvar;
    speed.x = 0;
  }
  if(blocked(position.x, position.y + speed.y, radius, grid))
  {
    //snap to collision position
    while(!blocked(position.x, position.y + yvar, radius, grid))
      position.y += yvar;
    speed.y = 0;
  }
  if(blocked(position.x + speed.x, position.y + speed.y, radius, grid))
  {
    //snap to collision position
    while(!blocked(position.x, position.y + yvar, radius, grid))
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

float GridCollider::getRadius() const
{
  return radius;
}

void GridCollider::setRadius(float radius_)
{
  radius = radius_;
}
