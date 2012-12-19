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


#ifndef GAMEOBJECT_HPP_INCLUDED
#define GAMEOBJECT_HPP_INCLUDED

#include "../physics/CollisionMask.hpp"
#include "../view/ObjectView.hpp"
#include "../engine/math/V3.hpp"
#include "../engine/utils/IntrusiveLinked.hpp"

class GameObject : public IntrusiveLinked
{
//! VARIABLES
private:
  static size_t next_id;


//! ATTRIBUTES
protected:
  fV3 position;
  ObjectView* view;
  CollisionMask* mask;
public:
  const size_t id;


//! METHODS
public:
  // constructors, destructors
  GameObject(fV3 position_, ObjectView* view_ = NULL, CollisionMask* = NULL);
  virtual ~GameObject();
  // accessors
  fV3 const& getPosition() const { return position; }
  // mutators
  void push(fV3 direction);
  void repulse(GameObject* other, float spring_factor = 1.0f);
  // called each frame
  int update(float t_delta);
  void draw() const;
};

#endif // GAMEOBJECT_HPP_INCLUDED
