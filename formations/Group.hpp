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

#include "../pathing/NavGrid.hpp"
#include "../game_objects/GameObject.hpp"
#include "../formations/Formation.hpp"

//! **ABSTRACT**
class Group : public GameObject
{
  //! CONSTANTS
private:
  static const size_t N_PREVIOUS_POSITIONS = 10;

  //! ATTRIBUTES
private:
  gobject_container members;
  Formation *formation;
  fV3 direction;
  float radius, max_member_radius;
  fV3 previous_positions[N_PREVIOUS_POSITIONS];

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

  // overrides GameObject
  void push(fV3 direction);
  int update(float t_delta);
  void draw();
  float getRadius() const;

  // interface
protected:
  virtual GameObject* spawnMember(fV3 spawn_position) const = 0;


  //! SUBROUTINES
private:
  fV3 getIdealPosition(size_t member_i, fV3 const& centre) const;
  bool tryMoveMember(GameObject* member, size_t member_i, fV3 const& centre);
};

#endif // GROUP_HPP_INCLUDED
