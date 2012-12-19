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
members(),
formation(formation_),
direction(1, 0, 0), // face right
grid(grid_)
{

}

Group::~Group()
{
  for(members_container_it i = members.begin(); i != members.end(); i++)
    delete (*i);
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
  // add member
  GameObject* newbie = spawnMember(getDesiredMemberPosition(members.size()));
  members.push_back(newbie);

  // group becomes bigger
  radius += newbie->getRadius();
}

//!-----------------------------------------------------------------------------
//! OVERRIDES -- GAMEOBJECT
//!-----------------------------------------------------------------------------

void Group::push(fV3 push_direction)
{
  GameObject::push(push_direction * 10.0f); //! TODO FIXME
}

int Group::update(float t_delta)
{
  //! update position
  GameObject::update(t_delta);

  //! update each member of the group
  for(members_container_it i = members.begin(); i != members.end(); i++)
  {
    // cache current object
    GameObject* member = (*i);

    // push the members towards the centroid of the group
    fV3 reform = (position - member->getPosition());
    float norm = reform.normalise();
    if(norm > radius)
      member->push(reform);

    // push members away from eachother
    members_container_it j = i;
    for(j++; j != members.end(); j++)
      member->repulse((*j));

    // call the member's update function
    member->update(t_delta);
  }

  //! group is still alive (return 0)
  return 0;
}

void Group::draw()
{
  //! bind group identifier to all group members
  glLoadName(id);

  //! draw each member of the group
  for(members_container_it i = members.begin(); i != members.end(); i++)
    (*i)->draw();

  //! debug draw position and direction
  fV3 front_position = position + (direction * radius);
  glDisable(GL_LIGHTING);
    glBegin(GL_LINE_LOOP);
      glVertex3fv(position.front());
      glVertex3fv(front_position.front());
    glEnd();
  glEnable(GL_LIGHTING);

  //! unbind group identifier
  glLoadName(0);
}
