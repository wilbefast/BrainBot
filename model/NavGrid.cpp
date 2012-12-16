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

  // dig out a maze
  dig_maze(uV2(n_cells.x/2, n_cells.y/2));
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

NavCell const& NavGrid::getCell(uV2 grid_position) const
{
	return *(cells[grid_position.y][grid_position.x]);
}

uV2 const& NavGrid::getNCells() const
{
  return n_cells;
}

uV2 NavGrid::vertexToGridPos(fV2 position) const
{
	return uV2(position.x/NavCell::size.x, position.y/NavCell::size.y);
}

fV3 NavGrid::gridPosToVertex(uV2 position) const
{
  return fV3(origin.x + position.x*NavCell::size.x,
             origin.y + position.y*NavCell::size.y,
             origin.z);
}

bool NavGrid::isValidGridPos(iV2 position) const
{
  return (position.x >= 0 && position.y >= 0
          && position.x < (int)n_cells.x && position.y < (int)n_cells.y);
}

//! ----------------------------------------------------------------------------
//! PATHING
//! ----------------------------------------------------------------------------


path* NavGrid::getPath(uV2 source, uV2 destination)
{
  PathSearch s(this, source, destination);
  return s.getPath();
}


//! ----------------------------------------------------------------------------
//! MAZE
//! ----------------------------------------------------------------------------

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define TUNNEL_SIZE 3

static iV2 up(0,-TUNNEL_SIZE),
            down(0,TUNNEL_SIZE),
            left(-TUNNEL_SIZE,0),
            right(TUNNEL_SIZE,0);

void shuffle_array(int table[], size_t max)
{
  for(size_t i = max; i > 0; i--)
  {
    int rand_i = rand()%(i+1);
    int swap = table[i];
    table[i] = table[rand_i];
    table[rand_i] = swap;
  }
}

void NavGrid::dig_maze(uV2 pos)
{
  // dig out the current block
  dig_block(pos, TUNNEL_SIZE);

  // shuffle direction order
  static int direction_order[] = { UP, DOWN, LEFT, RIGHT};
  shuffle_array(direction_order, 3);

  for(size_t i = 0; i < 4; i++)
  switch(direction_order[i])
  {
    case UP:
      if(block_is_filled(pos + up*2, TUNNEL_SIZE))
      {
        dig_block(pos + up, TUNNEL_SIZE);
        dig_maze(pos + up*2);
      }
    break;

    case DOWN:
      if(block_is_filled(pos + down*2, TUNNEL_SIZE))
      {
        dig_block(pos + down, TUNNEL_SIZE);
        dig_maze(pos + down*2);
      }
    break;

    case LEFT:
      if(block_is_filled(pos + left*2, TUNNEL_SIZE))
      {
        dig_block(pos + left, TUNNEL_SIZE);
        dig_maze(pos + left*2);
      }
    break;

    case RIGHT:
      if(block_is_filled(pos + right*2, TUNNEL_SIZE))
      {
        dig_block(pos + right, TUNNEL_SIZE);
        dig_maze(pos + right*2);
      }
    break;
  }
}

void NavGrid::dig_block(uV2 centre, size_t size)
{
  int half_1 = size/2,
      half_2 = size - half_1;

  for(int r = (int)centre.y-half_1; r < (int)centre.y+half_2; r++)
  for(int c = (int)centre.x-half_1; c < (int)centre.x+half_2; c++)
  if(isValidGridPos(iV2(c,r)))
    cells[r][c]->obstacle = false;
}

bool NavGrid::block_is_filled(uV2 centre, size_t size)
{
  bool result = true;
  int half_1 = size/2,
      half_2 = size - half_1;

  for(int r = (int)centre.y-half_1; r < (int)centre.y+half_2; r++)
  for(int c = (int)centre.x-half_1; c < (int)centre.x+half_2; c++)
    result = (isValidGridPos(iV2(c,r)) && result
                             && cells[r][c]->obstacle);


  return result;
}

