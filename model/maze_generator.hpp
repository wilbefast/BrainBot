#ifndef MAZE_GENERATOR_HPP_INCLUDED
#define MAZE_GENERATOR_HPP_INCLUDED

#include "NavGrid.hpp"
#include "NavCell.hpp"

#include "../engine/math/V2.hpp"


void setCell(NavCell*** cells, uV2 const& maze_size, uV2 pos, bool obstacle);

void setCellBlock(NavCell*** cells, uV2 const& maze_size, uV2 origin, uV2 size,
                  bool obstacle);

bool isObstacleBlock(NavCell*** cells, uV2 const& maze_size, uV2 origin, uV2 size);

void generate_map(NavCell***, uV2 const& maze_size, uV2 current_position);

#endif // MAZE_GENERATOR_HPP_INCLUDED
