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

#include "BrainBotGroup.hpp"
#include "BlockFormation.hpp"

#include "../model/BrainBot.hpp"


//!-----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//!-----------------------------------------------------------------------------

BrainBotGroup::BrainBotGroup(fV3 position_, NavGrid* grid_) :
Group(position_, grid_, new BlockFormation())
{
  //! Create all the members of the group
  for(size_t i = 0; i < (size_t)INIT_SIZE; i++)
    addMember();
}

BrainBotGroup::~BrainBotGroup()
{

}

//!-----------------------------------------------------------------------------
//! IMPLEMENTS GROUP
//!-----------------------------------------------------------------------------

GameObject* BrainBotGroup::spawnMember(fV3 spawn_position) const
{
  return new BrainBot(spawn_position, grid);
}
