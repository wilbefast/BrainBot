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

#include "StrategyCamera.hpp"

#include "../engine/opengl.h"

#define PITCH 30
#define MAX_Z -30


#include <stdio.h>

//! ----------------------------------------------------------------------------
//! CONSTRUCTORS, DESTRUCTORS
//! ----------------------------------------------------------------------------

StrategyCamera::StrategyCamera() :
position(0, 0, 100)
{
  //ctor
}

StrategyCamera::~StrategyCamera()
{
  //dtor
}

//! ----------------------------------------------------------------------------
//! MUTATORS
//! ----------------------------------------------------------------------------

void StrategyCamera::pan(fV3 amount)
{
  position += amount;
  //if(position.z > MAX_Z)
    //position.z = MAX_Z;
}

//! ----------------------------------------------------------------------------
//! OPENGL
//! ----------------------------------------------------------------------------

static int turn = 0;

void StrategyCamera::lookThrough() const
{
  turn = (turn + 1)%360;

  glRotatef(180, 0.0f, 1.0f, 0.0f);
  //glRotatef(PITCH, 1.0f, 0.0f, 0.0f);
  glTranslatef(position.x, position.y, position.z);

}
