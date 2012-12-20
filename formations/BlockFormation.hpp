/*
Copyright (C) 2012 William James Dyce

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

#ifndef BLOCKFORMATION_HPP_INCLUDED
#define BLOCKFORMATION_HPP_INCLUDED

#include "Formation.hpp"
#include "../game_objects/GameObject.hpp"

class BlockFormation : public Formation
{
  //! ATTRIBUTES
private:
  size_t n_ranks, incomplete_rank, n_files, strength;
  float file_middle, rank_middle, spacing;

  //! METHODS
public:
  // constructors, destrucotrs
  BlockFormation();

  // implements -- Formation
  void setStrength(size_t strength_);
  void setSpacing(float spacing_);
  fV3 getOffset(fV3 direction, size_t member_i) const;

  //! SUBROUTINES
private:
  fV3 getOffset(fV3 direction, size_t rank, size_t file) const;
};

#endif // BLOCKFORMATION_HPP_INCLUDED
