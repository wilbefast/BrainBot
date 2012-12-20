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
grid(grid_),
radius(0.0f),
max_member_radius(0.0f)
{

}

Group::~Group()
{
  for(gobject_container_it i = members.begin(); i != members.end(); i++)
    delete (*i);
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
  fV3 spawn_position = position;
  if((int)radius > 0)
    spawn_position += iV3(rand()%(int)radius, rand()%(int)radius, 0);
  GameObject* spawn = spawnMember(spawn_position);
  members.push_back(spawn);

  // group becomes bigger
  float spawn_radius = spawn->getRadius();
  if(spawn_radius > max_member_radius)
    max_member_radius = spawn_radius;
  radius += spawn->getRadius();

  // inform the formation
  if(formation)
    formation->setStrength(members.size());
}

//!-----------------------------------------------------------------------------
//! ACCESSORS
//!-----------------------------------------------------------------------------

fV3 Group::getIdealPosition(size_t i) const
{
  if(!formation)
    return position;

  fV3 idealPosition = position + formation->getOffset(direction, i);
  if(grid->getCell(idealPosition).)

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
  size_t i = 0;
  for(gobject_container_it it = members.begin(); it != members.end(); it++, i++)
  {
    // cache current object
    GameObject* member = (*it);

    // push the members towards the centroid of the group
    fV3 reform = (getIdealPosition(i) - member->getPosition());
    float norm = reform.normalise();
    if(norm > max_member_radius)
      member->push(reform);

    // push members away from eachother
    gobject_container_it j = it;
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
  for(gobject_container_it i = members.begin(); i != members.end(); i++)
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

float Group::getRadius() const
{
  return radius;
}
