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

#include "NavGrid.hpp"
#include "../ai/PathSearch.hpp"

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------


NavGrid::NavGrid(fV3 origin_, uV2 n_cells_) :
n_cells(n_cells_),
origin(origin_)
{
  // allocate memory for cells
  cells = new NavCell**[n_cells.y];
  for(unsigned int r = 0; r < n_cells.y; r++)
    cells[r] = new NavCell*[n_cells.x];

  // allocate memory for cells
  uV2 grid_pos;
  for(grid_pos.y = 0; grid_pos.y < n_cells.y; grid_pos.y++)
  for(grid_pos.x = 0; grid_pos.x < n_cells.x; grid_pos.x++)
    cells[grid_pos.y][grid_pos.x] = new NavCell(grid_pos, true);
}

NavGrid::~NavGrid()
{
  // allocate memory from cells
  for(unsigned int r = 0; r < n_cells.y; r++)
    delete[] cells[r];
  delete[] cells;
}


//! ----------------------------------------------------------------------------
//! ACCESSORS
//! ----------------------------------------------------------------------------

fV3 NavGrid::getOrigin() const
{
  return origin;
}

uV2 const& NavGrid::getNCells() const
{
  return n_cells;
}

//! ----------------------------------------------------------------------------
//! COLLISION-TESTING
//! ----------------------------------------------------------------------------

bool NavGrid::isObstacle(uV2 grid_position) const
{
  if(!isValidGridPos(grid_position))
    return false;
	return cells[grid_position.y][grid_position.x]->obstacle;
}

bool NavGrid::isObstacle(fV3 position) const
{
  return isObstacle(iV2(position.x / NavCell::SIZE.x, position.y / NavCell::SIZE.y));
}

bool NavGrid::isValidGridPos(iV2 position) const
{
  return (position.x >= 0 && position.y >= 0
          && position.x < (int)n_cells.x && position.y < (int)n_cells.y);
}


//! ----------------------------------------------------------------------------
//! CONVERSION
//! ----------------------------------------------------------------------------

uV2 NavGrid::vertexToGridPos(fV2 position) const
{
	return uV2(position.x/NavCell::SIZE.x, position.y/NavCell::SIZE.y);
}

fV3 NavGrid::gridPosToVertex(uV2 position) const
{
  return fV3(origin.x + position.x*NavCell::SIZE.x,
             origin.y + position.y*NavCell::SIZE.y,
             origin.z);
}

fV3 NavGrid::gridPosToSize(uV2 position) const
{
  float h = (isValidGridPos(position))
          ? cells[position.y][position.x]->height : 0.0f;
  return fV3(NavCell::SIZE.x, NavCell::SIZE.y, h);
}

//! ----------------------------------------------------------------------------
//! PATHING
//! ----------------------------------------------------------------------------


path* NavGrid::getPath(uV2 source, uV2 destination)
{
  PathSearch s(this, source, destination);
  return s.getPath();
}

bool NavGrid::isLineOfSight(iV2 start, iV2 end) const
{
  if(!isValidGridPos(start) || !isValidGridPos(end))
    return false;

	// http://en.wikipedia.org/wiki/Bresenham's_line_algorithm
  int dx = abs(end.x - start.x),
      dy = abs(end.y - start.y),
      sx = (start.x < end.x) ? 1 : -1,
      sy = (start.y < end.y) ? 1 : -1,
      err = dx - dy;

  while(start.x != end.x || start.y != end.y)
  {
    if(isObstacle(start))
      // the way is shut (it was made by those who are dead)
      return false;

    int err2 = 2*err;

    //  move horizontally
    if(err2 > -dy)
    {
      err -= dy;
      start.x += sx;
    }

    // move vertically
    if(err2 < dx)
    {
      err += dx;
      start.y += sy;
    }
  }

  // made it - the way is clear!
  return true;
}

bool NavGrid::isLineOfSight(fV3 start, fV3 end) const
{
  return isLineOfSight(iV2(start.x / NavCell::SIZE.x, start.y / NavCell::SIZE.y),
                       iV2(end.x / NavCell::SIZE.x, end.y / NavCell::SIZE.y));
}
