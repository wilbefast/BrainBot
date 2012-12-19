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

#ifndef GROUP_HPP_INCLUDED
#define GROUP_HPP_INCLUDED

#include "../model/NavGrid.hpp"
#include "../model/GameObject.hpp"
#include "../ai/Formation.hpp"

class Group : public GameObject
{
  //! ATTRIBUTES
private:
  GameObject *first_member, *current_member, *second_member;
  size_t n_members;
  Formation *formation;
  fV3 direction;


public:
  NavGrid const* grid;

  //! METHODS
protected:
  // constructors, destructors
  Group(fV3 position_, NavGrid* grid_, Formation* formation = NULL);
public:
  virtual ~Group();

  // mutators
  void setDirection(fV3 direction_);
  void addMember();

  // accessors
  fV3 getDesiredMemberPosition(size_t member_i) const;

  // overrides GameObject
  void push(fV3 direction);
  int update(float t_delta);
  void draw();

  // interface
protected:
  virtual GameObject* spawnMember(fV3 spawn_position) const = 0;


  //! SUBROUTINES
private:
  void repulse(GameObject* a, GameObject* b);
};

#endif // GROUP_HPP_INCLUDED
