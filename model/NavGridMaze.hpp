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

#ifndef NAVGRIDMAZE_HPP_INCLUDED
#define NAVGRIDMAZE_HPP_INCLUDED

#include "NavGrid.hpp"

class NavGridMaze : public NavGrid
{
  //! ATTRIBUTES
private:
  size_t tunnel_size, percent_broken_walls;
  uV2 top_left_block;
  iV2 up, down, left, right;

  //! METHODS
public:
  // constructors
  NavGridMaze(fV3 origin_, uV2 grid_size_, size_t _tunnel_size, size_t _percent_broken_walls);

  // mutators
  void dig_block(uV2 centre);
  bool set_tunnel_size(size_t tunnel_size);

  // accessors
  bool block_is_filled(uV2 centre) const;
  bool block_is_clear(uV2 centre) const;
  bool block_is_valid(uV2 centre) const;
  bool block_touches_border(uV2 centre) const;
  bool block_border_is_clear(uV2 centre) const;
  size_t filled_neighbour_blocks(uV2 centre, bool diagonals) const;
  bool block_is_wall(uV2 centre) const;

  //! SUBROUTINES
private:
  void dig_maze(uV2 start_pos);
  void break_walls();
};

#endif // NAVGRIDMAZE_HPP_INCLUDED
