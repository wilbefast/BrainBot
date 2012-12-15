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


#ifndef PATHSEARCH_HPP_INCLUDED
#define PATHSEARCH_HPP_INCLUDED

#include <map>
#include <queue>

#include "../model/NavCell.hpp"

typedef std::deque<NavCell*> path;

#include "../model/NavGrid.hpp"

class PathSearch;

#include "SearchState.hpp"

class PathSearch
{
  //! ATTRIBUTES
private:
  NavGrid *grid;
  SearchState *start, *end, *fallback_plan;
  std::map<NavCell*, SearchState*> states;
  std::priority_queue<SearchState> open;
  bool has_result;

  //! METHODS
public:
  // constructors, destructors
  PathSearch(NavGrid *grid_, uV2 start_coord, uV2 end_coord);

  // query
  unsigned int estimateRemainingCost(NavCell const*) const;
  path* getPath();


  //! SUBROUTINES
private:
  bool search();
  void expand();
};


#endif // PATHSEARCH_HPP_INCLUDED
