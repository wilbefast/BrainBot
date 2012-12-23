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

#ifndef NAVGRID_HPP_INCLUDED
#define NAVGRID_HPP_INCLUDED

#include "Path.hpp"

#include "../engine/math/V3.hpp"
#include "../engine/math/Rect.hpp"

#include "../game_objects/GameObject.hpp"
#include "NavCell.hpp"


class NavGrid
{
  //! FRIENDS
friend class NavGridView;
friend class PathSearch;

  //! ATTRIBUTES
public:
    const uV2 n_cells;
protected:
  fV3 origin;
  NavCell ***cells;

  //! METHODS
public:
  // constructors, destructors
  NavGrid(fV3 origin_, uV2 grid_size_);
  virtual ~NavGrid();

  // accessors
  fV3 getOrigin() const;
  uV2 const& getNCells() const;

  // collision testing
  bool isObstacle(uV2 grid_position) const;
  bool isObstacle(fV3 position) const;
  bool isValidGridPos(iV2 position) const;

  // conversion
  uV2 vertexToGridPos(fV2 position) const;
  fV3 gridPosToVertex(uV2 grid_position) const;
  fV3 gridPosToSize(uV2 grid_position) const;

  // pathing
  path_t* getPath(iV2 source, iV2 destination) const;
  path_t* getPath(fV3 source, fV3 destination) const;
  bool isLineOfSight(iV2 start, iV2 end) const;
  bool isLineOfSight(fV3 start, fV3 end) const;
};

#endif // NAVGRID_HPP_INCLUDED

