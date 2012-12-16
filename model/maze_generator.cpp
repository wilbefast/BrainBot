#include "maze_generator.hpp"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define TUNNEL_SIZE 3

//!-----------------------------------------------------------------------------
//! GLOBAL VARIABLES
//!-----------------------------------------------------------------------------
static uV2 block(TUNNEL_SIZE,TUNNEL_SIZE),
            block_wrapper(TUNNEL_SIZE+1,TUNNEL_SIZE+1);

static iV2 up(0,-TUNNEL_SIZE),
            down(0,TUNNEL_SIZE),
            left(-TUNNEL_SIZE,0),
            right(TUNNEL_SIZE,0);


//!-----------------------------------------------------------------------------
//! PRIVATE FUNCTIONS
//!-----------------------------------------------------------------------------
inline bool validPos(uV2 pos, uV2 const& size)
{
  return (pos.x > 0 && pos.y > 0 && pos.x < size.x && pos.y < size.y);
}

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

//!-----------------------------------------------------------------------------
//! FUNCTIONS
//!-----------------------------------------------------------------------------
void setCellBlock(NavCell*** cells, uV2 const& maze_size, uV2 origin, uV2 size, bool obstacle)
{
  uV2 pos;
  for(pos.y = origin.y; pos.y < origin.y+size.y; pos.y++)
  for(pos.x = origin.x; pos.x < origin.x+size.x; pos.x++)
    setCell(cells, maze_size, pos, obstacle);
}

bool isObstacleBlock(NavCell*** cells, uV2 const& maze_size, uV2 origin, uV2 size)
{
  bool obstacle = true;
  uV2 pos;
  for(pos.y = origin.y; pos.y < origin.y + size.y; pos.y++)
  for(pos.x = origin.x; pos.x < origin.x + size.x; pos.x++)
  if(validPos(pos, maze_size))
    obstacle = (obstacle && cells[pos.y][pos.x]->obstacle);

  return obstacle;
}

void setCell(NavCell*** cells, uV2 const& maze_size, uV2 pos, bool obstacle)
{
  if(validPos(pos, maze_size))
    cells[pos.y][pos.x]->obstacle = false;
}

void generate_map(NavCell*** cells, uV2 const& maze_size, uV2 current_position)
{
  setCellBlock(cells, maze_size, current_position, block, false);

  // shuffle direction order
  static int direction_order[] = { 1, 2, 3, 4};
  shuffle_array(direction_order, 3);

  for(size_t i = 0; i < 4; i++)
  switch(direction_order[i])
  {
    case UP:
      if(isObstacleBlock(cells, maze_size, current_position+up, block))
        generate_map(cells, maze_size, current_position+up);
    break;

    case DOWN:
      if(isObstacleBlock(cells, maze_size, current_position+down, block))
        generate_map(cells, maze_size, current_position+down);
    break;

    case LEFT:
      if(isObstacleBlock(cells, maze_size, current_position+left, block))
        generate_map(cells, maze_size, current_position+left);
    break;

    case RIGHT:
      if(isObstacleBlock(cells, maze_size, current_position+right, block_wrapper))
        generate_map(cells, maze_size, current_position+right);
    break;
  }
}
