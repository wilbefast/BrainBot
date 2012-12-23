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

#include "NavCell.hpp"
#include "NavGrid.hpp"

class PathSearch;

#include "SearchState.hpp"
#include "Path.hpp"

#include <map>
#include <queue>
#include <vector>


typedef std::map<NavCell*, SearchState*> state_map_t;
typedef std::priority_queue<SearchState*, std::vector<SearchState*>, SearchState::compare_t>
          state_queue_t;

class PathSearch
{
  //! ATTRIBUTES
private:
  NavGrid const* grid;
  SearchState *start, *end, *fallback_plan;
  state_map_t states;
  state_queue_t open;
  bool has_result;

  //! METHODS
public:
  // constructors, destructors
  PathSearch(NavGrid const* grid_, uV2 start_coord, uV2 end_coord);

  // query
  path_t* getPath();


  //! SUBROUTINES
private:
  bool search();
  void expand(SearchState* src_state, NavCell* c);
};


#endif // PATHSEARCH_HPP_INCLUDED
