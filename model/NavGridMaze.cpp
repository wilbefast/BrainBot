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

#include "NavGridMaze.hpp"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

//! ----------------------------------------------------------------------------
//! PRIVATE FUNCTIONS
//! ----------------------------------------------------------------------------

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
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------


NavGridMaze::NavGridMaze(fV3 origin_, uV2 grid_size_, size_t tunnel_size_, size_t percent_broken_walls_) :
NavGrid(origin_, grid_size_),
tunnel_size(tunnel_size_),
percent_broken_walls(percent_broken_walls_),
top_left_block(grid_size_.x/2, grid_size_.y/2),
up(0,-tunnel_size_),
down(0,tunnel_size_),
left(-tunnel_size_,0),
right(tunnel_size_,0)
{

  // dig out a "perfect" maze
  dig_maze(top_left_block);

  // snap top-left block to top-left
  while(block_is_valid(top_left_block))
    top_left_block.y -= tunnel_size;
  top_left_block.y += tunnel_size;
  while(block_is_valid(top_left_block))
    top_left_block.x -= tunnel_size;
  top_left_block.x += tunnel_size;


  // starting at top-left: break some extra walls, just for fun
  break_walls();
}

//! ----------------------------------------------------------------------------
//! GENERATE A PERFECT MAZE
//! ----------------------------------------------------------------------------

void NavGridMaze::dig_maze(uV2 pos)
{
  // dig out the current block
  dig_block(pos);

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
    if(block_is_filled(two_steps)
       && !block_touches_border(two_steps))
    {
      dig_block(step);
      dig_maze(two_steps);
    }
  }
}

void NavGridMaze::dig_block(uV2 centre)
{
  int half_1 = tunnel_size/2,
      half_2 = tunnel_size - half_1;

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

bool NavGridMaze::block_is_filled(uV2 centre) const
{
  int half_1 = tunnel_size/2,
      half_2 = tunnel_size - half_1;

  for(int r = (int)centre.y-half_1; r < (int)centre.y+half_2; r++)
  for(int c = (int)centre.x-half_1; c < (int)centre.x+half_2; c++)
    if(!isValidGridPos(iV2(c,r)) || !cells[r][c]->obstacle)
       return false;


  return true;
}

bool NavGridMaze::block_is_clear(uV2 centre) const
{
  int half_1 = tunnel_size/2,
      half_2 = tunnel_size - half_1;

  for(int r = (int)centre.y-half_1; r < (int)centre.y+half_2; r++)
  for(int c = (int)centre.x-half_1; c < (int)centre.x+half_2; c++)
    if(!isValidGridPos(iV2(c,r)) || cells[r][c]->obstacle)
       return false;


  return true;
}

bool NavGridMaze::block_is_valid(uV2 centre) const
{
  int half_1 = tunnel_size/2,
      half_2 = tunnel_size - half_1;

  for(int r = (int)centre.y-half_1; r < (int)centre.y+half_2; r++)
  for(int c = (int)centre.x-half_1; c < (int)centre.x+half_2; c++)
    if(!isValidGridPos(iV2(c,r)))
       return false;
  return true;
}

bool NavGridMaze::block_touches_border(uV2 centre) const
{
  int half_1 = tunnel_size/2,
      half_2 = tunnel_size - half_1,
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
//! BREAK SOME WALLS DOWN TO MAKE IT IMPERFECT
//! ----------------------------------------------------------------------------


void NavGridMaze::break_walls()
{
  uV2 pos;
  for(pos.y = top_left_block.y; pos.y < n_cells.y; pos.y += tunnel_size)
    for(pos.x = top_left_block.x; pos.x < n_cells.x; pos.x += tunnel_size)
      // don't clear the whole map!
      if((rand() % 100) < (int)percent_broken_walls
      // objects should not be able to leave the map
      && !block_touches_border(pos)
      // destroy walls only, for a more aesthetic effect
      && block_is_wall(pos))
        dig_block(pos);
}

size_t NavGridMaze::filled_neighbour_blocks(uV2 centre, bool diagonals) const
{
  size_t result = 0;
  //std::cout << "couting those around " << centre << '\n';
  for(int r = centre.y - tunnel_size, i = -1; i < 2; r += tunnel_size, i++)
  for(int c = centre.x - tunnel_size, j = -1; j < 2; c += tunnel_size, j++)
  {
    if((diagonals || abs(i+j) == 1) && block_is_filled(iV2(c, r)))
      result++;
  }

  return result;
}

bool NavGridMaze::block_is_wall(uV2 centre) const
{
  // open areas cannot be walls
  if(!block_is_filled(centre))
    return false;

  // check neighbours
  bool n = block_is_filled(centre + up),
        s = block_is_filled(centre + down),
        e = block_is_filled(centre + right),
        w = block_is_filled(centre + left);

  return
  // vertical wall
    (!n && !s && e && w) ||
  // horizontal wall
    (n && s && !e && !w);
}

