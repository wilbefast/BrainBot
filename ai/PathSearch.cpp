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

#include "PathSearch.hpp"

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

PathSearch::PathSearch(NavGrid *grid_, uV2 start_coord, uV2 end_coord) :
grid(grid_),
start(new SearchState(&(grid->cells[start_coord.y][start_coord.x]), this)),
end(new SearchState(&(grid->cells[end_coord.y][end_coord.x]), this)),
fallback_plan(start),
states(),
open()
{
  start->totalCostEstimate = estimateRemainingCost(start->cell);
  states[start->cell] = start;
  states[end->cell] = end;
  open.push((*start));
}

//! ----------------------------------------------------------------------------
//! QUERY
//! ----------------------------------------------------------------------------

unsigned int PathSearch::estimateRemainingCost(NavCell const* cell) const
{
  //! TODO
  return 0;
}
