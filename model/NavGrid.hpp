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

#include "../engine/math/V3.hpp"
#include "../engine/math/Rect.hpp"

#include "GameObject.hpp"
#include "NavCell.hpp"


class NavGrid
{
  //! FRIENDS
  friend class NavGridView;


  //! ATTRIBUTES
private:
  fV3 origin;
  uV2 n_cells;
  NavCell **grid;

  //! METHODS
public:
  // constructors, destructors
  NavGrid(fV3 origin_, uV2 grid_size_);
  virtual ~NavGrid();

  // accessors
  fV3 getOrigin() const;
  NavCell const& getCell(uV2 position) const;
  uV2 const& getNCells() const;
  uV2 getGridPosition(fV2 position) const;
  fV3 getCellPosition(uV2 position) const;
  uRect getApproximateFootprint(GameObject& o);

  // mutators
  void generateGrid(std::vector<GameObject>& objects);

};

#endif // NAVGRID_HPP_INCLUDED

