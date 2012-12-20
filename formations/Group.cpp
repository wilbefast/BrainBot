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

#include "../engine/math/vector_angles.hpp"

//!-----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//!-----------------------------------------------------------------------------

Group::Group(fV3 position_, NavGrid* grid_, Formation* formation_) :
GameObject(position_),
members(),
formation(formation_),
direction(1, 0, 0), // face right
radius(0.0f),
max_member_radius(0.0f),
grid(grid_)
{
  // slightly above ground
  position.z = -1;

  // previous position are initialised to this position
  for(size_t i = 0; i < N_PREVIOUS_POSITIONS; i++)
    previous_positions[i] = position_;
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
  direction_.normalise();
  direction = direction_;

  /*fV2 direction2d(direction.x, direction.y),
      new_direction2d(direction_.x, direction_.y);
  turn(direction2d, new_direction2d, 0.1);
  direction.x = direction2d.x;
  direction.y = direction2d.y;*/
}

void Group::addMember()
{
  // add member
  fV3 spawn_position = position;
  if((int)radius > 0)
    spawn_position += iV3(rand()%(int)radius, rand()%(int)radius, 0);
  GameObject* spawn = spawnMember(spawn_position);
  members.push_back(spawn);

  // remember the size of the largest object in the group
  float spawn_radius = spawn->getRadius();
  if(spawn_radius > max_member_radius)
  {
    max_member_radius = spawn_radius;
    formation->setSpacing(max_member_radius * 4);
  }

  // group becomes bigger
  radius += spawn->getRadius();

  // inform the formation
  if(formation)
    formation->setStrength(members.size());
}

//!-----------------------------------------------------------------------------
//! OVERRIDES -- GAMEOBJECT
//!-----------------------------------------------------------------------------

void Group::push(fV3 push_direction)
{
  GameObject::push(push_direction * 5.0f); //! FIXME
}

int Group::update(float t_delta)
{
  //! update position
  GameObject::update(t_delta);

  //! update direction

  //! update previous position
  if((previous_positions[0] - position).getNorm2() > NavCell::SIZE.x*NavCell::SIZE.y)
  {
    for(int i = N_PREVIOUS_POSITIONS-2; i >= 0; i--)
      previous_positions[i+1] = previous_positions[i];
    previous_positions[0] = position;
  }


  //! update each member of the group
  size_t member_i = 0;
  for(gobject_container_it it = members.begin(); it != members.end();
  it++, member_i++)
  {
    // cache current object
    GameObject* member = (*it);

    // move the members with the group
    if(!tryMoveMember(member, member_i, position))
      for(size_t prev_i = 0; prev_i < N_PREVIOUS_POSITIONS; prev_i++)
        if(tryMoveMember(member, member_i, previous_positions[prev_i]))
          break;

    // keep members at a given distance from eachother
    gobject_container_it j = it;
    for(j++; j != members.end(); j++)
    {
      member->repulse((*j), 2.0f);
      member->cohere((*j));
    }



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
  fV3 front_position = position + direction*30.0f;
  glDisable(GL_LIGHTING);
    glBegin(GL_LINE_STRIP);
        glColor3f(0.5f, 0.5f, 1.0f);
      glVertex3fv(front_position.front());
      glVertex3fv(position.front());
      glColor3f(1.0f, 1.0f, 0.0f);
      for(size_t i = 0; i < N_PREVIOUS_POSITIONS; i++)
        glVertex3fv(previous_positions[i].front());
    glEnd();
  glEnable(GL_LIGHTING);

  //! unbind group identifier
  glLoadName(0);
}

float Group::getRadius() const
{
  return radius;
}

//!-----------------------------------------------------------------------------
//! SUBROUTINES -- REFORMATION
//!-----------------------------------------------------------------------------

fV3 Group::getIdealPosition(size_t member_i, fV3 const& centre) const
{
  //! if we have no formation we are forced to use the centroid
  if(!formation)
    return centre;

  fV3 formationPosition = centre + formation->getOffset(direction, member_i);

  //! move to the centre of the group if the formation possible is blocked
  if(grid->isObstacle(formationPosition))
    return centre;


  //! use the formation position whenever possible
  else
    return formationPosition;

}

bool Group::tryMoveMember(GameObject* member, size_t member_i, fV3 const& centre)
{
  // check where the formation wants the object
  fV3 current_position = getIdealPosition(member_i, centre),
      desired_position = member->getPosition();

  // make sure there's a clear line-of-sight
  if(!grid->isLineOfSight(current_position, desired_position))
    return false;

  // push the members towards where the formation wants them
  fV3 reform = (current_position - desired_position);
  float norm = reform.normalise();
  if(norm > max_member_radius)
    member->push(reform * 2.0f);

  return true;
}
