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

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define TUNNEL_SIZE 3
#define PERCENT_BROKEN_WALLS 35

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

  // dig out a "perfect" maze
  uV2 middle(n_cells.x/2, n_cells.y/2);
  top_left_block = middle;
  dig_maze(middle);
  while(block_is_valid(top_left_block, TUNNEL_SIZE))
    top_left_block.y -= TUNNEL_SIZE;
  top_left_block.y += TUNNEL_SIZE;
  while(block_is_valid(top_left_block, TUNNEL_SIZE))
    top_left_block.x -= TUNNEL_SIZE;
  top_left_block.x += TUNNEL_SIZE;


  // break some extra walls, just for fun
  break_walls();
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

//! ----------------------------------------------------------------------------
//! MAZE -- GENERATE A PERFECT MAZE
//! ----------------------------------------------------------------------------

void NavGrid::dig_maze(uV2 pos)
{
  // dig out the current block
  dig_block(pos, TUNNEL_SIZE);

  // shuffle direction order
  static int direction_order[] = { UP, DOWN, LEFT, RIGHT};
  shuffle_array(direction_order, 3);

  for(size_t i = 0; i < 4; i++)
  {
    // get a direction
    iV2 dir;
    switch(direction_order[i])
    {
      case UP: dir = up; break;
      case DOWN: dir = down; break;
      case LEFT: dir = left; break;
      case RIGHT: dir = right; break;
    }

    // strike the earth!
    iV2 step = pos + dir, two_steps = step + dir;
    if(block_is_filled(two_steps, TUNNEL_SIZE)
       && !block_touches_border(two_steps, TUNNEL_SIZE))
    {
      dig_block(step, TUNNEL_SIZE);
      dig_maze(two_steps);
    }
  }
}

void NavGrid::dig_block(uV2 centre, size_t size)
{
  int half_1 = size/2,
      half_2 = size - half_1;

  for(int r = (int)centre.y-half_1; r < (int)centre.y+half_2; r++)
  for(int c = (int)centre.x-half_1; c < (int)centre.x+half_2; c++)
  if(isValidGridPos(iV2(c,r)))
  {
    // dig out the block
    cells[r][c]->obstacle = false;
  }
  // reset top-left corner of the maze
  if(centre.x <= top_left_block.x && centre.y <= top_left_block.y)
    top_left_block = centre;
}

bool NavGrid::block_is_filled(uV2 centre, size_t size)
{
  int half_1 = size/2,
      half_2 = size - half_1;

  for(int r = (int)centre.y-half_1; r < (int)centre.y+half_2; r++)
  for(int c = (int)centre.x-half_1; c < (int)centre.x+half_2; c++)
    if(!isValidGridPos(iV2(c,r)) || !cells[r][c]->obstacle)
       return false;


  return true;
}

bool NavGrid::block_is_clear(uV2 centre, size_t size)
{
  int half_1 = size/2,
      half_2 = size - half_1;

  for(int r = (int)centre.y-half_1; r < (int)centre.y+half_2; r++)
  for(int c = (int)centre.x-half_1; c < (int)centre.x+half_2; c++)
    if(!isValidGridPos(iV2(c,r)) || cells[r][c]->obstacle)
       return false;


  return true;
}

bool NavGrid::block_is_valid(uV2 centre, size_t size)
{
  int half_1 = size/2,
      half_2 = size - half_1;

  for(int r = (int)centre.y-half_1; r < (int)centre.y+half_2; r++)
  for(int c = (int)centre.x-half_1; c < (int)centre.x+half_2; c++)
    if(!isValidGridPos(iV2(c,r)))
       return false;
  return true;
}

bool NavGrid::block_touches_border(uV2 centre, size_t size)
{
  int half_1 = size/2,
      half_2 = size - half_1,
      r, c;

  // top and bottom
  for(c = (int)centre.x-half_1-1; c < (int)centre.x+half_2+1; c++)
  {
    if(!isValidGridPos(iV2(c,(int)centre.y-half_1-1))
    || !isValidGridPos(iV2(c,(int)centre.y+half_1+1)))
       return true;
  }

  // left and right
  for(r = (int)centre.y-half_1; r < (int)centre.y+half_2; r++)
  {
      if(!isValidGridPos(iV2((int)centre.x-half_1-1,r))
      || !isValidGridPos(iV2((int)centre.x+half_2+1,r)))
       return true;
  }

  // if you've made it this far, you don't need glasses
  return false;
}

