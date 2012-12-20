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

#ifndef SEARCHSTATE_HPP_INCLUDED
#define SEARCHSTATE_HPP_INCLUDED

#include "NavCell.hpp"

class SearchState
{
  //! NESTING
public:
  struct compare_t
  {
    bool operator()(SearchState* a, SearchState* b)
    {
      return (*a)<(*b);
    }
  };


  //! FRIENDS
friend class PathSearch;

  //! ATTRIBUTES
private:
  NavCell const* goal;
  NavCell* cell;                    // the end cell of this path
  SearchState const* previous;      // previous state in the path back to the start

  unsigned int currentCost, remainingCostEstimate, totalCostEstimate;

  bool opened, closed;

  //! METHODS
public:
  // constructors, destructors
  SearchState(NavCell* cell, NavCell const* goal);

  // mutators
  void setPrevious(SearchState *previous_);

  // operators -- for priority queue
  bool operator<(SearchState const& other) const;
  bool operator>(SearchState const& other) const;
  bool operator<=(SearchState const& other) const;
  bool operator>=(SearchState const& other) const;
  bool operator==(SearchState const& other) const;


  //! SUBROUTINES
private:
  float estimateCost(NavCell const* a, NavCell const* b);

};

#endif // SEARCHSTATE_HPP_INCLUDED
