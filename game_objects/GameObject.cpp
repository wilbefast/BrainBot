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

#include "GameObject.hpp"

#include "../engine/opengl.h" // for glLoadName

//! ----------------------------------------------------------------------------
//! IDENTIFIER ALLOCATION
//! ----------------------------------------------------------------------------

size_t GameObject::next_id = 1; // 0 is reserved for null

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

GameObject::GameObject(fV3 position_, ObjectView* view_, CollisionMask* mask_) :
position(position_),
view(view_),
mask(mask_),
id(next_id++)
{
}

GameObject::~GameObject()
{
  //! NOT shared with other object, so we DO delete them
  if(view)
    delete view;
  if(mask)
    delete mask;
}

//! ----------------------------------------------------------------------------
//! MUTATORS
//! ----------------------------------------------------------------------------

void GameObject::push(fV3 direction)
{
  if(mask)
    mask->push(direction);
  else
    position += direction;
}

void GameObject::repulse(GameObject* other, float spring_factor)
{
  fV3 to_other = other->position - this->position;
  float distance2 = to_other.getNorm2(), radius = getRadius();

  if(distance2 < radius*radius*4)
  {
    spring_factor /= distance2;
    this->push(-to_other * spring_factor);
    other->push(to_other * spring_factor);
  }
}

void GameObject::cohere(GameObject* other, float spring_factor)
{
  fV3 to_other = other->position - this->position;
  float distance2 = to_other.getNorm2(), radius = getRadius();

  float radius2 = radius*radius;
  if(distance2 > radius2*8 && distance2 < radius2*16)
  {
    spring_factor /= distance2;
    this->push(to_other * spring_factor);
    other->push(-to_other * spring_factor);
  }
}


//! ----------------------------------------------------------------------------
//! ACCESSORS
//! ----------------------------------------------------------------------------

fV3 const& GameObject::getPosition() const
{
  return position;
}

float GameObject::getRadius() const
{
  return (mask) ? mask->getRadius() : 0;
}

//! ----------------------------------------------------------------------------
//! CALLED EACH FRAME
//! ----------------------------------------------------------------------------

int GameObject::update(float t_delta)
{
  int result = 0;
  if(mask)
    result = mask->update(position, t_delta);

  if(view)
    view->setPosition(position);

  return result;
}

void GameObject::draw() const
{
  if(view)
    view->draw();
}