//! ----------------------------------------------------------------------------
//! MAZE -- APPLY NOISE TO CREATE AN IMPERFECT MAZE
//! ----------------------------------------------------------------------------


void NavGrid::break_walls()
{

  /*std::cout << filled_neighbour_blocks(uV2(10,13), TUNNEL_SIZE, false) << '\n';
  cells[13][10]->obstacle = false;*/

  uV2 origin = top_left_block, pos;
  std::cout << origin << '\n';

  /*for(pos.y = 0; pos.y < n_cells.y; pos.y++)
  {
    for(pos.x = 0; pos.x < n_cells.x; pos.x++)
    if(block_is_filled(pos, TUNNEL_SIZE))
      std::cout << is_block_wall(pos, TUNNEL_SIZE) << ' ';
    else
      std::cout << "* ";
    std::cout << '\n';
  }*/

  for(pos.y = origin.y; pos.y < n_cells.y; pos.y += TUNNEL_SIZE)
  {

  for(pos.x = origin.x; pos.x < n_cells.x; pos.x += TUNNEL_SIZE)
  {
    if(block_is_filled(pos, TUNNEL_SIZE))
      std::cout << "# ";
    else
      std::cout << "- ";


  for(pos.y = origin.y; pos.y < n_cells.y; pos.y += TUNNEL_SIZE)
    for(pos.x = origin.x; pos.x < n_cells.x; pos.x += TUNNEL_SIZE)
      if(rand() % 100 < PERCENT_BROKEN_WALLS
      && !block_touches_border(pos, TUNNEL_SIZE)
      && block_is_wall(pos, TUNNEL_SIZE))
        dig_block(pos, TUNNEL_SIZE);

  }
      std::cout << '\n';
  }

  /*if(rand() % 100 < PERCENT_BROKEN_WALLS
  && !block_touches_border(pos, TUNNEL_SIZE)
  && block_is_wall(pos, TUNNEL_SIZE))
    dig_block(pos, TUNNEL_SIZE); */


  /*for(pos.x = 0; pos.x < n_cells.x; pos.x++)
  for(pos.y = 0; pos.y < n_cells.y; pos.y++)
  if(rand() % 100 < PERCENT_BROKEN_WALLS
  && !block_touches_border(pos, TUNNEL_SIZE)
  && block_is_wall(pos, TUNNEL_SIZE))
    dig_block(pos, TUNNEL_SIZE);*/



}

size_t NavGrid::filled_neighbour_blocks(uV2 centre, size_t size, bool diagonals)
{
  size_t result = 0;
  //std::cout << "couting those around " << centre << '\n';
  for(int r = centre.y - size, i = -1; i < 2; r += size, i++)
  for(int c = centre.x - size, j = -1; j < 2; c += size, j++)
  {
    /*if(diagonals || abs(i+j) == 1)
    std::cout << "checking block centered on " << c << ',' << r
              << '(' << cells[r][c]->obstacle << ")\n";*/
    if((diagonals || abs(i+j) == 1) && block_is_filled(iV2(c, r), size))
      result++;
  }

  return result;
}

bool NavGrid::block_is_wall(uV2 centre, size_t size)
{
  // open areas cannot be walls
  if(!block_is_filled(centre, size))
    return false;

  // check neighbours
  bool n = block_is_filled(centre + iV2(0, -size), size),
        s = block_is_filled(centre + iV2(0, size), size),
        e = block_is_filled(centre + iV2(size, 0), size),
        w = block_is_filled(centre + iV2(-size, 0), size);

  return
  // vertical wall
    (!n && !s && e && w) ||
  // horizontal wall
    (n && s && !e && !w);
}

