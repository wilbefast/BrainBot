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

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

GameObject::GameObject(fV3 position_, ObjectView* view_, CollisionMask* mask_) :
position(position_),
view(view_),
mask(mask_)
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
    position += direction*3.0f;
}

//! ----------------------------------------------------------------------------
//! CALLED EACH FRAME
//! ----------------------------------------------------------------------------

#include <iostream>

int GameObject::update(float t_delta)
{
  //std::cout << "position before mask->update: " << position << std::endl;
  if(mask)
    return mask->update(position, t_delta);

  //std::cout << "position before view->setPosition: " << position << std::endl;
  if(view)
    view->setPosition(position);

  return 0;
}

void GameObject::draw() const
{
  if(view)
    view->draw();
}
