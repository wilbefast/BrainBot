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
start(new SearchState(grid->cells[start_coord.y][start_coord.x], this)),
end(new SearchState(grid->cells[end_coord.y][end_coord.x], this)),
fallback_plan(start),
states(),
open(),
has_result(false)
{
  start->totalCostEstimate = estimateRemainingCost(start->cell);
  states[start->cell] = start;
  states[end->cell] = end;
  open.push(SearchStateRef(start));
}

//! ----------------------------------------------------------------------------
//! QUERY
//! ----------------------------------------------------------------------------

unsigned int PathSearch::estimateRemainingCost(NavCell const* cell) const
{
  fV3 remaining_vector =
    grid->getCellPosition(cell->grid_position)
    - grid->getCellPosition(end->cell->grid_position);

  return remaining_vector.getNorm();
}

path* PathSearch::getPath()
{
  path *result = new path();

  // start at the end, trace backwards adding vertices
  SearchState const* current = has_result ? end : fallback_plan;
  while (current != start)
  {
    // add element to front, in order for list to be in the right order
    result->push_front(current->cell);
    current = current->previous;
  }
  return result;
}

//! ----------------------------------------------------------------------------
//! SUBROUTINES
//! ----------------------------------------------------------------------------

bool PathSearch::search()
{
  while (!open.empty())
  {
    // expand from the open state that is currently cheapest
    SearchState *x = open.top().state; open.pop();

    // have we reached the end?
    if (x == end)
      return true;

    // try to expand each neighbour
    iV2 grid_pos, grid_offset;
    for(grid_offset.x = -1; grid_offset.x < 2; grid_offset.x++)
    for(grid_offset.y = -1; grid_offset.y < 2; grid_offset.y++)
    {
      grid_pos = x->cell->grid_position + grid_offset;
      if(grid_pos.x >= 0 && grid_pos.y >= 0
         && grid_pos.x < grid->n_cells.x && grid_pos.y < grid->n_cells.y)
         {
            NavCell* neighbour = grid->cells[grid_pos.y][grid_pos.x];
            if(!neighbour->obstacle)
              expand(x, neighbour);
         }
    }

    // remember to close x now that all connections have been expanded
    x->closed = true;

    // keep the best closed state, just in case the target is inaccessible
    if(estimateRemainingCost(x->cell) < estimateRemainingCost(fallback_plan->cell))
      fallback_plan = x;
  }

  // fail!
  return false;
}

void PathSearch::expand(SearchState* src_state, NavCell* c)
{
  SearchState* dest_state;
  cellStateMap::const_iterator it;

  // create states as needed
  it = states.find(c);

  if(it == states.end())
  {
    dest_state = new SearchState(c, this);
    states[c] = dest_state;
  }
  else
  {

    dest_state = (*it).second;

    // closed states are no longer under consideration
    if (dest_state->closed)
      return;
  }


/*
  // states not yet opened always link back to x
  if (!open.contains(dest_state))
  {
    // set cost before adding to heap, or order will be wrong!
    dest_state.setParent(src_state);
    open.add(dest_state);
  }
  // states already open link back to x only if it's better
  else if (src_state.currentCost < dest_state.currentCost)
  {
    // remove, reset cost and replace, or order will be wrong!
    open.remove(dest_state);
    dest_state.setParent(src_state);
    open.add(dest_state);
  }*/
}
