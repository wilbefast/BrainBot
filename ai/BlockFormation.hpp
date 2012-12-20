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
#include "../model/GameObject.hpp"

class BlockFormation : public Formation
{
  //! ATTRIBUTES
private:
  size_t n_ranks, incomplete_rank, n_files, strength;
  float file_middle, rank_middle;

  //! METHODS
public:
  // constructors, destrucotrs
  BlockFormation();

  // mutators
  void setStrength(size_t strength_);

  // implements -- Formation
  void form(fV3 centre, fV3 direction, gobject_container& objs);

  //! SUBROUTINES
private:
  fV3 getOffset(fV3 direction, size_t rank, size_t file) const;
  fV3 getOffset(fV3 direction, size_t member_i) const;
};

#endif // BLOCKFORMATION_HPP_INCLUDED
