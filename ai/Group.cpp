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

#include "Group.hpp"

#include "../engine/opengl.h"

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//!-----------------------------------------------------------------------------

Group::Group(fV3 position_, NavGrid* grid_, Formation* formation_) :
GameObject(position_),
first_member(NULL),
current_member(NULL),
n_members(0),
formation(formation_),
direction(1, 0, 0), // face right
grid(grid_)
{

}

Group::~Group()
{
  //! delete each member of the group
  first_member->deleteConnections();
  delete first_member;
}

//!-----------------------------------------------------------------------------
//! ACCESSORS
//!-----------------------------------------------------------------------------

fV3 Group::getDesiredMemberPosition(size_t member_i) const
{
  return /*(formation)
        ? position + formation->getMemberRelativePosition(member_i)
        : */position + fV3(rand() % 32, rand() % 32, 0);

}

//!-----------------------------------------------------------------------------
//! MUTATORS
//!-----------------------------------------------------------------------------

void Group::setDirection(fV3 direction_)
{
  direction = direction_;
  direction.normalise();
}

void Group::addMember()
{
  GameObject* newbie = spawnMember(getDesiredMemberPosition(n_members));
  if(first_member)
    first_member->newNext(newbie);
  else
    first_member = newbie;
  n_members++;
}

//!-----------------------------------------------------------------------------
//! OVERRIDES -- GAMEOBJECT
//!-----------------------------------------------------------------------------

void Group::push(fV3 push_direction)
{
  GameObject::push(push_direction * 10.0f);
}

int Group::update(float t_delta)
{
  //! update position
  GameObject::update(t_delta);

  //! update each member of the group
  size_t member_i = 0;
  if(first_member)
  {
    current_member = first_member;
    do
    {
      // update each member
      updateMember(current_member, member_i, t_delta);

      // advance iterators
      current_member = (GameObject*)current_member->getNext();
      member_i++;
    }
    while(current_member != first_member);
  }

  //! group is still alive (return 0)
  return 0;
}

void Group::draw()
{
  //! bind group identifier to all group members
  glLoadName(id);

  //! draw each member of the group
  if(first_member)
  {
    current_member = first_member;
    do
    {
      // draw the current object
      current_member->draw();

      // advance iterator
      current_member = (GameObject*)current_member->getNext();
    }
    while(current_member != first_member);
  }

  //! debug draw position and direction
  fV3 front_position = position + (direction*32.0f);
  glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
      glVertex3fv(position.front());
      glVertex3fv(front_position.front());
    glEnd();
  glEnable(GL_LIGHTING);

  //! unbind group identifier
  glLoadName(0);
}


//!-----------------------------------------------------------------------------
//! SUBROUTINES
//!-----------------------------------------------------------------------------

void Group::updateMember(GameObject *member, size_t member_i, float t_delta)
{
  // push the members towards the centre of the group

  fV3 reform = (position - member->getPosition());
  float norm = reform.normalise();
  if(norm > 32.0f)
    member->push(reform);

  // iterate through other members of the group

  //! NB - we're overwriting current_member here, we'll need to restore it
  current_member = (GameObject*)member->getNext();
  while(current_member != first_member)
  {
    // push members away from eachother
    member->repulse(current_member);

    // advance inner-iterator
    current_member = (GameObject*)current_member->getNext();
  }

  // call the member's update function
  member->update(t_delta);

  //! revert back to the original state
  current_member = member;
}
