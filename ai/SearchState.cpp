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

#include "SearchState.hpp"

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

SearchState::SearchState(NavCell* cell_, NavCell const* goal_) :
goal(goal_),
cell(cell_),
previous(NULL),
currentCost(0),
remainingCostEstimate(0),
totalCostEstimate(0),
opened(false),
closed(false)
{

}

//! ----------------------------------------------------------------------------
//! MUTATORS
//! ----------------------------------------------------------------------------


void SearchState::setPrevious(SearchState *previous_)
{
  previous = previous_;
  currentCost = previous->currentCost + previous->cell->cost;
  remainingCostEstimate = estimateCost(cell, goal);
  totalCostEstimate = currentCost + remainingCostEstimate;
}

//! ----------------------------------------------------------------------------
//! OPERATORS
//! ----------------------------------------------------------------------------

bool SearchState::operator<(SearchState const& other) const
{
  int delta = (int)totalCostEstimate - (int)other.totalCostEstimate;
  if(!delta)
    delta = (int)remainingCostEstimate - (int)other.remainingCostEstimate;
  return (delta > 0);
}

bool SearchState::operator>(SearchState const& other) const
{
  int delta = (int)totalCostEstimate - (int)other.totalCostEstimate;
  if(!delta)
    delta = (int)remainingCostEstimate - (int)other.remainingCostEstimate;
  return (delta < 0);
}

bool SearchState::operator<=(SearchState const& other) const
{
  return !((*this) > other);
}

bool SearchState::operator>=(SearchState const& other) const
{
  return !((*this) < other);
}

bool SearchState::operator==(SearchState const& other) const
{
  return (cell == other.cell
          && goal == other.goal
          && previous == other.previous);
}

//! ----------------------------------------------------------------------------
//! SUBROUTINES
//! ----------------------------------------------------------------------------

float SearchState::estimateCost(NavCell const* a, NavCell const* b)
{

  fV2 remaining_vector = (fV2)(a->grid_position) - (fV2)(b->grid_position);
  remaining_vector.x *= NavCell::size.x;
  remaining_vector.y *= NavCell::size.y;

  return remaining_vector.getNorm();
}
