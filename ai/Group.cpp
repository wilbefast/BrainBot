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
second_member(NULL),
n_members(0),
direction(1,0,0), // face right
grid(grid_)
{

}

Group::~Group()
{
  //! delete each member of the group
  first_member->deleteConnections();
  delete first_member;
}

// ---- Formation managment ----------------------------------------------------

/*void Group::assembleFormation() {
    uV2 tmpRelativePosition;

    if(formation != NULL) {
        for(unsigned int i = 0; i < members.size(); i++) {
            tmpRelativePosition = formation->assignPosition(members[i]);
            members[i]->setPosition(fV2(tmpRelativePosition.x * formation->getSpotSize().x + position.x,
                                 tmpRelativePosition.y * formation->getSpotSize().y + position.y));
        }

        tmpRelativePosition = formation->assignLeaderPosition(leader);
        leader->setPosition(fV2(tmpRelativePosition.x * formation->getSpotSize().x + position.x,
                         position.y - formation->getSpotSize().y));
    }
}*/

//!-----------------------------------------------------------------------------
//! ACCESSORS
//!-----------------------------------------------------------------------------

fV3 Group::getDesiredMemberPosition(size_t member_i) const
{
  return /*(formation)
        ? position + formation->getMemberPosition(member_i)
        : position;*/ position + fV3(rand()%30, rand()%30, 0);

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
  if(first_member)
  {
    current_member = first_member;
    do
    {
      // push the members towards the centre of the group
      fV3 direction = (position - current_member->getPosition());
      float norm = direction.normalise();
      if(norm > 32.0f)
        current_member->push(direction);

      // iterate through other members of the group
      second_member = (GameObject*)current_member->getNext();
      while(second_member != first_member)
      {
        // push members away from eachother
        current_member->repulse(second_member);

        // advance iterator
        second_member = (GameObject*)second_member->getNext();
      }

      // call the members' update functions
      current_member->update(t_delta);

      // advance iterator
      current_member = (GameObject*)current_member->getNext();
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

