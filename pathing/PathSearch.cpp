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

PathSearch::PathSearch(NavGrid const* grid_, uV2 start_coord, uV2 end_coord) :
grid(grid_),
start(new SearchState(grid->cells[start_coord.y][start_coord.x], grid->cells[end_coord.y][end_coord.x])),
end(new SearchState(grid->cells[end_coord.y][end_coord.x], grid->cells[end_coord.y][end_coord.x])),
fallback_plan(start),
states(),
open(),
has_result(false)
{
  start->totalCostEstimate = start->estimateCost(start->cell, end->cell);
  states[start->cell] = start;
  states[end->cell] = end;
  open.push(start);

  has_result = search();
}

//! ----------------------------------------------------------------------------
//! QUERY
//! ----------------------------------------------------------------------------

path_t* PathSearch::getPath()
{

  if(!has_result)
    return NULL;



  //! FIXME



  path_t *result = new path_t();

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
    SearchState *x = open.top(); open.pop();

    // have we reached the end?
    if (x == end)
      return true;

    // try to expand each neighbour
    iV2 grid_pos, grid_offset;
    for(grid_offset.x = -1; grid_offset.x < 2; grid_offset.x++)
    for(grid_offset.y = -1; grid_offset.y < 2; grid_offset.y++)
    {
      if(abs(grid_offset.x + grid_offset.y) != 1)
        continue;
      grid_pos = x->cell->grid_position + grid_offset;
      if(grid_pos.x >= 0 && grid_pos.y >= 0
         && (size_t)grid_pos.x < (size_t)grid->n_cells.x
         && (size_t)grid_pos.y < (size_t)grid->n_cells.y)
         {
            NavCell* neighbour = grid->cells[grid_pos.y][grid_pos.x];
            if(!neighbour->obstacle)
              expand(x, neighbour);
         }
    }

    // remember to close x now that all connections have been expanded
    x->closed = true;

    // keep the best closed state, just in case the target is inaccessible
    if(x->estimateCost(x->cell, end->cell)
       < x->estimateCost(x->cell, end->cell))
      fallback_plan = x;
  }

  // fail!
  return false;
}

void resort_queue(state_queue_t& queue)
{
  std::queue<SearchState*> temp;
  while(!queue.empty())
  {
    temp.push(queue.top());
    queue.pop();
  }
  while(!temp.empty())
  {
    queue.push(temp.front());
    temp.pop();
  }
}

void PathSearch::expand(SearchState* src_state, NavCell* c)
{
  SearchState* dest_state;
  state_map_t::const_iterator it;

  // create states as needed
  it = states.find(c);

  if(it == states.end())
  {
    dest_state = new SearchState(c, end->cell);
    states[c] = dest_state;
  }
  else
  {
    dest_state = (*it).second;

    // closed states are no longer under consideration
    if (dest_state->closed)
      return;
  }


  // states not yet opened always link back to x
  if (!dest_state->opened)
  {
    // set cost before adding to heap, or order will be wrong!
    dest_state->setPrevious(src_state);
    dest_state->opened = true;
    open.push(dest_state);
  }
  // states already open link back to x only if it's better
  else if (src_state->currentCost < dest_state->currentCost)
  {
    // remove, reset cost and replace, or order will be wrong!
    dest_state->setPrevious(src_state);
    resort_queue(open);
  }
}
