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
  //! ATTRIBUTES
private:
  fV3 origin;
  unsigned int numberOfRows;
  unsigned int numberOfCols;
  float cellHeight;
  float cellSize;
  NavCell **grid;
  float yMargin;

  //! METHODS
public:
  // constructors, destructors
  NavGrid(fV3 origin_, unsigned int numberOfCols_, unsigned int numberOfRows_,
          float cellHeight_, float cellSize_);
  virtual ~NavGrid();

  // accessors
  uV2 whatCell(fV2 position) const;
  fV3 getAbsoluteCellPosition(uV2 position) const;
  uV2 getSize() const;
  fV3 getOrigin() const;
  unsigned int getCellSize() const;
  NavCell getCell(uV2 position);

  // mutators
  void generateGrid(std::vector<GameObject>& objects);
  uRect getApproximateFootprint(GameObject& o);
};

#endif // NAVGRID_HPP_INCLUDED

