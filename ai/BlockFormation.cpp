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

#include "BlockFormation.hpp"

#define SPACING 32.0f

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//!-----------------------------------------------------------------------------

BlockFormation::BlockFormation() :
n_ranks(0),
incomplete_rank(0),
n_files(0),
strength(0),
file_middle(0.0f),
rank_middle(0.0f)
{

}

//!-----------------------------------------------------------------------------
//! IMPLEMENTS FORMATION
//!-----------------------------------------------------------------------------

void BlockFormation::setStrength(size_t strength_)
{
  strength = strength_;

  n_files = isqrt(strength);
  file_middle = (n_files - 1) * SPACING * 0.5f;
  n_ranks = strength / n_files;
  rank_middle = (n_ranks - 1) * SPACING * 0.5f;
  incomplete_rank = strength - (n_files * n_ranks);
}

fV3 BlockFormation::getOffset(fV3 direction, size_t member_i) const
{

  size_t rank = member_i / n_files,
          file = member_i % (rank >= n_ranks ? incomplete_rank : n_files);
  return getOffset(direction, rank, file);
}

//!-----------------------------------------------------------------------------
//! SUBROUTINES
//!-----------------------------------------------------------------------------

fV3 BlockFormation::getOffset(fV3 direction, size_t rank, size_t file) const
{
  fV3 left(-direction.y, direction.x, direction.z),
      rank_offset(direction * (rank_middle - (rank * SPACING))),
      file_offset(left * ((file * SPACING) - file_middle));

  return (rank_offset + file_offset);
}






/*void BlockFormation::form(fV3 centre, fV3 direction, gobject_container& objs)
{
  //! reset formation size
  size_t strength_ = objs.size();
  if(strength != strength_)
    setStrength(strength_);

  //! get the left-hand vector of the direction
  fV3 left(-direction.y, direction.x, direction.z);

  //! push each soldier towards where they're meant to be
  gobject_container_it i = objs.begin();
  // for each rank
  for(size_t member_i = 0; member_i < strength; member_i++, i++)
  //size_t member_i = 0;
  //for (size_t r = 0; r < (n_ranks + 1); r++)
  {
    // for each file
    //for (size_t f = 0; f < ((r < n_ranks) ? n_files : incomplete_rank); f++, i++, member_i++)
    {
      // calculate absolute position and move there
      fV3 desired_position = centre + getOffset(direction, member_i),
          reformation_direction = desired_position - (*i)->getPosition();
      float distance = reformation_direction.normalise();

      if(distance > SPACING)
        (*i)->push(reformation_direction);
    }
  }
}
*/

